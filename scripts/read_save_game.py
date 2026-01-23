#!/usr/bin/env python3

import serial
import sys

def dump_data(f, x):
    while len(x) > 0:
        chunk_len = min(16, len(x))
        chunk_data = x[:chunk_len]
        x = x[chunk_len:]

        f.write(chunk_data)

def exec_cmd(cmd):
    ser.write(cmd)
    ser.flush()

    reply = ser.read(8)
    reply_len = reply[6] | (reply[7] << 8)

    return ser.read(reply_len)

ser = serial.Serial('COM5', baudrate=115200, timeout=1)

if __name__ == "__main__":

    if not ser.isOpen():
        print("failed opening serial device")
        sys.exit(1)

    seek_cmd = bytearray([0x57, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00])
    data = exec_cmd(seek_cmd)
    print(data)

    seek_cmd = bytearray([0x57, 0x80, 0xC1, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00])
    data = exec_cmd(seek_cmd)

    with open("game_data.sav", "wb") as binary_file:
        for i in range(128):
            cmd = bytearray([0x57, 0x80, 0xC2, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x10])
            data = exec_cmd(cmd)
            dump_data(binary_file, data)
