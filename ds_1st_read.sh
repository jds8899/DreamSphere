#!/bin/bash

input=$1

if [[ -z $input ]]; then
    echo usage: ds_1st_read.sh inputfile
    exit 1
fi

sh-elf-objcopy -R .stack -O binary $input output.bin
$KOS_BASE/utils/scramble/scramble output.bin 1st_read.bin

rm output.bin

exit 0
