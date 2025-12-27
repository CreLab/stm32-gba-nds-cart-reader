set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

message("Build Target OPTIONS")

set(COMMON_FLAGS "-mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -Wextra -Wconversion")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -c")

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103RCTx_FLASH.ld")
set(LINKER_MEM_USAGE "-Wl,--start-group -lc -lm -Wl,--end-group -Wl,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -Wl,--gc-sections,-Map=${PROJECT_NAME}.map,-cref --specs=nosys.specs -T ${LINKER_SCRIPT} ${LINKER_MEM_USAGE}" )

# Debug/Release-spezifische Flags
set(C_FLAGS_DEBUG "-O0 -g3")
set(C_FLAGS_RELEASE "-Os -g0")
set(CXX_FLAGS_DEBUG "-O0 -g3")
set(CXX_FLAGS_RELEASE "-Os -g0")

set(CMAKE_C_FLAGS_DEBUG "${C_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE "${C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS_RELEASE}")
