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

# Zielarchitektur
set(TARGET_FLAGS "-mcpu=cortex-m3 -march=armv7-m -mthumb")

# Allgemeine Compiler-Warnungen und Standards
set(COMMON_C_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -std=c11")
set(COMMON_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics")

# Debug/Release-spezifische Flags
set(C_FLAGS_DEBUG "-O0 -g3")
set(C_FLAGS_RELEASE "-Os -g0")
set(CXX_FLAGS_DEBUG "-O0 -g3")
set(CXX_FLAGS_RELEASE "-Os -g0")

# ASM Flags
set(ASM_FLAGS "-x assembler-with-cpp -MMD -MP ${TARGET_FLAGS}")

# Linker-Script und Linker-Optionen
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103RCTx_FLASH.ld")
set(LINKER_FLAGS "-T${LINKER_SCRIPT} ${TARGET_FLAGS} --specs=nosys.specs")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group -Wl,--print-memory-usage")

# CMake-Variablen setzen
set(CMAKE_C_FLAGS "${TARGET_FLAGS} ${COMMON_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${TARGET_FLAGS} ${COMMON_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS "${ASM_FLAGS}")

set(CMAKE_C_FLAGS_DEBUG "${C_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_RELEASE "${C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS_RELEASE}")

set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}")
