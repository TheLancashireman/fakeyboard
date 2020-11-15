#	Makefile - Makefile for Fakeyboard
#
#	Copyright David Haworth
#
#	This file is part of Fakeyboard.
#
#	Fakeyboard is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	Fakeyboard is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with Fakeyboard.  If not, see <http://www.gnu.org/licenses/>.

#	Usage:
#		make [BOARD=blue-pill] [IMAGE=/path/to/image] [DV_ROOT=</path/to/davros>] [DV_GNU_D=</path/to/gcc>]
#	Alternatively, you can set BOARD, IMAGE, DV_ROOT and DV_GNU_D as environment variables.
#
#	Targets:
#		clean: removes all object and binary files
#		default: compiles and links
#		image: objcopy the ELF file to a binary (img) file IMAGE

# Find out where we are :-)
PRJ_ROOT	?= $(shell pwd)
DV_ROOT		?= $(shell (cd $(PRJ_ROOT)/../davros ; pwd))
DVSK_ROOT	= $(DV_ROOT)/davroska

# Select your hardware here
BOARD	?= blue-pill

# Select your compiler here
ifeq ($(BOARD), blue-pill)

# ARM gcc
DV_GNU_D	?=	/data1/gnu/gcc-arm-none-eabi-9-2019-q4-major

DV_GCC		?=	$(DV_GNU_D)/bin/arm-none-eabi-gcc
DV_LD		?=	$(DV_GNU_D)/bin/arm-none-eabi-ld
DV_OBJCOPY	?=	$(DV_GNU_D)/bin/arm-none-eabi-objcopy
DV_LDLIB_D	?=	$(DV_GNU_D)/arm-none-eabi/lib/thumb/v7-m/nofp

DV_LDSCRIPT	?=	$(DVSK_ROOT)/hardware/arm/ld/dv-blue-pill.ldscript

DV_ENTRY	?=	dv_reset

IMAGE		?=	fakeyboard.bin

CC_OPT		+= -mcpu=cortex-m3

endif


DV_BIN_D	= bin
DV_OBJ_D	= obj

CC_OPT		+=	-D DV_DAVROSKA=1
CC_OPT		+= -I h
CC_OPT		+= -I $(DVSK_ROOT)/h
CC_OPT		+= -I $(DVSK_ROOT)/hardware
CC_OPT		+= -I $(DV_ROOT)/usb/h
CC_OPT		+= -I $(DV_ROOT)/devices/h
CC_OPT		+= -I $(DV_ROOT)/lib/h
CC_OPT		+= -Wall
CC_OPT		+= -fno-common
CC_OPT		+= -g

CC_OPT		+= -O2

#CC_OPT		+= -mfloat-abi=hard
#CC_OPT		+= -mfpu=vfp

LD_OPT		+= -e $(DV_ENTRY)
LD_OPT		+= -T $(DV_LDSCRIPT)
LD_OPT		+=	-L $(DV_LDLIB_D)
LD_OPT		+=	-lc

# The project code
DV_LD_OBJS	+= $(DV_OBJ_D)/fakeyboard.o

# davroska and associated library files
DV_LD_OBJS	+= $(DV_OBJ_D)/davroska.o
DV_LD_OBJS	+= $(DV_OBJ_D)/davroska-time.o
DV_LD_OBJS	+= $(DV_OBJ_D)/davroska-extended.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-printf.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-xprintf.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-memset32.o

VPATH 		+=	c
VPATH 		+=	s
VPATH		+=	$(DVSK_ROOT)/c

# Hardware-specific files and paths
ifeq ($(BOARD), blue-pill)

# Hardware-specific project files
DV_LD_OBJS	+= $(DV_OBJ_D)/fakey-blue-pill.o

# davroska files
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-cortexm-vectors.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-stm32-rcc.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-stm32-uart.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-stm32-timx.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-stm32-usb.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-nvic.o
DV_LD_OBJS	+= $(DV_OBJ_D)/davroska-cortexm.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-switchcall.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-cortexm-ctxsw.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-usb.o
DV_LD_OBJS	+= $(DV_OBJ_D)/dv-usb-ep0-setup.o

VPATH		+=	$(DVSK_ROOT)/hardware/arm/c
VPATH		+=	$(DVSK_ROOT)/hardware/arm/s

endif

VPATH		+=	$(DVSK_ROOT)/hardware/common/c
VPATH		+=	$(DV_ROOT)/lib/c
VPATH		+=	$(DV_ROOT)/usb/c
VPATH		+=	$(DV_ROOT)/devices/c
VPATH		+=	$(DV_ROOT)/devices/s


.PHONY:		default all help clean image

default:	elf

clean:
	-rm -rf $(DV_OBJ_D) $(DV_BIN_D)

elf:		$(DV_OBJ_D) $(DV_BIN_D)/fakeyboard.elf

$(DV_BIN_D)/fakeyboard.elf:	$(DV_BIN_D) $(DV_LD_OBJS)
	$(DV_LD) -o $@ $(DV_LD_OBJS) $(LD_LIB) $(LD_OPT)

$(DV_OBJ_D)/%.o:  %.c
	$(DV_GCC) $(CC_OPT) -o $@ -c $<

$(DV_OBJ_D)/%.o:  %.S
	$(DV_GCC) $(CC_OPT) -o $@ -c $<

$(DV_BIN_D):
	mkdir -p bin

$(DV_OBJ_D):
	mkdir -p obj

image:			$(DV_OBJ_D) $(DV_BIN_D) $(IMAGE)

$(IMAGE):		$(DV_BIN_D)/fakeyboard.elf
	$(DV_OBJCOPY) $(DV_BIN_D)/fakeyboard.elf -O binary $(IMAGE)
	echo "flash write_image erase $(IMAGE) 0x08000000"
