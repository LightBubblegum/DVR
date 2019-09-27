#
# Makefile:
# email: egorplotkin@gmail.com
#
#       Copyright (c) 2019 Egor Plotkin

STACK_SIZE = 256

OUTDIR = "bin"
CC = sdcc
INCLUDE = \
		  -I./std_drv/inc \
		  -I./
OPTIM = --opt-code-size
LINKER = --out-fmt-ihx --out-fmt-elf --stack-loc $(STACK_SIZE)

CFLAGS = --srd-c99 $(OPTIM) $(LINKER) $(INCLUDE)

LDLIBS = -lstm8 -mstm8
SRC = ./main.c \
	  ./stm8s_it.c \
	  ./std_drv/src/stm8s_adc1.c \
	  ./std_drv/src/stm8s_adc2.c \
	  ./std_drv/src/stm8s_awuc \
	  ./std_drv/src/stm8s_beep.c \
	  ./std_drv/src/stm8s_can.c \
	  ./std_drv/src/stm8s_clk.c \
	  ./std_drv/src/stm8s_exti.c \
	  ./std_drv/src/stm8s_flash.c  \
	  ./std_drv/src/stm8s_gpio.c  \
	  ./std_drv/src/stm8s_i2c.c  \
	  ./std_drv/src/stm8s_itc.c  \
	  ./std_drv/src/stm8s_iwdg.c  \
	  ./std_drv/src/stm8s_rst.c  \
	  ./std_drv/src/stm8s_spi.c  \
	  ./std_drv/src/stm8s_tim1.c  \
	  ./std_drv/src/stm8s_tim2.c  \
	  ./std_drv/src/stm8s_tim3.c  \
	  ./std_drv/src/stm8s_tim4.c  \
 	  ./std_drv/src/stm8s_tim5.c  \
	  ./std_drv/src/stm8s_tim6.c  \
	  ./std_drv/src/stm8s_uart1.c  \
	  ./std_drv/src/stm8s_uart2.c  \
	  ./std_drv/src/stm8s_uart3.c  \
	  ./std_drv/src/stm8s_uart4.c  \
	  ./std_drv/src/stm8s_wwdg.c


