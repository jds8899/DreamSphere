#!/bin/bash

input=$1
output=$2

if [[ -z $input ]] || [[ -z $output ]]; then
    echo usage: ds_1st_read.sh inputfile outputfile
    exit 1
fi

sh-elf-objcopy -R .stack -O binary $input output.bin
$KOS_BASE/utils/scramble/scramble output.bin $output

rm output.bin

exit 0
