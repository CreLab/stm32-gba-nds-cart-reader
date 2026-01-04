#!/usr/bin/env python3

import serial
import sys

def char_conv(x):
    if x <= 0x20:
        return '.'
    if x >= 0x80:
        return '.'
    return chr(x)

def get_data(addr, size, name, hexdump=True):

    addr_bytes = bytearray(addr)
    size_bytes = size.to_bytes(2, byteorder="little")

    init_cmd = bytearray([0x57, 0x80, 0xB3, 0x00, 0x00, 0x00, 0x00, 0x00])
    seek_cmd = bytearray([0x57, 0x80, 0xB0, 0x00, 0x00, 0x00, 0x04, 0x00])
    get_cmd = bytearray([0x57, 0x80, 0xB1, 0x00, 0x01, 0x00, 0x02, 0x00])

    exec_cmd(init_cmd)
    exec_cmd(seek_cmd + addr_bytes)
    reply_data = exec_cmd(get_cmd + size_bytes)

    print(name)
    if hexdump:
        print_hex(reply_data)
    else:
        print_ascii(reply_data)

def print_hex(x):
    while len(x) > 0:
        chunk_len = min(32, len(x))
        chunk_data = x[:chunk_len]
        chunk_hex = ' '.join(['{0:02x}'.format(v) for v in chunk_data])
        chunk_hex = chunk_hex.ljust(52)
        print(chunk_hex)
        x = x[chunk_len:]

def print_ascii(x):
    while len(x) > 0:
        chunk_len = min(32, len(x))
        chunk_data = x[:chunk_len]
        chunk_ascii = ''.join([char_conv(v) for v in chunk_data])
        print(chunk_ascii)
        x = x[chunk_len:]

def exec_cmd(cmd):
    # send command
    ser.write(cmd)
    ser.flush()

    # receiver reply header
    reply = ser.read(8)
    reply_len = reply[6] | (reply[7] << 8)

    return ser.read(reply_len)

ser = serial.Serial('COM5', baudrate=115200, timeout=1)

if __name__ == "__main__":

    if not ser.isOpen():
        print("failed opening serial device")
        sys.exit(1)

    get_data([0x00, 0x00, 0x00, 0x00], 12,   "Game Title  (Uppercase ASCII, padded with 00h)                 :", False)
    get_data([0x0C, 0x00, 0x00, 0x00], 4,    "Gamecode    (Uppercase ASCII, NTR-<code>)        (0=homebrew)  :", False)
    get_data([0x10, 0x00, 0x00, 0x00], 2,    "Makercode   (Uppercase ASCII, eg. \"01\"=Nintendo) (0=homebrew):", False)
    get_data([0x12, 0x00, 0x00, 0x00], 1,    "Unitcode    (00h=NDS, 02h=NDS+DSi, 03h=DSi) (bit1=DSi)         :")
    get_data([0x13, 0x00, 0x00, 0x00], 1,    "Encryption Seed Select (00..07h, usually 00h)                  :")
    get_data([0x14, 0x00, 0x00, 0x00], 1,    "Devicecapacity         (Chipsize = 128KB SHL nn) (eg. 7 = 16MB):")
    get_data([0x15, 0x00, 0x00, 0x00], 7,    "Reserved    (zero filled)                                      :")
    get_data([0x1C, 0x00, 0x00, 0x00], 1,    "Reserved    (zero)                      (except, used on DSi)  :")
    get_data([0x1D, 0x00, 0x00, 0x00], 1,    "NDS Region  (00h=Normal, 80h=China, 40h=Korea) (other on DSi)  :")
    get_data([0x1E, 0x00, 0x00, 0x00], 1,    "ROM Version (usually 00h)                                      :")
    get_data([0x1F, 0x00, 0x00, 0x00], 1,    "Autostart (Bit2: Skip \"Press Button\" after Health and Safety):")
    get_data([0x20, 0x00, 0x00, 0x00], 4,    "ARM9 rom_offset    (4000h and up, align 1000h)                 :")
    get_data([0x24, 0x00, 0x00, 0x00], 4,    "ARM9 entry_address (2000000h..23BFE00h)                        :")
    get_data([0x28, 0x00, 0x00, 0x00], 4,    "ARM9 ram_address   (2000000h..23BFE00h)                        :")
    get_data([0x2C, 0x00, 0x00, 0x00], 4,    "ARM9 size          (max 3BFE00h) (3839.5KB)                    :")
    get_data([0x30, 0x00, 0x00, 0x00], 4,    "ARM7 rom_offset    (8000h and up)                              :")
    get_data([0x34, 0x00, 0x00, 0x00], 4,    "ARM7 entry_address (2000000h..23BFE00h, or 37F8000h..3807E00h) :")
    get_data([0x38, 0x00, 0x00, 0x00], 4,    "ARM7 ram_address   (2000000h..23BFE00h, or 37F8000h..3807E00h) :")
    get_data([0x3C, 0x00, 0x00, 0x00], 4,    "ARM7 size          (max 3BFE00h, or FE00h) (3839.5KB, 63.5KB)  :")
    get_data([0x40, 0x00, 0x00, 0x00], 4,    "File Name Table (FNT) offset                                   :")
    get_data([0x44, 0x00, 0x00, 0x00], 4,    "File Name Table (FNT) size                                     :")
    get_data([0x48, 0x00, 0x00, 0x00], 4,    "File Allocation Table (FAT) offset                             :")
    get_data([0x4C, 0x00, 0x00, 0x00], 4,    "File Allocation Table (FAT) size                               :")
    get_data([0x50, 0x00, 0x00, 0x00], 4,    "File ARM9 overlay_offset                                       :")
    get_data([0x54, 0x00, 0x00, 0x00], 4,    "File ARM9 overlay_size                                         :")
    get_data([0x58, 0x00, 0x00, 0x00], 4,    "File ARM7 overlay_offset                                       :")
    get_data([0x5C, 0x00, 0x00, 0x00], 4,    "File ARM7 overlay_size                                         :")
    get_data([0x60, 0x00, 0x00, 0x00], 4,    "Port 40001A4h setting for normal commands (usually 00586000h)  :")
    get_data([0x64, 0x00, 0x00, 0x00], 4,    "Port 40001A4h setting for KEY1 commands   (usually 001808F8h)  :")
    get_data([0x68, 0x00, 0x00, 0x00], 4,    "Icon/Title offset (0=None) (8000h and up)                      :")
    get_data([0x6C, 0x00, 0x00, 0x00], 2,    "Secure Area Checksum, CRC-16 of [[020h]..00007FFFh]            :")
    get_data([0x6E, 0x00, 0x00, 0x00], 2,    "Secure Area Delay (in 131kHz units) (051Eh=10ms or 0D7Eh=26ms) :")
    get_data([0x70, 0x00, 0x00, 0x00], 4,    "ARM9 Auto Load List Hook RAM Address (?) ;\endaddr of auto-load:")
    get_data([0x74, 0x00, 0x00, 0x00], 4,    "ARM7 Auto Load List Hook RAM Address (?) ;/functions           :")
    get_data([0x78, 0x00, 0x00, 0x00], 8,    "Secure Area Disable (by encrypted \"NmMdOnly\") (usually zero) :")
    get_data([0x80, 0x00, 0x00, 0x00], 4,    "Total Used ROM size (remaining/unused bytes usually FFh-padded):")
    get_data([0x84, 0x00, 0x00, 0x00], 4,    "ROM Header Size (4000h)                                        :")
    get_data([0x88, 0x00, 0x00, 0x00], 4,    "Unknown, some rom_offset, or zero? (DSi: slightly different)   :")
    get_data([0x8C, 0x00, 0x00, 0x00], 8,    "Reserved (zero filled; except, [88h..93h] used on DSi)         :")
    get_data([0x94, 0x00, 0x00, 0x00], 2,    "NAND end of ROM area  ;\in 20000h-byte units (DSi: 80000h-byte):")
    get_data([0x96, 0x00, 0x00, 0x00], 2,    "NAND start of RW area ;/usually both same address (0=None)     :")
    get_data([0x98, 0x00, 0x00, 0x00], 24,   "Reserved (zero filled)                                         :")
    get_data([0xB0, 0x00, 0x00, 0x00], 16,   "Reserved (zero filled; or \"DoNotZeroFillMem\"=unlaunch fastboot):")
    get_data([0xC0, 0x00, 0x00, 0x00], 156,  "Nintendo Logo (compressed bitmap, same as in GBA Headers)      :", False)
    get_data([0x5C, 0x01, 0x00, 0x00], 2,    "Nintendo Logo Checksum, CRC-16 of [0C0h-15Bh], fixed CF56h     :")
    get_data([0x5E, 0x01, 0x00, 0x00], 2,    "Header Checksum, CRC-16 of [000h-15Dh]                         :")
    get_data([0x60, 0x01, 0x00, 0x00], 4,    "Debug rom_offset   (0=none) (8000h and up)       ;only if debug:")
    get_data([0x64, 0x01, 0x00, 0x00], 4,    "Debug size         (0=none) (max 3BFE00h)        ;version with :")
    get_data([0x68, 0x01, 0x00, 0x00], 4,    "Debug ram_address  (0=none) (2400000h..27BFE00h) ;SIO and 8MB  :")
    get_data([0x6C, 0x01, 0x00, 0x00], 4,    "Reserved (zero filled) (transferred, and stored, but not used) :")
    get_data([0x70, 0x01, 0x00, 0x00], 144,  "Reserved (zero filled) (transferred, but not stored in RAM)    :")
    get_data([0x00, 0x02, 0x00, 0x00], 3584, "Reserved (zero filled) (usually not transferred)               :")
