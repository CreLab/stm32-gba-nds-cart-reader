cmake_minimum_required(VERSION 3.22)

set(STM32_LIB_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Legacy/stm32f1xx_hal_can.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_cortex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_dma.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_gpio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_gpio_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pcd.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pcd_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_pwr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rcc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_rcc_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_tim.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_tim_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_hal_uart.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f1xx_ll_usb.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/syscalls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sysmem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/system_stm32f1xx.c
)

add_library(stm32_lib_interface INTERFACE)
target_include_directories(stm32_lib_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_definitions(stm32_lib_interface INTERFACE
        USE_HAL_DRIVER
        STM32F103xE
        $<$<CONFIG:Debug>:DEBUG>)

add_library(stm32_lib OBJECT)
target_sources(stm32_lib PRIVATE ${STM32_LIB_SRC})
target_link_libraries(stm32_lib PUBLIC stm32_lib_interface)
target_compile_options(stm32_lib PRIVATE -Wno-int-to-void-pointer-cast -Wno-int-to-pointer-cast)

