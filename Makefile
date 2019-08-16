#
# Makefile:
# email: egorplotkin@gmail.com
#
#       Copyright (c) 2019 Egor Plotkin

DEBUG   = -O3
CC      = g++
INCLUDE = -I/usr/local/include \
                                        -I./src/display \
                                        -I./src/display/spfd54124b \
                                        -I./src/gpioManip \
                                        -I./src
CFLAGS  = $(DEBUG) -std=c++14 -Wall $(INCLUDE) -Winline -pipe

LDFLAGS = -L/usr/local/lib
LDLIBS  = -lwiringPi -lwiringPiDev -lpthread -lm

# Should not alter anything below this line
###############################################################################

#SRC    =       lcd_test1.cpp
SRC = ./src/lcd_test1.cpp \
                        ./src/display/display.cpp \
                        ./src/spfd54124b/spfd54124b.cpp \
                        ./gpioManip/gpio_manip.cpp

OBJ     =       $(SRC:.c=.o)

BINS    =       $(SRC:.c=)

all:
        @cat README.TXT
        @echo "    $(BINS)" | fmt
        @echo ""

really-all:     $(BINS)

lcd_test1:      lcd_test1.o
        @echo [link]
        @$(CC) -o $@ lcd_test1.o $(LDFLAGS) $(LDLIBS)

.c.o:
        @echo [CC] $<
        @$(CC) -c $(CFLAGS) $< -o $@

clean:
        @echo "[Clean]"
        @rm -f $(OBJ) *~ core tags $(BINS)

tags:   $(SRC)
        @echo [ctags]
        @ctags $(SRC)

depend:
        makedepend -Y $(SRC)

# DO NOT DELETE
