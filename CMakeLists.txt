cmake_minimum_required(VERSION 3.22)

find_package(Python3 REQUIRED)

add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/gen_keys.py ${CMAKE_SOURCE_DIR}
        COMMENT "Running script before build"
)

add_custom_target(run_script ALL DEPENDS ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_PROJECT_NAME nintendo-cartridge-reader)
set(CMAKE_PROJECT_INTERFACE cartridge-reader-interface)

if (NOT ENABLE_UNIT_TESTS)
    include("cmake/gcc-arm-none-eabi.cmake")
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

enable_language(C ASM)

add_subdirectory(lib/stm32_lib)
add_subdirectory(lib/usbd_lib)

add_library(${CMAKE_PROJECT_INTERFACE} INTERFACE)
target_include_directories(${CMAKE_PROJECT_INTERFACE} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/inc/usbd)

if (ENABLE_UNIT_TESTS)
    enable_language(CXX)
    add_compile_options(-fdata-sections -ffunction-sections)

    include(${CMAKE_CURRENT_SOURCE_DIR}/lib/unit_tests_lib/catch2/catch.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/lib/unit_tests_lib/approval/approval_tests.cmake)

    set(XML_ENDIANNESS "LITTLE")

    add_subdirectory(tests)
else ()
    set(CMAKE_PROJECT_SRC
        ${CMAKE_SOURCE_DIR}/src/gba_cart.c
        ${CMAKE_SOURCE_DIR}/src/nds_cart.c
        ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c
        ${CMAKE_SOURCE_DIR}/src/usart.c
        ${CMAKE_SOURCE_DIR}/src/util.c
        ${CMAKE_SOURCE_DIR}/src/main.c
        ${CMAKE_SOURCE_DIR}/src/usbd/host_interface.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usb_device.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_cdc_if.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_conf.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_desc.c
    )

    add_executable(${CMAKE_PROJECT_NAME})
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_SRC})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_INTERFACE} stm32_lib usbd_lib usbd_lib_interface)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)
    add_dependencies(${CMAKE_PROJECT_NAME} run_script)

    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
            COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
            COMMENT "Create ${CMAKE_PROJECT_NAME}.hex and ${CMAKE_PROJECT_NAME}.bin"
    )
endif ()