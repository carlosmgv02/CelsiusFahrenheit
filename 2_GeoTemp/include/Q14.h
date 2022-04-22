/*-----------------------------------------------------------------
|   Declaraci� de tipus, m�scares i macro del format Q14, �s a dir, 
|	en format Coma Fixa 1:17:14.
| -----------------------------------------------------------------
|	pere.millan@urv.cat
|	santiago.romani@urv.cat
|	(Mar� 2021)
| ----------------------------------------------------------------*/

#ifndef Q14_H
#define Q14_H


/* Declaraci� de tipus Coma Fixa 1:17:14 
		 1 bit  de signe (bit 31), =0 -> positiu, =1 -> negatiu
		17 bits de part entera (bits 30..14), aprox. 5 d�gits en base 10
		14 bits de part fraccion�ria (bits 13..0), aprox. 4 d�gits en base 10
*/
typedef int Q14;


/* Macro per convertir valors reals en valors Coma Fixa 1:17:14
		Exemples:
		MAKE_Q14(3.1416) --> 0x0000C910
		MAKE_Q14(-5.125) --> 0xFFFEB800
*/
#define MAKE_Q14(real)	(int)((real)*(1<<14)+(real<0?-0.5:0.5)) 


/* M�SCARES per als camps de bits de valors 1:17:14 */
#define MASK_SIGN	0x80000000	/* bit 31:		signe */
#define MASK_INT	0x7FFFC000	/* bits 30..14:	part entera */
#define MASK_FRAC	0x00003FFF	/* bits 13..0:	part fraccion�ria */


#endif /* Q14_H */
