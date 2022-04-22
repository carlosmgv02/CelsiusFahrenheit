@;-----------------------------------------------------------------
@;  avgmaxmintemp.s: rutines per al calcul de la temperatura promig,
@;	maxima, minima i l'index de la posició on hem trobat aquesta
@;	temperatura maxima i minima. Tot en codificacion Q14.
@;-----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Mar� 2021)
@;----------------------------------------------------------------
@;	Programador/a 1: carlos.martinezg@estudiants.urv.cat
@;	Programador/a 2: kennethleander.salazar@estudiants.urv.cat
@;----------------------------------------------------------------*/
.include "include/avgmaxmintemp.i"
	
.text
		.align 2
		.arm
		.global avgmaxmin_city
		.global avgmaxmin_month
		
@; Description:
@;		Computes the medium temperature, maximum and minimun of a city from a
@; 		temperatures table, where each row is a city and a column is a month
@; 		and each temperature is expressed in Q14 format. 
@; Parameters:
@;		R0 -> base address to the table that contains the temperatures
@;		R1 -> number of rows in the table
@;		R2 -> id_city, number of row (city) that we have to process
@;		R3 -> memory address to the structure that will contain the result of 
@;		this rutine
@; Result:
avgmaxmin_city:
	push {r1, r4-r12, lr}
	
	mov r1, #12						@; columns number of table ttemp
	mov r4, #0						@; avg variable
	mov r5, #0						@; min variable
	mov r6, #0						@; max variable
	mov r7, #0						@; idmin variable
	mov r8, #0 						@; idmax variable
	mov r9, #0						@; for loop index
	mov r10, #0						@; temporal variable of temperature
	mov r11, #0						@; offset to get the temperature

@; Initialize avg, min and max variable with the values at the first column
	mul r11, r2, r1					@; R12 = i*NC, calculate  offset
	ldr r4, [r0, r11, lsl #2]		@; init avg with ttemp[id_city][0]
	mov r5, r4
	mov r6, r4						
	
	add r9, #1						@; init the index loop at one				
	.Lfor:
		@; loop body
		add r12, r11, r9			@; R12 = i*NC + j, move to the next column 
		ldr r10, [r0, r12, lsl #2]	@; get temp of next month in tvar
		
		add r4, r10					@; avg += tvar
@; evaluate cond. one to update the max value if a higher one has been founded
		.Lif:
			cmp r10, r6				@; tvar - max
			ble .LendUpdatemax		@; jump if tvar <= max
		.Lupdatemax:
			mov r6, r10				@; one temp. higher than max was founded
			mov r8, r9				@; idmax = j
		.LendUpdatemax:
@; evaluate condition two to update the min value
		.Lif2:
			cmp r10, r5				@; tvar - min
			bge .LendUpdatemin		@; jump if tvar >= min
		.Lupdatemin:
			mov r5, r10				@; one temp. lower than min was founded
			mov r7, r9				@; idmin = j
		.LendUpdatemin:
		
		add r9, #1					@; move to the next column, j++		
		cmp r9, r1					@; check the continuity of the loop
		blt .Lfor					@; repeat the lop while j < NC
	.Lendfor:	
	
	mov r10, r3						@; copy the tmax_min address because R3 is
									@; overwritten later when calling div_mod
	mov r9, r4						@; used later to return the negative sign
									@; of avg, in case avg is negative 

	.LifConvert2Positive:
		cmp r4, #0					@; determines sign of avg value
		bge .LendIfConvert2Positive
	.LthenConvert2Positive:
		mvn r4, r4					@; Ca2 algorithm to convert num to positive 
		add r4, #1
	.LendIfConvert2Positive:
	
	@; prepare arguments for div_mod rutine
	sub sp, #8						@; allocate in the stack 8 bytes
	mov r0, r4						@; avg is the numerator for div_mod rutine
	mov r1, #12						@; int. 12 is the denominator for div_mod
	mov r2, sp						@; quotient of R0/R1
	add r3, sp, #4					@; remainder of R0/R1

	bl div_mod 						@; divide Q14(avg) / 12
	ldr r4, [r2]					@; substitute avg with avg/12
	
	add sp, #8						@; remove the space reserved in the stack
	.LifConvert2Negative:
		cmp r6, #0					@; Was avg negative before calling div_mod 
		bge .LendIfConvert2Negative
	.LthenConvert2Negative:
		mvn r4, r4					@; apply the Ca2 algorithm to change sign
		add r4, #1					@; of an integer number
	.LendIfConvert2Negative:
	
	str r5, [r10, #MM_TMINC]		@; mmres->tmin_C = min
	
	str r6, [r10, #MM_TMAXC] 		@; mmres->tmax_C = max
	
	mov r0, r5						@; load input to rutine C2F, R5 = min
	bl Celsius2Fahrenheit			@; R0 returns the converted temperature
	
	@; store the results of min, max, idmin and idmax in the struct t_maxmin
	str r0, [r10, #MM_TMINF]		@; mmres->tmin_F = C2F(min)
	
	mov r0, r6						@; copy max to R0, used by rutine C2F
	bl Celsius2Fahrenheit			@; R0 returns the converted temperature
	
	str r0, [r10, #MM_TMAXF]		@; mmres->tmax_F = C2F(max)
	
	strh r7, [r10, #MM_IDMIN]		@; mmres->id_min = idmin
	
	strh r8, [r10, #MM_IDMAX]		@; mmres->id_max = idmax
	
	mov r0, r4						@; return the avg value in register R0
	
	pop {r1, r4-r12, pc}
	
@; Description:
@;		Computes the medium temperature, maximum and minimun in a month from
@; 		a temperature table, where each row is a city and a column is a month
@; 		and each temperature is expressed in Q14 format. 
@; Parameters:
@;		R0 -> base address to the table that contains the temperatures
@;		R1 -> number of rows in the table
@;		R2 -> id_month, number of column (month) that we have to process
@;		R3 -> memory address to the structure that contains the result of this
@;		rutine	
@; Result: 
avgmaxmin_month:
	push {r4-r12, lr}
@; how the registers are used to imitate the local variables in the c code
	mov r4, #0						@; avg variable
	mov r5, #0						@; min variable
	mov r6, #0						@; max variable
	mov r7, #0 						@; idmin varible 
	mov r8, #0 						@; idmax variable
	mov r9, #0						@; while loop index
	mov r10, #0						@; temporal variable of temperature, tvar
	mov r11, #12 					@; number of columns in the table


	ldr r4, [r0, r2, lsl #2]		@; init avg var with ttemp[0][id_month]
	mov r5, r4						@; min = avg
	mov r6, r4						@; max = avg
	
	add r9, #1						@; positionate the index at the second row
	.Lwhile:
		cmp r9, r1					@; check the continuity of the loop
		bge .LendWhile				@; terminate the loop if i >= n_rows
		@; loop body
 
		mul r12, r9, r11			@; R12 = i * NC, positionate in the row
		add r12, r2					@; R12 += j, positionate on the right col
		ldr r10, [r0, r12, lsl #2]	@; get next city temperature and store it 
									@; in tvar
		add r4, r10					@; avg += tvar
		
@; evaluate condition one that updates the max value
		.Lifmax:
			cmp r10, r6				@; has been found a higher temp than max?
			ble .Lendifmax 			@; if not then jump to the end of this if
		.Lthenmax:
			mov r6, r10				@; update the max value
			mov r8, r9				@; update the index of max value
		.Lendifmax:
@; evaluate condition two that updates the min value		
		.Lifmin:
			cmp r10, r5				@; has been found a lower temp than min?
			bge .Lendifmin			@; if not then jump to the end of this if
		.Lthenmin:
			mov r5, r10				@; update the min value
			mov r7, r9				@; update the index of min value
		.Lendifmin:
		
		add r9, #1					@; move to the next row
		b .Lwhile					@; repeat the loop
	.LendWhile:
	
	mov r12, #0						@; indicates if avg is negative, avgNeg
	cmp r4, #0						@; determine if avg is negative
	movlt r12, #1					@; if it's then variable avgNeg equal to 1

	@; change sign of avg if it is negative
	.Lifavgnegative:	
		cmp r12, #0					@; determine if avgNeg is equal to 1
		beq .Lendifavgnegative		@; if not then don't change sign of avg
	.Lthenavgnegative:
		mvn r4, r4					@; change sign of avg to positive
		add r4, #1
	.Lendifavgnegative:
	
	mov r10, r4						@; tvar = abs(avg)
	
	mov r11, r3						@; copy the tmax_min address because R3 is
									@; overwritten later when calling div_mod
	
	@; prepare arguments for div_mod rutine
	mov r0, r10						@; load numerator of div_mod rutine
	@;mov r1, r1					@; unnecessary but added for clarity
	
	sub sp, #8						@; reserve space in the stack 
	mov r2, sp						@; quotient address for div_mod rutine
	add r3, sp, #4					@; fourth parameter address for div_mod
	
	bl div_mod						@; invoke div_mod rutine
	
	ldr r4, [r2]					@; load vlue of avg/n_rows in avg register
	
	add sp, #8						@; remove the space allocated in the stack
	
	@; restore sign of avg if after calling rutine div_mod was a negative num
	cmp r12, #1						@; determine if avgNeg is equal to 1
	moveq r4, r4					@; if it's then change the sign of avg
	addeq r4, #1		
	
	str r5, [r11, #MM_TMINC]		@; mmres->tmin_C = min
	
	str r6, [r11, #MM_TMAXC]		@; mmres->tmax_C = max
	
	mov r0, r5						@; load min as argument to rutine C2F
	bl Celsius2Fahrenheit 			@; convert min into a fahrenheit temp
	
	str r0, [r11, #MM_TMINF]		@; mmres->tmin_F = C2F(min)
	
	mov r0, r6						@; load max as argument to rutine C2F
	bl Celsius2Fahrenheit			@; convert max into a fahrenheit temp
	
	str r0, [r11, #MM_TMAXF]		@; mmres->tmax_F = C2F(max)
	
	strh r7, [r11, #MM_IDMIN]		@; mmres->id_min = idmin
	
	strh r8, [r11, #MM_IDMAX]		@; mmres->id_max = idmax
	
	mov r0, r4						@; return the avg obtanied in register R0
	
	pop {r4-r12, pc}
	
.end
