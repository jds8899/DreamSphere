#!/bin/bash

sh-elf-objcopy -R .stack -O binary dream_sphere.elf output.bin
/opt/toolchains/dc/kos/utils/scramble/scramble output.bin 1st_read.bin
