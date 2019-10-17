#
# Makefile:
# email: egorplotkin@gmail.com
#
#       Copyright (c) 2019 Egor Plotkin

OUTDIR 	= "bin"

#Compiler
CC 		= sdcc

#Platform
PLATFORM = stm8

#Product name
PNAME 	= main

INCLUDE = \
		  -I./std_drv/inc \
		  -I./

SRC 	= ./main.c \
		  ./stm8s_it.c

OPTIM 	= --opt-code-size
LINKER 	= --out-fmt-ihx 

CFLAGS 	= --std-c99 -m$(PLATFORM) $(OPTIM)
LDLIBS 	= -l$(PLATFORM)

#In case of ever want a different name for the main source file
MAINSRC = $(PNAME).c

OBJ 	= $(SRC:.c=.rel)
BINS 	= $(SRC:.c=)
HEX 	= $(OUTDIR)/

#
###############################################################
.PHONY: clean all tags depend directories build
.SUFFIXES: .c .rel

all: clean build

build: $(SRC) $(HEX)

$(HEX): directories $(OBJ) 
	@echo "build $@"
	@$(CC) $(INCLUDE) $(CFLAGS) $(LDLIBS) $(MAINSRC) $(wildcard $(OUTDIR)/*.rel) -o $(OUTDIR)/

.c.rel: 
	@echo [CC] $<
	@$(CC) -c $(INCLUDE) $(CFLAGS) $(LDLIBS) $< -o $(OUTDIR)/$@

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
	mkdir -p $(OUTDIR)

# DO NOT DELETE
###############################################################
