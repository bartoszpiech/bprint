#!/bin/sh

CC=gcc
CFLAGS="-Wall -pedantic -std=c11 -g"
INC=bprint.c
OBJ=bprint.o
OBJS="bprint.o bstring.o"
SRC=bprint_tests.c
BIN=tests

$CC $CFLAGS -c $INC -o $OBJ && $CC $CFLAGS $SRC $OBJS -o $BIN && ./$BIN
