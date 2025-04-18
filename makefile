.PHONY: build all clean flash

# setup
PROJECT_NAME = stm32_cardridge_reader
MAIN_OUT = build
MAIN_OUT_ELF = $(MAIN_OUT)/$(PROJECT_NAME).elf
MAIN_OUT_BIN = $(MAIN_OUT)/$(PROJECT_NAME).bin
MAIN_OUT_MAP = $(MAIN_OUT)/$(PROJECT_NAME).map

COMPILE_OPTS = -mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -Wextra -pedantic -Wconversion -g -O2 -std=c11
INCLUDE_DIRS = -I include -I lib/inc
LIBRARY_DIRS = -L lib

CC = arm-none-eabi-gcc
CFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

CXX = arm-none-eabi-g++
CXXFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

AS = arm-none-eabi-gcc
ASFLAGS = $(COMPILE_OPTS) -c

LD = arm-none-eabi-gcc
LDFLAGS = $(COMPILE_OPTS) -Wl,--gc-sections,-Map=$(MAIN_OUT_MAP),-cref --specs=nosys.specs $(INCLUDE_DIRS) $(LIBRARY_DIRS) -T STM32F103RCTx_FLASH.ld

OBJCP = arm-none-eabi-objcopy
OBJCPFLAGS = -O binary

AR = arm-none-eabi-ar
ARFLAGS = cr

PROJECT_SRC_FILES = $(wildcard src/*.c)
LIB_SRC_FILES = $(wildcard lib/src/*.c)

KEY_FILE = $(MAIN_OUT)/nds_cart_key.o
OBJ_FILES = $(subst src,$(MAIN_OUT), $(PROJECT_SRC_FILES:.c=.o)) $(subst lib/src,$(MAIN_OUT), $(LIB_SRC_FILES:.c=.o)) build/startup_stm32f103xe.o
ELF_OBJ_FILES = $(OBJ_FILES) $(KEY_FILE)

build:
	mkdir -p build

# all
all: clean build $(KEY_FILE) $(MAIN_OUT_ELF) $(MAIN_OUT_BIN)

# main

$(KEY_FILE): bios/biosnds7.rom bios/biosdsi7.rom
	./scripts/gen_keys.sh | $(CC) $(CFLAGS) -x c -c -o $@ -

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: lib/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
build/%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@
	
$(MAIN_OUT_ELF): $(ELF_OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@

$(MAIN_OUT_BIN): $(MAIN_OUT_ELF)
	$(OBJCP) $(OBJCPFLAGS) $< $@

clean:
	rm -rf $(MAIN_OUT)

flash: $(MAIN_OUT_BIN)
	stm32flash -b 115200 -w $(MAIN_OUT_BIN) /dev/ttyUSB0
