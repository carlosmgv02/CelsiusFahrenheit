/*----------------------------------------------------------------
|   CelsiusFahrenheit.c: rutines de conversió de temperatura en 
|						 format Q14 (Coma Fixa 1:17:14). 
| ----------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Març 2021)
| ----------------------------------------------------------------*/

#include "Q14.h"	/* Q14: tipus Coma Fixa 1:17:14
					   MAKE_Q14(real): codifica un valor real en format Q14
					   MASK_SIGN: màscara per obtenir el bit de signe
					*/


/* Celsius2Fahrenheit(): converteix una temperatura en graus Celsius a la
						temperatura equivalent en graus Fahrenheit, utilitzant
						valors codificats en Coma Fixa 1:17:14.
	output = (input * 9/5) + 32.0;
*/
Q14 Celsius2Fahrenheit(Q14 input)
{
	Q14 output;
	long long prod64;		// resultat de la multiplicació (64 bits)

		// ajust d'escala (input * 9/5), amb multiplicació de 64 bits
	prod64 = (((long long) input) * MAKE_Q14(9.0/5.0));
	
		// ajustar bits fraccionaris:
		//	prod64 = real(input) * 2^14 * real(9/5) * 2^14
		//	output = prod64 / 2^14 = real(input * 9/5) * 2^14
	output = (Q14) (prod64 >> 14);
	
	output += MAKE_Q14(32.0);		// afegir desplaçament d'escala Fahrenheit

	return(output);
}


/* Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
						temperatura equivalent en graus Celsius, utilitzant
						valors codificats en Coma Fixa 1:17:14.
	output = (input - 32.0) * 5/9;
*/
Q14 Fahrenheit2Celsius(Q14 input)
{
	Q14 output;
	long long prod64;		// resultat de la multiplicació (64 bits)

	input -= MAKE_Q14(32.0);		// treure desplaçament d'escala Fahrenheit
		
		// ajust d'escala ((input - 32.0) * 5/9), amb multiplicació de 64 bits
	prod64 = (((long long) input) * MAKE_Q14(5.0/9.0));
	
		// ajustar bits fraccionaris:
		//	prod64 = real(input - 32.0) * 2^14 * real(5/9) * 2^14
		//	output = prod64 / 2^14 = real(input - 32.0) * real(5/9) * 2^14
	output = (Q14) (prod64 >> 14);

	return(output);
}

