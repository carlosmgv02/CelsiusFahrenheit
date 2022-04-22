/*-----------------------------------------------------------------------
|   "geotempData.c":
|		Dades per a ser processades pel les rutines definides en
|	"avgmaxmintemp.c", a partir de taules que contenen valors de
|	temperatura per a diferents ciutats del món durant els 12 mesos
|	de l'any.
|	Font: https://en.wikipedia.org/wiki/List_of_cities_by_average_temperature
|------------------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Març 2021)
| -----------------------------------------------------------------------*/

#include "Q14.h"				/* Q14: tipus Coma Fixa 1:17:14 */
#include "geotemp.h"			/* t_cityinfo: tipus amb info. de ciutat */
#include "data.h"				/* defines número de ciutats */			

Q14 tempHNord_2020[NUMCITIESHNORD][12] = {
	{MAKE_Q14(13.4), MAKE_Q14(13.9), MAKE_Q14(15.7), MAKE_Q14(18.5),	// Alexandria
	 MAKE_Q14(21.2), MAKE_Q14(24.3), MAKE_Q14(25.9), MAKE_Q14(26.3),
	 MAKE_Q14(25.1), MAKE_Q14(22.0), MAKE_Q14(18.7), MAKE_Q14(14.9)},
	{MAKE_Q14(2.2), MAKE_Q14(3.5), MAKE_Q14(5.8), MAKE_Q14(7.5),		// Andorra la Vella
	 MAKE_Q14(11.5), MAKE_Q14(15.4), MAKE_Q14(18.8), MAKE_Q14(18.5),
	 MAKE_Q14(14.9), MAKE_Q14(10.3), MAKE_Q14(5.7), MAKE_Q14(3.0)},
	{MAKE_Q14(-3.1), MAKE_Q14(0.3), MAKE_Q14(6.7), MAKE_Q14(14.8),		// Beijing
	 MAKE_Q14(20.8), MAKE_Q14(24.9), MAKE_Q14(26.7), MAKE_Q14(25.5),
	 MAKE_Q14(20.8), MAKE_Q14(13.7), MAKE_Q14(5.0), MAKE_Q14(-0.9)},
	{MAKE_Q14(-7.1), MAKE_Q14(-5.4), MAKE_Q14(-1.6), MAKE_Q14(4.6),		// Calgary
	 MAKE_Q14(9.7), MAKE_Q14(13.7), MAKE_Q14(16.5), MAKE_Q14(15.8),
	 MAKE_Q14(11.0), MAKE_Q14(5.2), MAKE_Q14(-2.4), MAKE_Q14(-6.8)},
	{MAKE_Q14(-24.8), MAKE_Q14(-25.4), MAKE_Q14(-22.1), MAKE_Q14(-17.2),// Dikson
	 MAKE_Q14(-7.8), MAKE_Q14(0.4), MAKE_Q14(4.9), MAKE_Q14(5.5),
	 MAKE_Q14(1.6), MAKE_Q14(-7.5), MAKE_Q14(-17.5), MAKE_Q14(-22.9)},
	{MAKE_Q14(25.1), MAKE_Q14(25.7), MAKE_Q14(27.0), MAKE_Q14(28.7),	// Djibouti
	 MAKE_Q14(31.0), MAKE_Q14(34.2), MAKE_Q14(36.4), MAKE_Q14(36.0),
	 MAKE_Q14(33.1), MAKE_Q14(29.3), MAKE_Q14(26.9), MAKE_Q14(25.4)},
	{MAKE_Q14(78.4), MAKE_Q14(79.0), MAKE_Q14(79.9), MAKE_Q14(81.7),	// George Town
	 MAKE_Q14(83.3), MAKE_Q14(84.6), MAKE_Q14(85.3), MAKE_Q14(85.5),
	 MAKE_Q14(84.7), MAKE_Q14(83.3), MAKE_Q14(81.5), MAKE_Q14(79.2)},
	{MAKE_Q14(28.8), MAKE_Q14(33.5), MAKE_Q14(44.2), MAKE_Q14(54.8),	// Kansas City
	 MAKE_Q14(64.5), MAKE_Q14(73.5), MAKE_Q14(78.3), MAKE_Q14(77.0),
	 MAKE_Q14(68.1), MAKE_Q14(56.3), MAKE_Q14(43.6), MAKE_Q14(31.4)},
	{MAKE_Q14(4.6), MAKE_Q14(5.1), MAKE_Q14(8.4), MAKE_Q14(14.2),		// Kyoto
	 MAKE_Q14(19.0), MAKE_Q14(23.0), MAKE_Q14(26.8), MAKE_Q14(28.2),
	 MAKE_Q14(24.1), MAKE_Q14(17.8), MAKE_Q14(12.1), MAKE_Q14(7.0)},
	{MAKE_Q14(17.4), MAKE_Q14(18.1), MAKE_Q14(19.7), MAKE_Q14(22.1),	// La Paz
	 MAKE_Q14(24.5), MAKE_Q14(27.1), MAKE_Q14(29.7), MAKE_Q14(30.2),
	 MAKE_Q14(29.3), MAKE_Q14(26.2), MAKE_Q14(22.0), MAKE_Q14(18.6)},
	{MAKE_Q14(41.3), MAKE_Q14(45.5), MAKE_Q14(54.0), MAKE_Q14(63.0),	// Memphis
	 MAKE_Q14(71.7), MAKE_Q14(79.6), MAKE_Q14(82.7), MAKE_Q14(82.1),
	 MAKE_Q14(75.2), MAKE_Q14(64.1), MAKE_Q14(53.2), MAKE_Q14(43.6)},
	{MAKE_Q14(13.8), MAKE_Q14(16.5), MAKE_Q14(22.1), MAKE_Q14(28.7),	// New Delhi
	 MAKE_Q14(32.8), MAKE_Q14(34.0), MAKE_Q14(30.9), MAKE_Q14(29.7),
	 MAKE_Q14(29.0), MAKE_Q14(26.1), MAKE_Q14(20.5), MAKE_Q14(15.3)},
	{MAKE_Q14(10.6), MAKE_Q14(10.6), MAKE_Q14(13.1), MAKE_Q14(17.1),	// Nicosia
	 MAKE_Q14(22.3), MAKE_Q14(26.9), MAKE_Q14(29.7), MAKE_Q14(29.4),
	 MAKE_Q14(26.2), MAKE_Q14(22.3), MAKE_Q14(16.3), MAKE_Q14(12.0)},
	{MAKE_Q14(16.0), MAKE_Q14(18.2), MAKE_Q14(23.1), MAKE_Q14(27.9),	// Reggane
	 MAKE_Q14(32.2), MAKE_Q14(36.4), MAKE_Q14(39.8), MAKE_Q14(38.4),
	 MAKE_Q14(35.5), MAKE_Q14(29.2), MAKE_Q14(22.0), MAKE_Q14(17.8)},
	{MAKE_Q14(77.6), MAKE_Q14(77.9), MAKE_Q14(78.9), MAKE_Q14(80.3),	// San Juan
	 MAKE_Q14(81.9), MAKE_Q14(83.3), MAKE_Q14(83.4), MAKE_Q14(83.7),
	 MAKE_Q14(83.5), MAKE_Q14(82.6), MAKE_Q14(80.6), MAKE_Q14(76.7)},
	{MAKE_Q14(60.6), MAKE_Q14(63.2), MAKE_Q14(67.1), MAKE_Q14(71.7),	// Tampa
	 MAKE_Q14(78.2), MAKE_Q14(82.0), MAKE_Q14(82.8), MAKE_Q14(83.0),
	 MAKE_Q14(81.5), MAKE_Q14(76.0), MAKE_Q14(69.0), MAKE_Q14(63.0)},
	{MAKE_Q14(-21.6), MAKE_Q14(-16.6), MAKE_Q14(-7.4), MAKE_Q14(2.0),	// Ulaanbaatar
	 MAKE_Q14(10.1), MAKE_Q14(15.7), MAKE_Q14(18.2), MAKE_Q14(16.0),
	 MAKE_Q14(9.6), MAKE_Q14(0.5), MAKE_Q14(-11.9), MAKE_Q14(-19.0)},
	{MAKE_Q14(-38.6), MAKE_Q14(-33.8), MAKE_Q14(-20.1), MAKE_Q14(-4.8),	// Yakutsk
	 MAKE_Q14(7.5), MAKE_Q14(16.4), MAKE_Q14(19.5), MAKE_Q14(15.2),
	 MAKE_Q14(6.1), MAKE_Q14(-7.8), MAKE_Q14(-27.0), MAKE_Q14(-37.6)}
	};


t_cityinfo info_HNord[NUMCITIESHNORD] = {
	{"Alexandria", 'C'},				// Egypt
	{"Andorra la Vella", 'C'},			// Andorra
	{"Beijing", 'C'},					// China
	{"Calgary", 'C'},					// Canada
	{"Dikson", 'C'},					// Russia
	{"Djibouti", 'C'},					// Djibouti
	{"George Town", 'F'},				// Cayman Islands
	{"Kansas City", 'F'},				// USA
	{"Kyoto", 'C'},						// Japan
	{"La Paz", 'C'},					// Mexico
	{"Memphis", 'F'},					// USA
	{"New Delhi", 'C'},					// India
	{"Nicosia", 'C'},					// Cyprus
	{"Reggane", 'C'},					// Argelia
	{"San Juan", 'F'},					// Puerto Rico
	{"Tampa", 'F'},						// USA
	{"Ulaanbaatar", 'C'},				// Mongolia
	{"Yakutsk", 'C'}					// Russia
};	


Q14 tempHSud_2020[NUMCITIESHSUD][12] = {
	{MAKE_Q14(23.2), MAKE_Q14(23.3), MAKE_Q14(20.9), MAKE_Q14(17.6),	// Adelaide
	 MAKE_Q14(13.5), MAKE_Q14(12.1), MAKE_Q14(11.4), MAKE_Q14(12.4),
	 MAKE_Q14(14.4), MAKE_Q14(16.7), MAKE_Q14(19.7), MAKE_Q14(21.3)},
	{MAKE_Q14(15.0), MAKE_Q14(14.8), MAKE_Q14(11.9), MAKE_Q14(7.9),		// Bariloche
	 MAKE_Q14(4.9), MAKE_Q14(2.9), MAKE_Q14(2.1), MAKE_Q14(3.0),
	 MAKE_Q14(5.1), MAKE_Q14(8.0), MAKE_Q14(10.8), MAKE_Q14(13.5)},
	{MAKE_Q14(20.6), MAKE_Q14(20.1), MAKE_Q14(17.6), MAKE_Q14(13.4),	// Canberra
	 MAKE_Q14(9.4), MAKE_Q14(6.7), MAKE_Q14(5.7), MAKE_Q14(7.0),
	 MAKE_Q14(9.8), MAKE_Q14(12.8), MAKE_Q14(15.8), MAKE_Q14(18.8)},
	{MAKE_Q14(27.7), MAKE_Q14(27.6), MAKE_Q14(27.4), MAKE_Q14(27.4),	// Dili
	 MAKE_Q14(27.0), MAKE_Q14(26.8), MAKE_Q14(25.5), MAKE_Q14(25.1),
	 MAKE_Q14(25.4), MAKE_Q14(26.0), MAKE_Q14(27.2), MAKE_Q14(27.4)},
	{MAKE_Q14(20.8), MAKE_Q14(20.8), MAKE_Q14(20.0), MAKE_Q14(18.9),	// Fianarantsoa
	 MAKE_Q14(16.7), MAKE_Q14(14.5), MAKE_Q14(14.0), MAKE_Q14(14.4),
	 MAKE_Q14(16.2), MAKE_Q14(18.3), MAKE_Q14(19.7), MAKE_Q14(20.4)},
	{MAKE_Q14(25.9), MAKE_Q14(25.3), MAKE_Q14(24.1), MAKE_Q14(21.2),	// Ghanzi
	 MAKE_Q14(17.6), MAKE_Q14(14.3), MAKE_Q14(14.1), MAKE_Q14(17.1),
	 MAKE_Q14(21.5), MAKE_Q14(24.6), MAKE_Q14(25.7), MAKE_Q14(26.1)},
	{MAKE_Q14(23.3), MAKE_Q14(23.7), MAKE_Q14(23.1), MAKE_Q14(21.9),	// Hanga Roa
	 MAKE_Q14(20.1), MAKE_Q14(18.9), MAKE_Q14(18.0), MAKE_Q14(17.9),
	 MAKE_Q14(18.3), MAKE_Q14(19.0), MAKE_Q14(20.4), MAKE_Q14(21.8)},
	{MAKE_Q14(21.0), MAKE_Q14(20.7), MAKE_Q14(20.3), MAKE_Q14(18.8),	// Harare
	 MAKE_Q14(16.1), MAKE_Q14(13.7), MAKE_Q14(13.4), MAKE_Q14(15.5),
	 MAKE_Q14(18.6), MAKE_Q14(20.8), MAKE_Q14(21.2), MAKE_Q14(20.9)},
	{MAKE_Q14(27.1), MAKE_Q14(26.9), MAKE_Q14(27.1), MAKE_Q14(27.3),	// Jayapura
	 MAKE_Q14(27.2), MAKE_Q14(26.9), MAKE_Q14(26.4), MAKE_Q14(26.6),
	 MAKE_Q14(26.9), MAKE_Q14(27.2), MAKE_Q14(27.3), MAKE_Q14(27.0)},
	{MAKE_Q14(19.5), MAKE_Q14(19.0), MAKE_Q14(18.0), MAKE_Q14(15.3),	// Johannesburg
	 MAKE_Q14(12.6), MAKE_Q14(9.6), MAKE_Q14(10.0), MAKE_Q14(12.5),
	 MAKE_Q14(15.9), MAKE_Q14(17.1), MAKE_Q14(17.9), MAKE_Q14(19.0)},
	{MAKE_Q14(15.2), MAKE_Q14(14.8), MAKE_Q14(12.4), MAKE_Q14(9.2),		// Lake Tekapo
	 MAKE_Q14(5.9), MAKE_Q14(2.6), MAKE_Q14(1.4), MAKE_Q14(3.6),
	 MAKE_Q14(6.5), MAKE_Q14(8.8), MAKE_Q14(11.1), MAKE_Q14(13.2)},
	{MAKE_Q14(23.0), MAKE_Q14(22.5), MAKE_Q14(20.6), MAKE_Q14(17.2),	// Montevideo
	 MAKE_Q14(14.0), MAKE_Q14(11.1), MAKE_Q14(10.9), MAKE_Q14(11.7),
	 MAKE_Q14(13.4), MAKE_Q14(16.0), MAKE_Q14(18.6), MAKE_Q14(21.3)},
	{MAKE_Q14(27.4), MAKE_Q14(27.3), MAKE_Q14(27.1), MAKE_Q14(27.0),	// Port Moresby
	 MAKE_Q14(26.9), MAKE_Q14(26.1), MAKE_Q14(25.7), MAKE_Q14(26.1),
	 MAKE_Q14(26.5), MAKE_Q14(27.5), MAKE_Q14(27.6), MAKE_Q14(27.8)},
	{MAKE_Q14(10.8), MAKE_Q14(10.3), MAKE_Q14(8.5), MAKE_Q14(6.2),		// Punta Arenas
	 MAKE_Q14(3.7), MAKE_Q14(1.5), MAKE_Q14(1.4), MAKE_Q14(2.3),
	 MAKE_Q14(4.2), MAKE_Q14(6.4), MAKE_Q14(8.4), MAKE_Q14(9.9)},
	{MAKE_Q14(26.3), MAKE_Q14(26.6), MAKE_Q14(26.0), MAKE_Q14(24.4),	// Rio de Janeiro
	 MAKE_Q14(22.8), MAKE_Q14(21.8), MAKE_Q14(21.3), MAKE_Q14(21.8),
	 MAKE_Q14(22.2), MAKE_Q14(22.9), MAKE_Q14(24.0), MAKE_Q14(25.3)},
	{MAKE_Q14(9.5), MAKE_Q14(8.9), MAKE_Q14(8.1), MAKE_Q14(6.1),		// Stanley
	 MAKE_Q14(3.9), MAKE_Q14(2.2), MAKE_Q14(1.9), MAKE_Q14(2.2),
	 MAKE_Q14(3.9), MAKE_Q14(5.3), MAKE_Q14(7.0), MAKE_Q14(8.1)},
	{MAKE_Q14(16.2), MAKE_Q14(15.7), MAKE_Q14(15.8), MAKE_Q14(15.5),	// Sucre
	 MAKE_Q14(14.9), MAKE_Q14(13.8), MAKE_Q14(13.9), MAKE_Q14(14.9),
	 MAKE_Q14(16.2), MAKE_Q14(16.9), MAKE_Q14(17.3), MAKE_Q14(16.7)},
	{MAKE_Q14(9.6), MAKE_Q14(9.3), MAKE_Q14(7.7), MAKE_Q14(5.7),		// Ushuaia
	 MAKE_Q14(3.2), MAKE_Q14(1.7), MAKE_Q14(1.3), MAKE_Q14(2.2),
	 MAKE_Q14(4.1), MAKE_Q14(6.2), MAKE_Q14(7.8), MAKE_Q14(9.1)},
	{MAKE_Q14(16.9), MAKE_Q14(17.2), MAKE_Q14(15.8), MAKE_Q14(13.7),	// Wellington
	 MAKE_Q14(11.7), MAKE_Q14(9.7), MAKE_Q14(8.9), MAKE_Q14(9.4),
	 MAKE_Q14(10.8), MAKE_Q14(12.0), MAKE_Q14(13.5), MAKE_Q14(15.4)}
};


t_cityinfo info_HSud[NUMCITIESHSUD] = {
	{"Adelaide", 'C'},					// Australia
	{"Bariloche", 'C'},					// Argentina
	{"Canberra", 'C'},					// Australia
	{"Dili", 'C'},						// East Timor
	{"Fianarantsoa", 'C'},				// Madagascar
	{"Ghanzi", 'C'},					// Botswana
	{"Hanga Roa", 'C'},					// Chile
	{"Harare", 'C'},					// Zimbabwe
	{"Jayapura", 'C'},					// Indonesia
	{"Johannesburg", 'C'},				// South Africa
	{"Lake Tekapo", 'C'},				// New Zealand
	{"Montevideo", 'C'},				// Uruguay
	{"Port Moresby", 'C'},				// Papua New Guinea
	{"Punta Arenas", 'C'},				// Chile
	{"Rio de Janeiro", 'C'},			// Brazil
	{"Stanley", 'C'},					// Falkland Islands
	{"Sucre", 'C'},						// Bolivia
	{"Ushuaia", 'C'},					// Argentina
	{"Wellington", 'C'}					// New Zealand
};

