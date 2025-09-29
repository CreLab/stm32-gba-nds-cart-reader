cmake_minimum_required(VERSION 3.22)

enable_language(C ASM)

set(USB_LIB_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_cdc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_core.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_ctlreq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usbd_ioreq.c
)

add_library(usbd_lib_interface INTERFACE)
target_include_directories(usbd_lib_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_definitions(usbd_lib_interface INTERFACE
        $<$<CONFIG:Debug>:DEBUG>)

add_library(usbd_lib_unit_test OBJECT)
target_sources(usbd_lib_unit_test PRIVATE ${USB_LIB_SRC})
target_link_libraries(usbd_lib_unit_test PRIVATE usbd_lib_interface stm32_lib_interface)

add_library(usbd_lib OBJECT)
target_sources(usbd_lib PRIVATE ${USB_LIB_SRC})
target_link_libraries(usbd_lib PRIVATE usbd_lib_interface stm32_lib)
