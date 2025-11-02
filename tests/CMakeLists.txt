cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/cmake/add_unit_test/add_unit_test.cmake)

set(USB_LIB_SRC
        ${CMAKE_SOURCE_DIR}/src/gba_cart.c
        ${CMAKE_SOURCE_DIR}/src/nds_cart.c
        ${CMAKE_SOURCE_DIR}/src/usart.c
        ${CMAKE_SOURCE_DIR}/src/util.c
        ${CMAKE_SOURCE_DIR}/src/usbd/host_interface.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usb_device.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_cdc_if.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_conf.c
        ${CMAKE_SOURCE_DIR}/src/usbd/usbd_desc.c
)

add_library(stm32_data_mock OBJECT)
target_sources(stm32_data_mock PRIVATE stm32_data_mock.cpp)
target_include_directories(stm32_data_mock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(stm32_data_mock PRIVATE stm32_lib_interface ${CMAKE_PROJECT_INTERFACE})

add_unit_test(test_nintendo_cartridge_reader
        SOURCES nintendo_cartridge_reader_tests.cpp
        SOURCE_FILE ${USB_LIB_SRC}
        MOCKING_OBJECTS stm32_data_mock
        PREFIX "nintendo_cartridge_reader")

add_dependencies(test_nintendo_cartridge_reader run_script)
target_sources(test_nintendo_cartridge_reader PRIVATE ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c)

target_compile_options(test_nintendo_cartridge_reader PRIVATE -Wno-int-to-void-pointer-cast -Wno-int-to-pointer-cast)
target_link_libraries(test_nintendo_cartridge_reader PRIVATE stm32_lib_interface usbd_lib_interface usbd_lib_unit_test ${CMAKE_PROJECT_INTERFACE})
