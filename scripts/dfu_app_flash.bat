@echo off
setlocal enabledelayedexpansion

REM --- Konfiguration ---
set APP_BIN=%1
set APP_ADDR=0x08001000
set DFU=%~dp0..\tools\dfu-util\dfu-util.exe

if "%APP_BIN%"=="" (
    echo Usage: dfu_app_flash.bat firmware.bin
    exit /b 1
)

echo "Reboot device to DFU mode ..."
python.exe "%~dp0reboot_dfu_mode.py"

echo "Checking for DFU device..."
%DFU% -l

echo "Patch Firmware ..."
python.exe "%~dp0checksum.py" %APP_BIN%

echo "Flashing %APP_BIN% to %APP_ADDR% via DFU..."
%DFU% -s %APP_ADDR%:leave -D "%APP_BIN%"

if errorlevel 1 (
    echo "Flash failed."
    exit /b 1
)

echo "Flash successful."
exit /b 0
