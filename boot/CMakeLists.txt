cmake_minimum_required(VERSION 3.22)

if (NOT ENABLE_UNIT_TESTS)
    set(CMAKE_PROJECT_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/init.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/usb.c
    )

    add_library(${CMAKE_PROJECT_INTERFACE} INTERFACE)
    target_include_directories(${CMAKE_PROJECT_INTERFACE} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

    add_executable(${CMAKE_PROJECT_NAME})
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_SRC})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_INTERFACE})
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "-T${CMAKE_SOURCE_DIR}/STM32F103RCTx_BOOT.ld")
    add_dependencies(${CMAKE_PROJECT_NAME} run_script)

    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
            COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
            COMMENT "Create ${CMAKE_PROJECT_NAME}.hex and ${CMAKE_PROJECT_NAME}.bin"
    )
endif ()