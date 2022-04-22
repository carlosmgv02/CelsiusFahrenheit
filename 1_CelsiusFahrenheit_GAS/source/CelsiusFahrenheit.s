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

.include "include/Q14.i"

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
		push {r1-r6, lr}
				
		ldr	r1, =onePoint8			@; R1 points to @onePoint8
		ldr r1, [r1]				@; load decimal number 1.8 codified in Q14
									@; format
		
		smull r2, r3, r0, r1		@; R2 = Q14(input) * Q14(1.8)
		
@; Displacement of register 2 and 3 to the right.
		mov r4, #14					@; number of bits to shift 
		rsb r5, r4, #32				@; R2 = 32 - 14 = 18
		mov r6, r2, lsl r5			@; R6 hold r1 bits that get out when doing
									@; the lower part displacement
									
		mov r6, r6, lsr r5			@; r6 = r6 >> 18
		mov r2, r2, lsr r4			@; shift to the right the lower part
		orr r2, r3, lsl r5			@; add to Rlo d bits between Rhi and Rlo
		mov r3, r3, asr r4			@; shift to the right the higher part

		ldr r1, =thirty2			@; R1 points to @thirty2
		ldr r1, [r1]				@; load number 32.0 codified in Q14 format
		add r2, r1					@; sum 32.0 to R2
		
		mov r0, r2					@; R0 = output, as R0 must contain the 
									@; output value
		pop {r1-r6, pc}



@; Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
@;						temperatura equivalent en graus Celsius, utilitzant
@;						valors codificats en Coma Fixa 1:17:14.
@;	Entrada:
@;		input 	-> R0
@;	Sortida:
@;		R0 		-> output = (input - 32.0) * 5/9;
	.global Fahrenheit2Celsius
Fahrenheit2Celsius:
		push {r1-r6, lr}
		
		ldr r1, =thirty2			@; R1 points to @thirty2
		ldr r1, [r1]				@; load number 32.0 coded in Q14 format  
		
		sub r0, r1					@; R0 = R0 - R1 = Q14(input) - Q14(32.0)
		
		ldr r1, =zeroPoint5			@; R1 points to @zeroPoint5
		ldr r1, [r1]				@; Assign the value pointed by zeroPoint5
		
		smull r2, r3, r0, r1		@; R2 = Q14(input - 32.0) * Q14(5/9)
		
@; Desplazo r2 y r3 a la derecha. Es un desplazamiento aritmetico.
		mov r4, #14					@; number of bits to shift 
		rsb r5, r4, #32				@; R2 = 32 - 14 = 18
		mov r6, r2, lsl r5			@; R6 hold r1 bits that get out when doing
									@; the lower part displacement
									
		mov r6, r6, lsr r5			@; r6 = r6 >> 18
		mov r2, r2, lsr r4			@; shift to the right the lower part
		orr r2, r3, lsl r5			@; add to Rlo d bits between Rhi and Rlo
		mov r3, r3, asr r4			@; shift to the right the higher part		
				
		mov r0, r2					@; The result must be loaded in register 0
		
		pop {r1-r6, pc}

