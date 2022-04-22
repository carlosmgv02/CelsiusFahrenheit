/*-----------------------------------------------------------------------
|   Description: a program to check some fixed point arithmetic functions
|				implemented in "libQ14.a"; specifically, it computes the
|				area of a trapezium, given the key parameters (long base,
|				short base, height).
|------------------------------------------------------------------------
|	Author: Santiago Romani (DEIM, URV)
|	Date:   April/2021 
| -----------------------------------------------------------------------*/

#include "Q14.h"		/* external declarations of types, defines, macros
				   and function prototypes for operating with Q14 numbers */


/* global variables as inputs and output, for computing the areas */
Q14 long_base = MAKE_Q14(45.12);		// B = 45.12 cm
Q14 short_base = MAKE_Q14(30.75);		// b = 30.75 cm
Q14 height = MAKE_Q14(29.99);			// h = 29.99 cm
Q14 trapezium_area;		// expected value: (B+b)*h/2 = 1137.67065 cm^2

int main(void)
{
	unsigned char ov;				/* possible overflow */
	Q14 pr;						/* partial result */
	
		// trapezium_area = (long_base + short_base)*height / 2.0
	pr = add_Q14(long_base, short_base, &ov);
	if (!ov)
	{			// proceed with remaining ops only if not overflow
		pr = mul_Q14(pr, height, &ov);
		if (!ov)
		{
			pr = div_Q14(pr, MAKE_Q14(2.0), &ov);
			if (!ov)				// if everthing went fine,
				trapezium_area = pr;	// update output global variable
		}
	}

/* TESTING POINT: check the result (if no overflow)
	(gdb) p ov
	(gdb) p /f trapezium_area/16384.0
*/

/* BREAKPOINT */
	return(ov);
}
