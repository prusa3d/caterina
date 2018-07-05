# Caterina

## Building under Windows
Use Atmel provided GCC based tool chain: https://github.com/eerimoq/avr-toolchain-windows
run make

## Building under Linux
No success yet, avr-gcc shipped with e.g. Debian doesn't optimize enough to fit resulting bootloader into flash.