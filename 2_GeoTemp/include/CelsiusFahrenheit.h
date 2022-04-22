/*---------------------------------------------------------------------
|   Declaració de prototipus de funcions de conversió de temperatures,
|	en format Coma Fixa 1:17:14.
| ---------------------------------------------------------------------
|	pere.millan@urv.cat
|	santiago.romani@urv.cat
|	(Març 2021)
| ---------------------------------------------------------------------*/

#ifndef CELSIUSFAHRENHEIT_H
#define CELSIUSFAHRENHEIT_H

#include "Q14.h"

/* Celsius2Fahrenheit(): converteix una temperatura en graus Celsius a la
						temperatura equivalent en graus Fahrenheit, utilitzant
						valors codificats en Coma Fixa 1:17:14.
	output = (input * 9/5) + 32.0;
*/
extern Q14 Celsius2Fahrenheit(Q14 input);

/* Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
						temperatura equivalent en graus Celsius, utilitzant
						valors codificats en Coma Fixa 1:17:14.
	output = (input - 32.0) * 5/9;
*/
extern Q14 Fahrenheit2Celsius(Q14 input);


#endif /* CELSIUSFAHRENHEIT_H */
