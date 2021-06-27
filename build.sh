#!/bin/bash

if [[ ! -d "build" ]]; then
    echo no build
    mkdir build
fi

if [[ ! -d "bin" ]]; then
    echo no bin
    mkdir bin
fi

gcc -c -o build/util.o util.c
gcc -c -o build/main.o main.c

gcc -o bin/plexability build/util.o build/main.o
