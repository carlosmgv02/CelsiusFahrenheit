@;----------------------------------------------------------------
@;  CelsiusFahrenheit.s: rutines de conversi� de temperatura en 
@;						 format Q14 (Coma Fixa 1:17:14). 
@;----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Mar� 2021)
@;----------------------------------------------------------------
@;	Programador/a 1: carlos.martinezg@estudiants.urv.cat
@;	Programador/a 2: kennethleander.salazar@estudiants.urv.cat
@;----------------------------------------------------------------*/

.include "includes/Q14.i"

.data
		.align 2
	onePoint8:	.word 0x00007333	@; real 9.0/5.0 en codificacion Q14
	zeroPoint5: .word 0x0000238E	@; real 5.0/9.0 en codificacion Q14
	thirty2: 	.word 0x00080000	@; real 32.0 en codificacion Q14
.text
		.align 2
		.arm


@; Celsius2Fahrenheit(): converteix una temperatura en graus Celsius a la
@;						temperatura equivalent en graus Fahrenheit, utilitzant
@;						valors codificats en Coma Fixa 1:17:14.
@;	Entrada:
@;		input 	-> R0
@;	Sortida:
@;		R0 		-> output = (input * 9/5) + 32.0 = (input * 1.8) +32.0;
	.global Celsius2Fahrenheit
Celsius2Fahrenheit:
		push {r1-r2, lr}

		ldr	r1, =onePoint8			@; R1 points to @onePoint8
		ldr r1, [r1]				@; load decimal number 1.8 codified in Q14
									@; format
		sub sp, #4					@; allocate space in the stack for one var
		mov r2, sp 					@; R2 is the overflow argument for div_Q14 rutine 

		bl mul_Q14					@; invoke the rutine, R0 returns Q14(input*1.8)

		add sp, #4					@; remove the space allocated in the stack

		ldr r1, =thirty2			@; R1 points to @thirty2
		ldr r1, [r1]				@; load number 32.0 codified in Q14 format

		sub sp, #4					@; allocate space for the overflow variable
		mov r2, sp 					@; R2 is the overflow argument for div_Q14 rutine 

		bl add_Q14					@; sum R1 = Q14(input*1.8) + Q14(32.0)

		add sp, #4					@; remove the space allocated in the stack

		@: mov r0, r0				@; returns the output in register 0
		
		pop {r1-r2, pc}



@; Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
@;						temperatura equivalent en graus Celsius, utilitzant
@;						valors codificats en Coma Fixa 1:17:14.
@;	Entrada:
@;		input 	-> R0
@;	Sortida:
@;		R0 		-> output = (input - 32.0) * 5/9;
	.global Fahrenheit2Celsius
Fahrenheit2Celsius:
		push {r1-r2, lr}
		
		ldr r1, =thirty2			@; R1 points to @thirty2
		ldr r1, [r1]				@; load number 32.0 coded in Q14 format  

		sub sp, #4					@; allocate space for the overflow variable
		mov r2, sp 					@; R2 is the overflow argument for div_Q14 rutine 

		bl sub_Q14					@; invoke the rutine, R0 returns Q14(input) - Q14(32.0) 

		add sp, #4					@; remove the space reserved

		ldr r1, =zeroPoint5			@; R1 points to @zeroPoint5
		ldr r1, [r1]				@; Assign the value pointed by zeroPoint5

		sub sp, #4					@; allocate space for the overflow variable
		mov r2, sp 					@; R2 is the overflow argument for div_Q14 rutine 

		bl mul_Q14					@; calculates Q14(input-32.0) * Q14(5.0/9.0)

		add sp, #4					@; remove the space reserved

		@; mov r0, r0				@; return the result of this rutine in R0

		pop {r1-r2, pc}

