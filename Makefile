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

SRC = ./src/main.cpp \
	./src/display/display.cpp \
	./src/display/spfd54124b/spfd54124b.cpp \
	./src/gpioManip/gpio_manip.cpp \
	./src/picture/libbmp.cpp
OBJ     =       $(SRC:.cpp=.o)
BINS    =       $(SRC:.cpp=)
EXECUTABLE = DVR_EXEC

# Should not alter anything below this line
###############################################################################


all: $(SRC) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@echo "build $@"
	@$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $@

.cpp.o:
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
