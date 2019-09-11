#
# Makefile:
# email: egorplotkin@gmail.com
#
#       Copyright (c) 2019 Egor Plotkin

OUTDIR  = "bin"
DEBUG   = -O3
CC      = g++
INCLUDE = \
	-I./src/camera \
	-I./src/display \
	-I./src/display/spfd54124b \
	-I./src/gpioManip \
	-I./src/menue \
	-I./src/picture \
	-I./src
CFLAGS  = $(DEBUG) -std=c++17 -Wall $(INCLUDE) -Winline -pipe

LDFLAGS = -L/usr/local/lib
LDLIBS  = -lwiringPi -lwiringPiDev -lpthread -lm

# Should not alter anything below this line
###############################################################################

SRC = ./src/main.cpp \
	./src/display/display.cpp \
	./src/display/spfd54124b/spfd54124b.cpp \
	./src/gpioManip/gpio_manip.cpp \
	./src/picture/libbmp.cpp
OBJ     =       $(SRC:.c=.o)
BINS    =       $(SRC:.c=)

all:
#	@[ ! -d $(OUTDIR) ] && mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/DVR $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC)
#	@cat README.TXT
#	@echo "    $(BINS)" | fmt
#	@echo ""

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
