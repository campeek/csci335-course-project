#!/bin/bash
set -e

BUILD_TYPE="Release"

if [ "$1" = "clean" ]; then
    rm -rf build
    echo "build dir kill"
    exit 0
fi

if [ "$1" = "debug" ]; then
    BUILD_TYPE="Debug"
fi

echo "building SIC/XE assembler [$BUILD_TYPE]..."

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ln -sf build/compile_commands.json compile_commands.json

cmake --build build -j$(nproc)

echo "built :))))"
