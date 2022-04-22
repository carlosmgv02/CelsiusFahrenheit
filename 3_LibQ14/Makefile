#-------------------------------------------------------------------------------
# Example Makefile to build a library and to test the functions of each module
# Authors: Santiago Romani, Pere Mill�n
# Date: April 2021
#----------------------------------------------------------------
#	Programador/a 1: carlos.martinezg@estudiants.urv.cat
#	Programador/a 2: kennethleander.salazar@estudiants.urv.cat
#----------------------------------------------------------------

#-------------------------------------------------------------------------------
# options for code generation
#-------------------------------------------------------------------------------
ARCH	:= -march=armv5te -mlittle-endian
ASFLAGS	:= $(ARCH) -g
CCFLAGS	:= -Wall -gdwarf-3 -O0 $(ARCH) -I./includes
LDFLAGS := -z max-page-size=0x8000

#-------------------------------------------------------------------------------
# make commands
#-------------------------------------------------------------------------------
libQ14.a: build/Q14.o
	arm-none-eabi-ar -rs libQ14.a build/Q14.o

build/Q14.o: sources/Q14.s includes/Q14.h includes/Q14.i
	arm-none-eabi-as $(ASFLAGS) sources/Q14.s -o build/Q14.o


#-------------------------------------------------------------------------------
# test making commands for Q14.s source file
#-------------------------------------------------------------------------------
test_Q14.elf : tests/test_Q14.c includes/Q14.h libQ14.a
	arm-none-eabi-gcc $(CCFLAGS) -c tests/test_Q14.c -o build/test_Q14.o
	arm-none-eabi-ld $(LDFLAGS) build/test_Q14.o tests/startup.o \
					libQ14.a tests/libfoncompus.a -o test_Q14.elf

demo.elf : tests/demo.c includes/Q14.h libQ14.a
	arm-none-eabi-gcc $(CCFLAGS) -c tests/demo.c -o build/demo.o
	arm-none-eabi-ld $(LDFLAGS) build/demo.o tests/startup.o \
					libQ14.a tests/libfoncompus.a -o demo.elf

#-------------------------------------------------------------------------------
# test making commands for avgmaxmintemp.s source file
#-------------------------------------------------------------------------------
test_geotemp.elf : p_lib/CelsiusFahrenheit.o p_lib/startup.o p_lib/libfoncompus.a \
	build/test_geotemp.o build/avgmaxmintemp.o includes/avgmaxmintemp.i  build/Q14.o
	arm-none-eabi-ld $(LDFLAGS) build/test_geotemp.o build/avgmaxmintemp.o build/Q14.o\
			p_lib/CelsiusFahrenheit.o p_lib/startup.o p_lib/libfoncompus.a -o test_geotemp.elf

build/avgmaxmintemp.o: sources/avgmaxmintemp.s includes/avgmaxmintemp.i 
	arm-none-eabi-as $(ASFLAGS) sources/avgmaxmintemp.s -o build/avgmaxmintemp.o

build/test_geotemp.o: tests/test_geotemp.c 
	arm-none-eabi-gcc $(CCFLAGS) -c tests/test_geotemp.c -o build/test_geotemp.o

#-------------------------------------------------------------------------------
# test making commands for CelsiusFahrenheit.s source file
#-------------------------------------------------------------------------------
build/CelsiusFahrenheit.o: sources/CelsiusFahrenheit.s includes/Q14.i
	arm-none-eabi-as $(ASFLAGS) -c sources/CelsiusFahrenheit.s -o build/CelsiusFahrenheit.o

test_celsiusfahrenheit.elf : build/test_CelsiusFahrenheit.o p_lib/libfoncompus.a build/CelsiusFahrenheit.o build/Q14.o
	arm-none-eabi-ld $(LDFLAGS) build/test_CelsiusFahrenheit.o build/Q14.o build/CelsiusFahrenheit.o \
						p_lib/startup.o p_lib/libfoncompus.a -o test_CelsiusFahrenheit.elf

build/test_CelsiusFahrenheit.o: tests/test_CelsiusFahrenheit.c includes/CelsiusFahrenheit.h includes/Q14.h
	arm-none-eabi-gcc $(CCFLAGS) -c tests/test_CelsiusFahrenheit.c -o build/test_CelsiusFahrenheit.o

#-------------------------------------------------------------------------------
# clean commands
#-------------------------------------------------------------------------------
clean : 
	@rm -fv build/*
	@rm -fv *.elf


#-----------------------------------------------------------------------------
# run commands
#-----------------------------------------------------------------------------
run : demo.elf
	arm-eabi-insight demo.elf &


#-----------------------------------------------------------------------------
# debug commands
#-----------------------------------------------------------------------------
debug : test_Q14.elf
	arm-eabi-insight test_Q14.elf &

debug_geotemp: test_geotemp.elf
	arm-eabi-insight test_geotemp.elf &

debug_celfah: test_celsiusfahrenheit.elf
	arm-eabi-insight test_celsiusfahrenheit.elf &
