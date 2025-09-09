#!/bin/bash
echo "installing compiler and debugger.."
sudo apt update

echo "Installing ARM toolchain and utilities..."
sudo apt install -y gcc-arm-none-eabi gdb-arm-none-eabi make cmake openocd
