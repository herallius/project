#
#     sudo apt-get install libv4l-dev
#     sudo apt-get install v4l-utils
#     sudo apt-get install imagemagick
#
#     cd /usr/lib/arm-linux-gnueabihf
#     cp lv4l2.so lv4lconvert.so ljpeg.so /mnt/remote
#
#
#
#

CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
LFLAGS = -L$(HOME)/cmpt433/public/
OUTFILE = main
OUTDIR = $(HOME)/cmpt433/public/

SRC = cam_test.c

OBJ = $(addsuffix .o, $(basename $(SRC)))

all: main
# Copy wave files to the shared folder
main:
	$(CC_C) $(CFLAGS) $(SRC) -o $(OUTFILE) -lpthread $(LFLAGS) -lv4l2 -lv4lconvert -ljpeg

	cp $(OUTFILE) $(OUTDIR)

%.o: %c
	$(CC_C) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OUTDIR)/$(OUTFILE)
