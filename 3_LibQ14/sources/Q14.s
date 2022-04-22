@;-----------------------------------------------------------------
@;  Q14.s: rutines que permeten fer operacions aritmetiques amb
@;  valors codificats en codificacio 1:17:14(Q14). 
@;-----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Mar� 2021)
@;----------------------------------------------------------------
@;	Programador/a 1: carlos.martinezg@estudiants.urv.cat
@;	Programador/a 2: kennethleander.salazar@estudiants.urv.cat
@;----------------------------------------------------------------
.include "includes/Q14.i"
.text
    .align 2
    .arm
    .global add_Q14
    .global sub_Q14
    .global mul_Q14
    .global div_Q14

@; Description: 
@;          computes and returns the sum of the first 2 operands, (num1 + num2) 
@;          codified in Q14 format. it also informs if the operation has caused
@;          overflow
@; Parameters:
@;          R0 -> first operand
@;          R1 -> second operand
@;          R2 -> pointer to the variable that will contain the possible overflow
@; Result:
@;          R0 -> sum of num1 + num2
add_Q14:
    push {r3, lr}
    mov r3, #0                      @; indicates if the sum operation has produced overflow,
                                    @; initially we assume that there isn't overflow 

    adds r0, r1                     @; sum num1 and num2, and update the overflow flag
    movvs r3, #1                    @; set R3 equal to 1 if the sum operation has produced overflow 
    strb r3, [r2]                   @; store in memory the state of overflow

    pop {r3, pc}
        
@; Description: 
@;          computes and returns the subtraction of the first 2 operands, (num1-num2) 
@;          codified in Q14 format. it also informs if the operation has caused
@;          overflow
@; Parameters:
@;          R0 -> first operand
@;          R1 -> second operand
@;          R2 -> pointer to the variable that will contain the possible overflow
@; Result:
@;          R0 -> subtraction of num1 - num2
sub_Q14:
    push {r3, lr}

    mov r3, #0                      @; indicates if the sub operation has produced overflow,
                                    @; initially set to false 
    subs r0, r1                     @; R0 = R0 - R1
    movvs r3, #1                    @; update R3 in case the last instruction has produced
                                    @; overflow
    strb r3, [r2]                   @; store the overflow status in memory
    pop {r3, pc}
@; Description: 
@;          computes and returns the product of the first 2 operands, (num1*num2) 
@;          codified in Q14 format. it also informs if the operation has caused
@;          overflow
@; Parameters:
@;          R0 -> first operand
@;          R1 -> second operand
@;          R2 -> pointer to the variable that will contain the possible overflow
@; Result:
@;          R0 -> multiplication of num1 * num2
mul_Q14:
    push {r3-r8, lr}

    mov r3, #0                      @; indicates if the product operation has produced an
                                    @; overflow, initially set to 0
    mov r4, #0                      @; lower bits of num1 * num2
    mov r5, #0                      @; higher bits of num1 * num2

    smull r4, r5, r0, r1            @; computes the product of num1*num2 and store it's
                                    @; result in two registers, R4 and R5
@; set up the register to make the displacement of two registers 
    mov r6, #14                     @; # of bits to shift
    rsb r7, r6, #32                 @; R7 = 32 - 14 = 18, # of bits that aren't shifted
    mov r8, r4, lsl r7              @; get the bits that go out when doing the lower
                                    @; part displacement
    mov r8, r8, lsr r7              @; set the bits that went out in the last instruction
                                    @; in correspondece with their original weigth in bits
    mov r4, r4, lsr r6              @; shift to the right the lower part
    orr r4, r5, lsl r7              @; add to Rlo the d bits between Rhi and Rlo
    mov r5, r5, asr r6              @; shift to the right the higher part 

    .LDetermineOverflowBySign:
        cmp r4, #0                  @; determine the sign of the product result 
        blt .LProductIsNeg
    .LProductIsPositive:            @; if lower part is positive then R5 = 0
        cmp r5, #0
        movne r3, #1                @; update R3 state to indicate overflow if R5 != 0  
        b .LendDetermineOverflow
    .LProductIsNeg:
        mvn r5, r5                  @; revert bits of R5, 0s to 1s and 1s to 0s
        cmp r5, #0
        movne r3, #1                @; if R5 != 0 an overflow has been produced 
    .LendDetermineOverflow:

    mov r0, r4                      @; returns product in r0
    strb r3, [r2]                   @; save in memory the overflow state obtained

    pop {r3-r8, pc}

@; Description: 
@;          computes and returns the division of the first 2 operands, (num1/num2) 
@;          codified in Q14 format. it also informs if the operation has caused
@;          overflow
@; Parameters:
@;          R0 -> first operand
@;          R1 -> second operand
@;          R2 -> pointer to the variable that will contain the possible overflow
@; Result:
@;          R0 -> division of num1/num2
div_Q14:
    push {r3-r9, lr}

    mov r3, #0                      @; overflow state, initially set to false 
    mov r4, #0                      @; is negative the second operand ?, initially set to false 
    mov r6, r2                      @; copy the address inside R2 because R2 is overwritten later
                                    @; when setting up the arguments for calling the div_mod rutine

    .LIsDivisor0:
        cmp r1, #0                  @; Determine if the divisor is equal to 0
        beq .LCantPerformDivByZero  @; jump if divisor == 0
    .LDetermineOp2Sign:
        cmp r1, #0                  @; determine the sign of Op2 
        movlt r4, #1                @; if Op2 is negative then update Op2Neg to True 
        bge .LOp2NotNeg             @; don't change the sign of Op2 if it's a positive number 
    .LChangeOp2Sign:
        mvn r1, r1                  @; apply the Ca2 algorithm to convert Op2 to positive
        add r1, #1
    .LOp2NotNeg:

    sub sp, #12                     @; allocate in the stack 12 bytes for quo, mod and ov
    mov r5, sp                      @; R5 is a fixed reference to the stack

    @; set up the arguments to invoke the div_mod rutine
    mov r7, r3                      @; copy the overflow state and num1 because are overwritten  
    mov r8, r0                      @; later when setting up the arguments for the div_mod rutine 
    mov r9, #1
    mov r0, r9, lsl #28             @; R0 = MAKE_Q14(1.0) << 14 = (1.0 << 14) << 14 = 1.0 << 28 
    mov r2, r5                      @; get address of local variables quo and mod located in the
    add r3, r5, #4                  @; stack 

    bl div_mod

    mov r0, r8                      @; restore the num1 value in R0 
    ldr r1, [r5]                    @; R1 = quo value 
    add r2, r5, #8                  @; R2 contains the mem address of the local variable ov

    bl mul_Q14                      @; invoke the rutine, R0 returns the result of this routine too

    ldrb r3, [r5, #8]               @; load in R3 the overflow state possibly modified by mul_Q14 

    add sp, #12                     @; remove the space allocated for quo and mod on the stack

    .LIfOp2WasNeg:
        cmp r4, #1                  @; check if Op2Neg is true
        bne .LOp2WasPositive        @; if not then don't convert the result to negative
    .LConvertResult2Neg:
        mvn r0, r0                  
        add r0, #1
    .LOp2WasPositive:

    b .LendProgram                  @; jump the next instructions 

    .LCantPerformDivByZero:
        mov r0, #0
        mov r3, #1                  @; infinite can't be represented numerically so overflow = 1
        strb r3, [r2]
    .LendProgram:

    strb r3, [r6]                   @; *overflow = ov

    pop {r3-r9, pc}

.end

