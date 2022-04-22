/*----------------------------------------------------------------
|   Testing temperature data processing;
| ----------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(April 2021)
| ----------------------------------------------------------------*/

#include "Q14.h"				/* external declarations of types, defines and
								   macro for dealing with Q14 numbers */
#include "avgmaxmintemp.h"		/* mmres: return type from avgmaxmin routines */

#define NUM_TEST_ROWS	6

Q14 test_data[NUM_TEST_ROWS][12] = {
	{MAKE_Q14(13.4), MAKE_Q14(13.4), MAKE_Q14(20.0), MAKE_Q14(13.4),	// several replicated min and max
	 MAKE_Q14(20.0), MAKE_Q14(20.0), MAKE_Q14(25.9), MAKE_Q14(25.9),
	 MAKE_Q14(20.0), MAKE_Q14(20.0), MAKE_Q14(20.0), MAKE_Q14(25.9)},
	{MAKE_Q14(-2.2), MAKE_Q14(-3.5), MAKE_Q14(-5.8), MAKE_Q14(-7.5),	// all negatives
	 MAKE_Q14(-11.5), MAKE_Q14(-15.4), MAKE_Q14(-18.8), MAKE_Q14(-18.5),
	 MAKE_Q14(-14.9), MAKE_Q14(-10.3), MAKE_Q14(-5.7), MAKE_Q14(-3.0)},
	{MAKE_Q14(0.1), MAKE_Q14(0.3), MAKE_Q14(0.7), MAKE_Q14(0.8),		// all values around 0� Celsius
	 MAKE_Q14(0.8), MAKE_Q14(-0.9), MAKE_Q14(-0.7), MAKE_Q14(0.5),
	 MAKE_Q14(0.0), MAKE_Q14(0.7), MAKE_Q14(0.5), MAKE_Q14(-0.9)},
	{MAKE_Q14(12.8), MAKE_Q14(15.0), MAKE_Q14(18.1), MAKE_Q14(22.2),	// Tamanrasset, Algeria
	 MAKE_Q14(26.1), MAKE_Q14(28.9), MAKE_Q14(28.7), MAKE_Q14(28.2),
	 MAKE_Q14(26.5), MAKE_Q14(22.4), MAKE_Q14(17.3), MAKE_Q14(13.9)},
	{MAKE_Q14(18.0), MAKE_Q14(18.8), MAKE_Q14(19.4), MAKE_Q14(19.2),	// Nairobi, Kenya 
	 MAKE_Q14(17.8), MAKE_Q14(16.3), MAKE_Q14(15.6), MAKE_Q14(15.9),
	 MAKE_Q14(17.3), MAKE_Q14(18.5), MAKE_Q14(18.4), MAKE_Q14(18.1)},
	{MAKE_Q14(11.8), MAKE_Q14(12.4), MAKE_Q14(14.2), MAKE_Q14(15.8),	// Barcelona, Spain 
	 MAKE_Q14(19.3), MAKE_Q14(23.0), MAKE_Q14(25.7), MAKE_Q14(26.1),
	 MAKE_Q14(23.0), MAKE_Q14(19.5), MAKE_Q14(14.9), MAKE_Q14(12.3)},
};

/* type definition of the structured record that holds the test case values */
typedef struct {
	unsigned char op;	/* type of operation ('C': by city, 'M': by month) */
	unsigned short id;	/* index to be checked (city or month) */
	Q14 xavg;			/* expected average */
	t_maxmin xmm;		/* expected max-min results */
} test_struct;

/* the list of test case values */
test_struct test_case[] =
	/* Tests for cities */
{{'C', 0, MAKE_Q14(19.8),				/*  0: several replicated min and max */
	{MAKE_Q14(13.4), MAKE_Q14(25.9),
	 MAKE_Q14(56.12), MAKE_Q14(78.62),
	 0, 6}},
 {'C', 1, MAKE_Q14(-9.8),				/*  1: all negatives */
	{MAKE_Q14(-18.8), MAKE_Q14(-2.2),
	 MAKE_Q14(-1.84), MAKE_Q14(28.04),
	 6, 0}},
 {'C', 2, MAKE_Q14(0.2),				/*  2: all values around 0� Celsius */
	{MAKE_Q14(-0.9), MAKE_Q14(0.8),
	 MAKE_Q14(30.38), MAKE_Q14(33.44),
	 5, 3}},
 {'C', 3, MAKE_Q14(21.7),				//  3: values from the city Tamanrasset, Algeria
 	{MAKE_Q14(12.8), MAKE_Q14(28.9),
	 MAKE_Q14(55.04), MAKE_Q14(84.02),
	 0, 5}},
 {'C', 4, MAKE_Q14(17.775),				// 4: values from the city Nairobi, Kenya 
 	{MAKE_Q14(15.6), MAKE_Q14(19.4),
	 MAKE_Q14(60.08), MAKE_Q14(66.92),
	 6, 2}},	
 {'C', 5, MAKE_Q14(18.16666667),		// 5: values from the city Barcelona, Spain
 	{MAKE_Q14(11.8), MAKE_Q14(26.1),
	 MAKE_Q14(53.24), MAKE_Q14(78.98),
	 0, 7}},

	/* Tests  for months */
 {'M', 0, MAKE_Q14(8.983333),				/*  6: first column (January) */
	{MAKE_Q14(-2.2), MAKE_Q14(18),
	 MAKE_Q14(28.04), MAKE_Q14(64.4),
	 1, 4}},
 {'M', 6, MAKE_Q14(12.733335),				/*  7: middle column (July) */
	{MAKE_Q14(-18.799999), MAKE_Q14(28.700001),
	 MAKE_Q14(-1.8399982), MAKE_Q14(83.6600018),
	 1, 3}},
 {'M', 11, MAKE_Q14(11.05),					/*  8: last column (Desember) */
	{MAKE_Q14(-3.0), MAKE_Q14(25.9),
	 MAKE_Q14(26.6), MAKE_Q14(78.62),
	 1, 0}},
 {'M', 5, MAKE_Q14(11.98),					/* 9: May month */
 	{MAKE_Q14(-15.4), MAKE_Q14(28.9),
	 MAKE_Q14(4.28), MAKE_Q14(84.02),
	 1, 3}},
 {'M', 7, MAKE_Q14(13.0166),				/* 10: July month */
 	{MAKE_Q14(-18.5), MAKE_Q14(28.200001),
	 MAKE_Q14(-1.3), MAKE_Q14(82.76),
	 1, 3}},
 {'M', 2, MAKE_Q14(11.099999),				/* 11: February month */
 	{MAKE_Q14(-5.8), MAKE_Q14(20),
	 MAKE_Q14(21.56), MAKE_Q14(68),
	 1, 0}},
};


unsigned int abs_value(int x) { return(x < 0 ? -x : x); }

unsigned char error_bits(Q14 avg, t_maxmin *maxmin, Q14 xavg, t_maxmin *xmm)
{
	unsigned char nerr = 0;
	unsigned int error;						/* marginql error */
	
	error = abs_value(avg - xavg);
	if (error > 1024)					/* average divergence error */
		nerr |= 1;						// set bit 0

	error = abs_value(maxmin->tmin_C - xmm->tmin_C);
	if (error > 4)						/* min temp. (�C) divergence error */
		nerr |= 2;						// set bit 1

	error = abs_value(maxmin->tmax_C - xmm->tmax_C);
	if (error > 4)						/* max temp. (�C) divergence error */
		nerr |= 4;						// set bit 2
	
	error = abs_value(maxmin->tmin_F - xmm->tmin_F);
	if (error > 1024)					/* min temp. (�F) divergence error */
		nerr |= 8;						// set bit 3
	
	error = abs_value(maxmin->tmax_F - xmm->tmax_F);
	if (error > 1024)					/* max temp. (�F) divergence error */
		nerr |= 16;						// set bit 4
	
	if (maxmin->id_min != xmm->id_min) /* min index divergence error */
		nerr |= 32;						// set bit 5
	
	if (maxmin->id_max != xmm->id_max) /* max index divergence error */
		nerr |= 64;						// set bit 6

	return(nerr);
}

int main(void)
{
	unsigned int i;						/* loop index */
	Q14 avg;							/* routine results */
	t_maxmin maxmin;
	unsigned int num_ok = 0;			/* number of right tests */
	unsigned int num_tests = 			/* total number of tests */
					sizeof(test_case) / sizeof(test_struct);

	/********* evaluate the list of test case values *********/
	for (i = 0; i < num_tests; i++)
	{
		if (test_case[i].op == 'C')
			avg = avgmaxmin_city(test_data, NUM_TEST_ROWS, test_case[i].id, &maxmin);
		else
			avg = avgmaxmin_month(test_data, NUM_TEST_ROWS, test_case[i].id, &maxmin);
		
		if (error_bits(avg, &maxmin, test_case[i].xavg, &test_case[i].xmm) == 0)
			num_ok++;
	}

/* TESTING POINT: check if number of ok tests 
				  is equal to number of total tests
	(gdb) p num_ok
	(gdb) p num_tests
*/

/* BREAKPOINT */
	return(0);
}
