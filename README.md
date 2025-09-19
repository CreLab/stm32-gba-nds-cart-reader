# STM32 GBA/NDS Cartridge Reader (Refactored Fork)

This project is a refactored fork of [ipatix/stm32-gba-nds-cart-reader](https://github.com/ipatix/stm32-gba-nds-cart-reader),
built upon the original hardware design by ipatix. The corresponding PCB files and hardware
documentation can be found in the related repository:
[ipatix/stm32-gba-nds-cart-reader-pcb](https://github.com/ipatix/stm32-gba-nds-cart-reader-pcb).

## Refactoring Overview

The original codebase has undergone a comprehensive refactoring process:

- Unused or irrelevant lines have been removed to improve readability and maintainability.
- Existing structures were re-evaluated and either optimized or reinterpreted for better
  performance and clarity.
- The result is a cleaner, more modular codebase that retains full compatibility with the original
  hardware.

## Documentation

The `doc/` directory contains a Markdown snapshot of the Nintendo cartridge documentation originally
hosted at [problemkaputt.de](https://www.problemkaputt.de/gbatek.htm).

This documentation covers technical details for various Nintendo handheld systems:

- [Game Boy Advance (GBA)](./doc/gbareference.md)
- [Nintendo DS (NDS)](./doc/ndsreference.md)
- [Nintendo DSi (DSi)](./doc/dsireference.md)
- [Nintendo 3DS (3DS)](./doc/3dsreference.md)
- [CPU Technical Info](./doc/armcpureference.md)

Please note:
- The Markdown version is a static snapshot and may not reflect the latest updates.
- To fetch a newer version of the documentation, you can run the included script: 
  `update_gbatek_docu.sh`.

## Purpose

This project aims to provide a streamlined and maintainable software interface for reading data from
Nintendo cartridges using STM32 microcontrollers. It is ideal for developers, modders and hardware
enthusiasts who want to interact with GBA/NDS/DSi/3DS cartridges at a low level.

## Repository Structure

```
├── cmake/           # CMake directory for code generation
├── doc/             # Markdown snapshot documentation (GBAtek)
├── inc/             # Refactored header files
├── lib/             # Libraries for STM32
├── scripts/         # Utility scripts
├── src/             # Refactored source files
├── tests/           # Approval and unit tests
├── CMakeLists.txt   # Main cmake file
├── LICENSE.md       # License information
└── README.txt       # This file
```

## Requirements

- STM32 microcontroller (compatible with ipatix's PCB design)
- UART interface for flashing firmware
- Cartridge headers (GBA/NDS) – may require sourcing from third-party vendors

## Getting Started

1. Clone the repository.
2. Flash the firmware to your STM32 using `stm32flash` and the serial interface.
3. Connect your cartridge and begin communication using the provided software tools.

## License

- Code: GNU General Public License v3.0 (see LICENSE)
- Documentation: Creative Commons Attribution-ShareAlike 4.0 (see LICENSE_DOCS)

This project is a refactored fork of ipatix/stm32-gba-nds-cart-reader. The original repository
did not specify a license. All modifications and additions are released under the terms above.

## Credits

- Original hardware and software design by [ipatix](https://github.com/ipatix)
- Refactoring and documentation snapshot by [CreLab](https://github.com/crelab)

---

For questions, improvements, or bug reports, feel free to open an issue or contribute via pull
request.
