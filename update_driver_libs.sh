#!/bin/bash

# Konfiguration
REPO_CMSIS_URL="https://github.com/STMicroelectronics/cmsis-device-f1.git"
REPO_STM32_URL="https://github.com/STMicroelectronics/stm32f1xx-hal-driver.git"
REPO_USBD_URL="https://github.com/STMicroelectronics/stm32-mw-usb-device.git"
TEMP_DIR="temp_cube"
TARGET_STM32_LIB_DIR="lib/stm32_lib"
TARGET_USBD_LIB_DIR="lib/usbd_lib"

echo "Starte Aktualisierung der STM32F1 HAL Treiber..."

# 1. Temporäres Verzeichnis bereinigen
rm -rf $TEMP_DIR
mkdir -p $TEMP_DIR

# 2. Sparse Clone (lädt nur Metadaten, keine Dateien)
git clone --depth 1 --filter=blob:none --sparse $REPO_CMSIS_URL "$TEMP_DIR/cmsis_lib"
cd "$TEMP_DIR/cmsis_lib" && git sparse-checkout set Include && cd ../..

git clone --depth 1 --filter=blob:none --sparse $REPO_STM32_URL "$TEMP_DIR/stm32_lib"
cd "$TEMP_DIR/stm32_lib" && git sparse-checkout set Inc Src && cd ../..

git clone --depth 1 --filter=blob:none --sparse $REPO_USBD_URL "$TEMP_DIR/usbd_lib"
cd "$TEMP_DIR/usbd_lib" && git sparse-checkout set Core Class/CDC && cd ../..

echo "Kopiere neue Dateien in $TARGET_STM32_LIB_DIR and $TARGET_USBD_LIB_DIR..."

# 5. Dateien synchronisieren (Überschreiben der alten Versionen) Kopiert den HAL Treiber
cp -r $TEMP_DIR/cmsis_lib/Include/* "$TARGET_STM32_LIB_DIR/cmsis/inc"

cp -r $TEMP_DIR/stm32_lib/Inc/* "$TARGET_STM32_LIB_DIR/inc"
cp -r $TEMP_DIR/stm32_lib/Src/* "$TARGET_STM32_LIB_DIR/src"

cp -r $TEMP_DIR/usbd_lib/Core/Inc/* "$TARGET_USBD_LIB_DIR/inc"
cp -r $TEMP_DIR/usbd_lib/Core/Src/* "$TARGET_USBD_LIB_DIR/src"

cp -r $TEMP_DIR/usbd_lib/Class/CDC/Inc/* "$TARGET_USBD_LIB_DIR/inc"
cp -r $TEMP_DIR/usbd_lib/Class/CDC/Src/* "$TARGET_USBD_LIB_DIR/src"

#cp $TARGET_USBD_LIB_DIR/src/usbd_conf_template.c "$TARGET_USBD_LIB_DIR/src/usbd_conf.c"
#cp $TARGET_USBD_LIB_DIR/src/usbd_desc_template.c "$TARGET_USBD_LIB_DIR/src/usbd_desc.c"
#
#cp $TARGET_USBD_LIB_DIR/inc/usbd_conf_template.h "$TARGET_USBD_LIB_DIR/inc/usbd_conf.h"
#cp $TARGET_USBD_LIB_DIR/inc/usbd_desc_template.h "$TARGET_USBD_LIB_DIR/inc/usbd_desc.h"

sed -i 's/stm32fxxx.h/stm32f1xx.h/g' "$TARGET_USBD_LIB_DIR/inc/usbd_conf.h"

# 6. Aufräumen
rm -rf $TEMP_DIR/cmsis_lib
rm -rf $TEMP_DIR/stm32_lib
rm -rf $TEMP_DIR/usbd_lib

rm -rf $TARGET_STM32_LIB_DIR/inc/*template.h
rm -rf $TARGET_STM32_LIB_DIR/src/*template.c

rm -rf $TARGET_USBD_LIB_DIR/inc/*template.h
rm -rf $TARGET_USBD_LIB_DIR/src/*template.c

echo "Update abgeschlossen. Bitte prüfe deine 'stm32f1xx_hal_conf.h', da diese oft projektspezifisch ist."
