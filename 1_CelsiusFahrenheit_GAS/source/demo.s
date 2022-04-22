@;-----------------------------------------------------------------------
@;   Description: a program to check the temperature-scale conversion
@;				functions implemented in "CelsiusFahrenheit.c".
@;	IMPORTANT NOTE: there is a much confident testing set implemented in
@;				"tests/test_CelsiusFahrenheit.c"; the aim of "demo.c" is
@;				to show how would it be a usual main() code invoking the
@;				mentioned functions.
@;-----------------------------------------------------------------------
@;	Author: Santiago Romani (DEIM, URV)
@;	Date:   March/2021 
@;-----------------------------------------------------------------------
@;	Programador/a 1: carlos.martinezg@estudiants.urv.cat
@;	Programador/a 2: kennethleander.salazar@estudiants.urv.cat
@;-----------------------------------------------------------------------*/

.data
		.align 2
	temp1C:	.word 0x0008CD71		@; temp1C = 35.21 ºC
	temp2F:	.word 0xFFFA1000		@; temp2F = -23.75 ºF

.bss
		.align 2
	temp1F:	.space 4				@; expected conversion:  95.378   ºF
	temp2C:	.space 4				@; expected conversion: -30.97222 ºC


.text
		.align 2
		.arm
		.global main
main:
		push {r0, r1, lr}
		
		ldr r1, =temp1C				
		ldr r0, [r1]				@; C2F rutine requires Fahrenheit temp
									@; loaded in register 0
		
			@; temp1F = Celsius2Fahrenheit(temp1C);
		bl Celsius2Fahrenheit		@; call the routine, R0 has the result
		
		ldr r1, =temp1F				
		str r0, [r1]				@; stores in memory the conversion C2F
		
		ldr r1, =temp2F				
		ldr r0, [r1]				@; F2C rutine needs Celsius temperature
									@; loaded in R0
									
			@; temp2C = Fahrenheit2Celsius(temp2F);
		bl Fahrenheit2Celsius		@; call the routine, R0 brings back result
		
		ldr r1, =temp2C
		str r0, [r1]				@; stores F2C conversion in temp2C var
		
		
@; TESTING POINT: check the results
@;	(gdb) p /x temp1F		-> 0x0017D831
@;	(gdb) p /x temp2C		-> 0xFFF841C7
@; BREAKPOINT
		mov r0, #0					@; return(0)
		
		pop {r0, r1, pc}

.end

