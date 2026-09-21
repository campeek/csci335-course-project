#!/bin/bash
set -e

if [ "$1" = "clean"]; then
    rm -rf build
    echo "build dir kill"
    exit 0
fi

cmake -S . -B build
cmake --build build -j$(nproc)
