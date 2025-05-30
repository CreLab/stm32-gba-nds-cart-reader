#!/usr/bin/env python3

import serial
import sys

def char_conv(x):
    if x <= 0x20:
        return '.'
    if x >= 0x80:
        return '.'
    return chr(x)

def print_hex(x):
    while len(x) > 0:
        chunk_len = min(16, len(x))
        chunk_data = x[:chunk_len]
        # chunk_hex = ' '.join(['{0:02x}'.format(v) for v in chunk_data])
        # chunk_hex = chunk_hex.ljust(52)
        # chunk_ascii = ''.join([char_conv(v) for v in chunk_data])
        # print(chunk_hex + chunk_ascii)
        x = x[chunk_len:]

        binary_file.write(chunk_data)

ser = serial.Serial('COM8', baudrate=115200, timeout=1)

if not ser.isOpen():
    print("failed opening serial device")
    sys.exit(1)

def exec_cmd(cmd, hexdump=False):
    request = bytearray(cmd)

    # send command
    ser.write(request)
    ser.flush()

    # receiver reply header
    reply = ser.read(8)
    reply_len = reply[6] | (reply[7] << 8)
    reply_data = ser.read(reply_len)

    if hexdump:
        print_hex(reply_data)
    else:
        print("reply header:")
        print(reply)
        print("reply data:")

        print(reply_data)

# NDS init command
exec_cmd([0x57, 0x80, 0xB3, 0x00, 0x00, 0x00, 0x00, 0x00])

# NDS seek(0) command
exec_cmd([0x57, 0x80, 0xB0, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00])

# NDS size command
# exec_cmd([0x57, 0x80, 0x48, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00], hexdump=False)

with open("output.nds", "wb") as binary_file:
    for i in range(32768):
        # NDS read(4096) commad
        exec_cmd([0x57, 0x80, 0xB1, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x10], hexdump=True)
