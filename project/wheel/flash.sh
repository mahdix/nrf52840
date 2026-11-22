#!/bin/bash
set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"

NRFUTIL="$HOME/dev/nrf52840/toolchain/tools/adafruit-nrfutil"
HEX="$PROJECT_DIR/build/hello_world.hex"
ZIP="$PROJECT_DIR/build/hello_world.zip"
PORT="/dev/cu.usbmodem1101"

echo "==> Creating DFU package"

"$NRFUTIL" dfu genpkg \
    --dev-type 0x0052 \
    --sd-req 0x00B6 \
    --application "$HEX" \
    "$ZIP"

echo "==> Flashing $PORT"

"$NRFUTIL" dfu serial \
    -pkg "$ZIP" \
    -p "$PORT" \
    -b 115200 \
    --singlebank

echo
echo "==> Flash complete."
