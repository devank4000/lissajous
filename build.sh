#!/bin/sh

gcc -ggdb -Wall -Wextra -Wpedantic -o main main.c ffmpeg_linux.c -lm
