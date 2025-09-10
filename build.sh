#!/bin/bash

APP="maicra"

SRC="src/main.c src/core/*.c src/graphics/*.c src/game/*.c src/math/*.c"

echo "Compiling $SRC ..."
gcc $SRC -o $APP -I./vendor/ -lglfw -lGLEW -lGL -lm

if [ $? -eq 0 ]; then
    echo "Compilation succesful."
    echo "Running..."
    ./maicra
else
    echo "Error in compilation."
fi
