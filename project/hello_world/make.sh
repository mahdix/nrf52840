#!/bin/bash
set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"

TOOLCHAIN="$HOME/dev/nrf52840/toolchain"
ARM_GCC="/Volumes/Data/bin/arm-gnu-toolchain/arm-gnu-toolchain-15.3.rel1-darwin-arm64-arm-none-eabi/bin"

BUILD="$PROJECT_DIR/build"

CC="$ARM_GCC/arm-none-eabi-gcc"
CXX="$ARM_GCC/arm-none-eabi-g++"
OBJCOPY="$ARM_GCC/arm-none-eabi-objcopy"
SIZE="$ARM_GCC/arm-none-eabi-size"

mkdir -p "$BUILD"

CFLAGS=(
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
    -Os
    -DNRF52840_XXAA
    -I"$TOOLCHAIN/include"
    -I"$TOOLCHAIN/cmsis/CMSIS/Core/Include"
    -I"$TOOLCHAIN/nordic/nrfx/mdk"
)

LDFLAGS=(
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    "-T$TOOLCHAIN/linker/nrf52840_s140_v6.ld"
    -Wl,--gc-sections
    "-Wl,-L$TOOLCHAIN/linker"
    "-Wl,-Map=$BUILD/hello_world.map"
    --specs=nano.specs
    --specs=nosys.specs
)

echo "==> Compiling main.cpp"
"$CXX" "${CFLAGS[@]}" \
    -c "$PROJECT_DIR/main.cpp" \
    -o "$BUILD/main.o"

echo "==> Compiling system_nrf52840.c"
"$CC" "${CFLAGS[@]}" \
    -c "$TOOLCHAIN/nordic/nrfx/mdk/system_nrf52840.c" \
    -o "$BUILD/system_nrf52840.o"

echo "==> Compiling startup code"
"$CC" "${CFLAGS[@]}" \
    -c "$TOOLCHAIN/src/gcc_startup_nrf52840.S" \
    -o "$BUILD/gcc_startup_nrf52840.o"

echo "==> Linking"
"$CXX" \
    "$BUILD/main.o" \
    "$BUILD/system_nrf52840.o" \
    "$BUILD/gcc_startup_nrf52840.o" \
    "${LDFLAGS[@]}" \
    -o "$BUILD/hello_world.elf"

echo "==> Creating HEX"
"$OBJCOPY" \
    -O ihex \
    "$BUILD/hello_world.elf" \
    "$BUILD/hello_world.hex"

echo "==> Firmware size"
"$SIZE" "$BUILD/hello_world.elf"

echo
echo "Build complete:"
echo "  $BUILD/hello_world.elf"
echo "  $BUILD/hello_world.hex"
