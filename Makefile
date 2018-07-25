# Makefile for building embedded application.
# by Brian Fraser

SRC_C = camera.c sensor.c main.c

PUBDIR = $(HOME)/cmpt433/public
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -g 
# -pg for supporting gprof profiling.
#CFLAGS += -pg

all:  main

main:
	$(CC_C) $(CFLAGS) $(SRC_C) -o $(OUTDIR)/main -lpthread -lm
	cp *.c $(OUTDIR)/
		
	
clean:
	rm -f $(OUTDIR)/main