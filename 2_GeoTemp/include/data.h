/*---------------------------------------------------------------------
|   Declaraci� de variables globals definides en "data.c", amb
|	informaci� per al programa "geotemp.c" .
| ---------------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Mar� 2021)
| ---------------------------------------------------------------------*/

#ifndef DATAGEOTEMP_H
#define DATAGEOTEMP_H

#include "Q14.h"				// definici� tipus Q14
#include "geotemp.h"			// definitici� tipus t_cityinfo

		/* declaracions estructures de dades externes amb les dades */
#define NUMCITIESHNORD	18
#define NUMCITIESHSUD	19

extern Q14 tempHNord_2020[NUMCITIESHNORD][12];
extern Q14 tempHSud_2020[NUMCITIESHSUD][12];

extern t_cityinfo info_HNord[NUMCITIESHNORD];
extern t_cityinfo info_HSud[NUMCITIESHSUD];

#endif 	/* DATAGEOTEMP_H */