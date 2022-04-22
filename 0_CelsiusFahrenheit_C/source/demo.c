/*-----------------------------------------------------------------------
|   Description: a program to check the temperature-scale conversion
|				functions implemented in "CelsiusFahrenheit.c".
|	IMPORTANT NOTE: there is a much confident testing set implemented in
|				"tests/test_CelsiusFahrenheit.c"; the aim of "demo.c" is
|				to show how would it be a usual main() code invoking the
|				mentioned functions.
|------------------------------------------------------------------------
|	Author: Santiago Romani (DEIM, URV)
|	Date:   March/2021 
| -----------------------------------------------------------------------*/

#include "Q14.h"				/* external declarations of types, defines and
								   macro for dealing with Q14 numbers */
#include "CelsiusFahrenheit.h"	/* external declarations of function
								   prototypes for temperature conversions */


/* global variables as inputs and output */
Q14 temp1C = MAKE_Q14(35.21);		// sample Celsius temperature
Q14 temp2F = MAKE_Q14(-23.75);		// sample Fahrenheit temperature

Q14 temp1F;		// expected conversion of temp1C:  95.378   ºF
Q14 temp2C;		// expected conversion of temp2C: -30.97222 ºC

int main(void)
{
	temp1F = Celsius2Fahrenheit(temp1C);
	temp2C = Fahrenheit2Celsius(temp2F);

/* TESTING POINT: check the results
	(gdb) p /f temp1F/16384.0		-> 95.378
	(gdb) p /f temp2C/16384.0		-> -30.97222
*/

/* BREAKPOINT */
	return(0);
}
