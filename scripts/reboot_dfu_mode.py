#!/usr/bin/env python3

import serial
import time
import sys
import usb.core
import usb.backend.libusb1
import os

# VID/PID DFU-Bootloader
DFU_VID = 0x0483
DFU_PID = 0xCA5D

ser = serial.Serial('COM5', baudrate=115200, timeout=1)
backend = usb.backend.libusb1.get_backend( find_library=lambda x: os.path.join(os.path.dirname(__file__), "libusb-1.0.dll") )

def exec_cmd(cmd):
    request = bytearray(cmd)

    # send command
    ser.write(request)
    ser.flush()

    # receiver reply header
    reply = ser.read(8)

    print("reply header:")
    print(reply)

def wait_for_dfu(timeout=10.0):
    print("Warte auf DFU-Device...")

    start = time.time()
    while time.time() - start < timeout:
        dev = usb.core.find(idVendor=DFU_VID, idProduct=DFU_PID, backend=backend)
        if dev is not None:
            print("DFU-Device erkannt!")
            return True
        time.sleep(0.2)

    print("Timeout: DFU-Device nicht gefunden.")
    return False

def main():
    if not wait_for_dfu():
        if not ser.isOpen():
            print("failed opening serial device")
            sys.exit(1)

        print("Sende Reboot-Befehl an Firmware...")
        # DFU mode command
        exec_cmd([0x57, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00])

        # Jetzt auf DFU warten
        if not wait_for_dfu():
            sys.exit(1)

if __name__ == "__main__":
    main()
