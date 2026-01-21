#!/bin/bash

# Stop on unset variables
set -u

if [ $# -eq 0 ]; then
    echo "Usage: ./build.sh [filename without extension]"
    echo "Example: ./build.sh 01"
    exit 1
fi

FILENAME="$1"

echo "Compiling ${FILENAME}.c..."

gcc \
    -g -O0 -Wall -Wextra \
    -o "${FILENAME}" \
    "${FILENAME}.c" \
    raylib/lib/linux_amd64/libraylib.a \
    -lm -lpthread -ldl 

if [ $? -eq 0 ]; then
    echo
    echo "Compilation successful! Running ${FILENAME}..."
    echo
    ./"${FILENAME}"
else
    ERRORLEVEL=$?
    echo
    echo "Compilation failed with error code ${ERRORLEVEL}"
    exit ${ERRORLEVEL}
fi
