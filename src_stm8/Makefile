#
# Makefile:
# email: egorplotkin@gmail.com
#
#       Copyright (c) 2019 Egor Plotkin

OUTDIR 	= bin

#Compiler
CC 		= sdcc

#Platform
PLATFORM = stm8

#Product name
PNAME 	= main

INCLUDE = -I./std_drv/inc \
		  -I./

SRC 	= \
		  ./stm8s_it.c \
		  ./std_drv/src/stm8s_adc1.c \
		  ./std_drv/src/stm8s_awu.c \
		  ./std_drv/src/stm8s_beep.c \
		  ./std_drv/src/stm8s_clk.c \
		  ./std_drv/src/stm8s_exti.c \
		  ./std_drv/src/stm8s_flash.c \
		  ./std_drv/src/stm8s_gpio.c \
		  ./std_drv/src/stm8s_i2c.c \
		  ./std_drv/src/stm8s_itc.c \
		  ./std_drv/src/stm8s_iwdg.c \
		  ./std_drv/src/stm8s_rst.c \
		  ./std_drv/src/stm8s_spi.c \
		  ./std_drv/src/stm8s_tim1.c \
		  ./std_drv/src/stm8s_tim2.c \
		  ./std_drv/src/stm8s_tim4.c \
		  ./std_drv/src/stm8s_uart1.c \
		  ./std_drv/src/stm8s_wwdg.c

CFLAGS 	= --std-c99 -DSTM8S103
MODEL	= -m$(PLATFORM)
LDLIBS 	= -l$(PLATFORM)

#In case of ever want a different name for the main source file
MAINSRC = $(PNAME).c

OBJ 	= $(SRC:.c=.rel)
BINS 	= $(SRC:.c=)
HEX 	= out_file

#
###############################################################
.PHONY: clean all tags depend directories build
.SUFFIXES: .c .rel

all: clean build

build: $(SRC) $(HEX)

$(HEX): directories $(OBJ) 
	@echo "build $@"
	@mkdir -p $(OUTDIR)
	@$(CC) $(LDLIBS) $(MODEL) $(INCLUDE) $(CFLAGS) $(MAINSRC) $(wildcard $(OUTDIR)/*.rel) -o $(OUTDIR)/

.c.rel: 
	@echo [CC] $<
	@mkdir -p $(OUTDIR)
	@$(CC) -c $(LDLIBS) $(MODEL) $(INCLUDE) $(CFLAGS) $< -o $(OUTDIR)/
#	@$(CC) -c $(INCLUDE) $(CFLAGS) $(LDLIBS) $< -o $(OUTDIR)/$(notdir $@)

clean:
	@echo "[Clean]"
	@rm -rf $(OUTDIR)
#	@rm -f $(OUTDIR)/$(OBJ) *~ core tags $(BINS)

tags: $(SRC)
	@echo [ctags]
	@ctags $(SRC)

depend:
	makedepend -Y $(SRC)

directories: $(OUTDIR)

$(OUTDIR):
	@echo "[Create out folder]"
#	@mkdir -p $(OUTDIR)

# DO NOT DELETE
###############################################################
