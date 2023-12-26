#!/bin/sh

set -xe
gcc \
	-Wall -Wextra -pedantic \
	-fno-stack-protector \
	-nostdlib \
	start.S main.c
