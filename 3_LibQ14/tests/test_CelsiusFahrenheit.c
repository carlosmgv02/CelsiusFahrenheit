/*----------------------------------------------------------------
|   Testing temperature-scale conversion routines;
| ----------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Abril 2021)
| ----------------------------------------------------------------*/

#include "Q14.h"				/* external declarations of types, defines and
								   macro for dealing with Q14 numbers */
#include "CelsiusFahrenheit.h"	/* external declarations of function
								   prototypes for temperature conversions */


/* type definition of the structured record that holds the test case values */
typedef struct {
	char scale;			/* letter of input scale ('C' or 'F') */
	Q14 input;			/* input temperature value for conversion */
	Q14 xresult;		/* Expected result of the operation */
} test_ops_struct;

/* the list of test case values */
test_ops_struct test_case[] =
	/* Tests Celsius -> Fahrenheit */
{{'C', MAKE_Q14(0.0),					/*  0: 0.0 �C = 32.0 �F */
	   MAKE_Q14(32.0)},
 {'C', MAKE_Q14(0.00006103515625), 		/*  1: minimal fraction in �C */
	   MAKE_Q14(32.00010986328125)},		// result = 32 + converted fract.
 {'C', MAKE_Q14(-1.125), 				/*  2: small negative �C (positive �F) */
	   MAKE_Q14(29.975)},
 {'C', MAKE_Q14(31.1), 					/*  3: large positive �C */
	   MAKE_Q14(87.98)},
 {'C', MAKE_Q14(-40.0), 				/*  4: equal �C and �F */
	   MAKE_Q14(-40.0)},
 {'C', MAKE_Q14(72799.223), 			/*  5: max. convertable �C (aprox.) */
	   MAKE_Q14(131070.6014)},
 {'C', MAKE_Q14(-273.15), 				/*  6: absolute min. �C temperature */
	   MAKE_Q14(-459.67)},
 {'C', MAKE_Q14(-0.00006103515625),		/*  7: minimal neg. franction in �C */
 	   MAKE_Q14(32.00010986328125)},		// result = 32 + abs(converted fract.)
 {'C', MAKE_Q14(3227),					/*  8: rocket engine temperature in �C */
 	   MAKE_Q14(5840.6)},
 {'C', MAKE_Q14(56.7),					//  9: highest temp. ever recorded on earth 
 	   MAKE_Q14(134.06)},					//  in �C 
 {'C', MAKE_Q14(1700),					// 10: temp. necessary to transform sand into
 	   MAKE_Q14(3092)},						//  glass in �C 
 {'C', MAKE_Q14(100),					/* 11: water boiling point in �C */
 	   MAKE_Q14(212)},


	/* Tests  Fahrenheit -> Celsius */
 {'F', MAKE_Q14(0.0),					/* 12: 0.0 �F = -17.777... �C */
	   MAKE_Q14(-17.7777)},
 {'F', MAKE_Q14(-0.00006103515625), 	/* 13: minimal neg. fraction in �F */
	   MAKE_Q14(-17.7778116861979)},		// result = -17 - converted fract.
 {'F', MAKE_Q14(32.0), 					/*  14: 0 �C */
	   MAKE_Q14(0)},
 {'F', MAKE_Q14(31.999), 				/* 15: small converted �C */
	   MAKE_Q14(-0.0005555)},
 {'F', MAKE_Q14(-40.0), 				/* 16: equal �F and �C */
	   MAKE_Q14(-40.0)},
 {'F', MAKE_Q14(131070.5996), 			/* 17: max. convertable �F (aprox.) */
	   MAKE_Q14(72799.222)},
 {'F', MAKE_Q14(-459.67), 				/* 18: absolute min. �F temperature */
	   MAKE_Q14(-273.15)},
 {'F', MAKE_Q14(451), 					/* 19: temperature for burning books*/
	   MAKE_Q14(232.7777)},
 {'F', MAKE_Q14(98.6),					/* 20: normal human body temperature */
 	   MAKE_Q14(37)},	
 {'F', MAKE_Q14(122),					/* 21: normal CPU temp. when is IDLE */ 
 	   MAKE_Q14(50)},
};


unsigned int abs_value(int x) { return(x < 0 ? -x : x); }


int main(void)
{
	unsigned int i;						/* loop index */
	Q14 result;							/* routine results */
	unsigned int num_ok = 0;			/* number of right tests */
	unsigned int num_tests = 			/* total number of tests */
					sizeof(test_case) / sizeof(test_ops_struct);
	unsigned int error, rel_error;		/* marginal errors */

	/********* evaluate the list of test case values *********/
	for (i = 0; i < num_tests; i++)
	{
		if (test_case[i].scale == 'C')
			result = Celsius2Fahrenheit(test_case[i].input);
		else
			result = Fahrenheit2Celsius(test_case[i].input);
		
		error = abs_value(result - test_case[i].xresult);
		rel_error = abs_value(result >> 15);
		if (error <= rel_error)			// allow a relative degree of error
			num_ok++;					// (< 0.005% of result)
	}

/* TESTING POINT: check if number of ok tests 
				  is equal to number of total tests
	(gdb) p num_ok
	(gdb) p num_tests
*/

/* BREAKPOINT */
	return(0);
}
