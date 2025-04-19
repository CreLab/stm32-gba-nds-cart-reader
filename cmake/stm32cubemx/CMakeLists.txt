cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)

find_package(Python3 REQUIRED)

add_custom_command(
		OUTPUT ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c
		COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/gen_keys.py ${CMAKE_SOURCE_DIR}
		COMMENT "Running script before build"
)

add_custom_target(run_script ALL DEPENDS ${CMAKE_SOURCE_DIR}/src/nds_cart_key.c)

# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_HAL_DRIVER 
	STM32F103xE
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/inc
)

# STM32CubeMX generated application sources
set(MX_Application_Src
	${CMAKE_SOURCE_DIR}/src/gba_cart.c
	${CMAKE_SOURCE_DIR}/src/host_interface.c
	${CMAKE_SOURCE_DIR}/src/main.c
	${CMAKE_SOURCE_DIR}/src/nds_cart.c
	${CMAKE_SOURCE_DIR}/src/nds_cart_key.c
	${CMAKE_SOURCE_DIR}/src/usart.c
	${CMAKE_SOURCE_DIR}/src/util.c
    ${CMAKE_SOURCE_DIR}/startup_stm32f103xe.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
		${CMAKE_SOURCE_DIR}/lib/src/Legacy/stm32f1xx_hal_can.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_cortex.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_dma.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_gpio.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_gpio_ex.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_pcd.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_pcd_ex.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_pwr.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_rcc.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_rcc_ex.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_tim.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_tim_ex.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_hal_uart.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_it.c
		${CMAKE_SOURCE_DIR}/lib/src/stm32f1xx_ll_usb.c
		${CMAKE_SOURCE_DIR}/lib/src/syscalls.c
		${CMAKE_SOURCE_DIR}/lib/src/sysmem.c
		${CMAKE_SOURCE_DIR}/lib/src/system_stm32f1xx.c
)

# Drivers Midllewares
set(USB_Device_Library_Src
		${CMAKE_SOURCE_DIR}/lib/src/usbd_cdc.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_cdc_if.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_conf.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_core.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_ctlreq.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_desc.c
		${CMAKE_SOURCE_DIR}/lib/src/usbd_ioreq.c
		${CMAKE_SOURCE_DIR}/lib/src/usb_device.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    USB_Device_Library
	
)

# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)
add_dependencies(STM32_Drivers run_script)

# Create USB_Device_Library static library
add_library(USB_Device_Library OBJECT)
target_sources(USB_Device_Library PRIVATE ${USB_Device_Library_Src})
target_link_libraries(USB_Device_Library PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
