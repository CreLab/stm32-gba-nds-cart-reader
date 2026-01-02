# DFU Bootloader for STM32 GBA/NDS Cartridge Reader

This repository contains a lightweight DFU (Device Firmware Upgrade) bootloader designed for the STM32‑based **GBA/NDS Cartridge Reader** project.  
The bootloader occupies **4 KB of flash memory**, starting at the fixed address **0x08000000**, and provides a simple and reliable mechanism for updating and loading the main firmware.

This DFU bootloader is a **refactored version of the original** [davidgfnet/stm32-dfu-bootloader](https://github.com/davidgfnet/stm32-dfu-bootloader) and has been adapted specifically
to improve the debugging workflow.

---

## Overview

The DFU bootloader enables firmware flashing directly over USB without requiring the STM32CubeProgrammer software.  
This makes development and debugging significantly smoother—especially when working with IDEs like **CLion**, where firmware can be rebuilt and uploaded automatically.

The bootloader is always the first code executed after reset. It checks whether a new firmware image should be flashed or whether it should jump to the existing application firmware.

---

## Memory Layout

The bootloader is intentionally compact and occupies only the first **4 KB** of flash:

| Region            | Start Address | Size     | Description                          |
|-------------------|---------------|----------|--------------------------------------|
| Bootloader        | 0x08000000    | 4 KB     | DFU bootloader                       |
| Application FW    | 0x08001000    | remaining flash | Main firmware for the cartridge reader |

The application firmware must be linked to start at **0x08001000** to avoid overlapping with the bootloader.

---

## Features

- USB DFU support for flashing new firmware
- Automatic jump to application firmware after boot
- Safe firmware update mechanism
- No external flashing tools required
- Compatible with CLion and other modern development environments
- Minimal flash footprint (4 KB)

---

## Usage

### Flashing the Bootloader (one‑time setup)
The bootloader must be flashed once using STM32CubeProgrammer software via UART.  
After that, all firmware updates can be performed via USB DFU.

### Flashing Application Firmware
Once the bootloader is installed:

1. Connect the device via USB
2. Enter DFU mode (depending on your hardware trigger)
3. Flash the application firmware using dfu_app_flash.bat script
