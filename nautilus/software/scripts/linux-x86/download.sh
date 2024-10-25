#!/bin/bash

# Download a file to one of the FEC-Linux boards
# Author: Per Thomas Hille, Embedded Consulting AS for Semcon Devotek
# email:  pth@embc.no


base_addr=192.168.1
hostname=imx

declare -A fec_boards

indexes="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20"


for index in $indexes; do
    if [ $index -lt 10 ]; then
        fec_boards+=( ["fec$index"]=$base_addr$".10$index" )
    else
        fec_boards+=( ["fec$index"]=$base_addr$".1$index" )
    fi
done


function usage
{
    echo "Usage:    $0 [fec]  [file]"
    echo "Example:  $0 fec4  helloworld.txt  (downloads the file \"hellowordl.txt\" to fec4)"
}


if [ $1 == '--help' ]; then
    usage
    exit 0
fi

if [ "$#" -ne 2 ]; then
    echo "illegal number of parameters, expected 2 parameters, recieved " $# 
    usage
    printf "fec can be one of the following"
    for board in "${!fec_boards[@]}"; do
        printf "%s " "$board"
    done
    printf "\n"
    exit 1
fi


scp  $2 imx@${fec_boards["$1"]}:

    
