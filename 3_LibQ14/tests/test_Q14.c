/*----------------------------------------------------------------
|   Testing Q14 arithmetic routines;
| ----------------------------------------------------------------
|	pere.millan@urv.cat
|	santiago.romani@urv.cat
|	(Març 2021)
| ----------------------------------------------------------------*/

#include "Q14.h"

enum Q14_ops {add, sub, mul, div};

/* type definition of the structured record that holds the test case values */
typedef struct {
	enum Q14_ops op;	/* add / sub / mul / div */
	Q14 num1;			/* 1st input parameter of the operation */
	Q14 num2;			/* 2nd input parameter of the operation */
	Q14 result;			/* Expected result of the operation */
	unsigned char ovf;	/* Expected overflow of the operation */
} test_ops_struct;

/* the list of test case values */
test_ops_struct test_case[] =
	/* Tests operació SUMA (add) */
{{add, 0, 0, 0, 0},						/*  0: 0.0 + 0.0 = 0.0, ovflow 0 */
 {add, MAKE_Q14(1.125), 				/*  1: 1.125 + 2.5 = 3.625, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(3.625), 0},
 {add, MAKE_Q14(-1.125), 				/*  2: -1.125 + 2.5 = 1.375, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(1.375), 0},
 {add, MAKE_Q14(1.125), 				/*  3: 1.125 + -2.5 = -1.375, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(-1.375), 0},
 {add, MAKE_Q14(-1.125), 				/*  4: -1.125 + -2.5 = -3.625, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(-3.625), 0},
 {add, MAKE_Q14(123456.125), 			/*  5: Suma de positius amb OVERFLOW */
	   MAKE_Q14(54321.5),
	   MAKE_Q14(46705.625)|0x80000000, 1},
 {add, MAKE_Q14(-123456.125), 			/*  6: Suma de negatius amb OVERFLOW */
	   MAKE_Q14(-54321.5),
	   MAKE_Q14(-46705.625)&0x7FFFFFFF, 1},

	/* Tests operació RESTA (sub) */
 {sub, 0, 0, 0, 0},						/*  7: 0.0 - 0.0 = 0.0, ovflow 0 */
 {sub, MAKE_Q14(1.125), 				/*  8: 1.125 - 2.5 = -1.375, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(-1.375), 0},
 {sub, MAKE_Q14(-1.125), 				/*  9: -1.125 - 2.5 = -3.625, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(-3.625), 0},
 {sub, MAKE_Q14(1.125), 				/* 10: 1.125 - -2.5 = 3.625, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(3.625), 0},
 {sub, MAKE_Q14(-1.125), 				/* 11: -1.125 - -2.5 = 1.375, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(1.375), 0},
 {sub, MAKE_Q14(123456.125), 			/* 12: Resta a positiu amb OVERFLOW */
	   MAKE_Q14(-54321.5),
	   MAKE_Q14(46705.625)|0x80000000, 1},
 {sub, MAKE_Q14(-123456.125), 			/* 13: Resta a negatiu amb OVERFLOW */
	   MAKE_Q14(54321.5),
	   MAKE_Q14(-46705.625)&0x7FFFFFFF, 1},

	/* Tests operació MULTIPLICACIÓ (mul) */
 {mul, 0, 0, 0, 0},						/* 14: 0.0 * 0.0 = 0.0, ovflow 0 */
 {mul, MAKE_Q14(1.125), 				/* 15: 1.125 * 2.5 = 2.8125, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(2.8125), 0},
 {mul, MAKE_Q14(-1.125), 				/* 16: -1.125 * 2.5 = -2.8125, ovflow 0 */
	   MAKE_Q14(2.5),
	   MAKE_Q14(-2.8125), 0},
 {mul, MAKE_Q14(1.125), 				/* 17: 1.125 * -2.5 = -2.8125, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(-2.8125), 0},
 {mul, MAKE_Q14(-1.125), 				/* 18: -1.125 * -2.5 = 2.8125, ovflow 0 */
	   MAKE_Q14(-2.5),
	   MAKE_Q14(2.8125), 0},
 {mul, MAKE_Q14(123456.125), 			/* 19: Producte de positius amb OVERFLOW */
	   MAKE_Q14(2.5),
	   0x2D681400, 1},						/* 0x1 2D68 1400 (overflow al bit 32) */
 {mul, MAKE_Q14(-123456.125), 			/* 20: Producte de negatius amb OVERFLOW */
	   MAKE_Q14(-2.5),
	   0x2D681400, 1},						/* 0x1 2D68 1400 (overflow al bit 32) */
 {mul, MAKE_Q14(123456.125), 			/* 21: Producte de positius amb OVERFLOW */
	   MAKE_Q14(1.25),
	   0x96B40A00, 1},						/* overflow al bit 31 */
 {mul, MAKE_Q14(-123456.125), 			/* 22: Producte de negatius amb OVERFLOW */
	   MAKE_Q14(-1.25),
	   0x96B40A00, 1},						/* overflow al bit 31 */
 {mul, MAKE_Q14(1024.0),				/* 23: Producte positiu amb OVERFLOW total */
	   MAKE_Q14(1024.0),
	   0, 1},								/* 0x00010000 00000000 overflow a bit 48 */
 {mul, MAKE_Q14(-512.0),				/* 24: Producte negatiu amb OVERFLOW total */
	   MAKE_Q14(2048.0),
	   0, 1},								/* 0xFFFFFFFC 00000000 overflow a bits 34+ */
 {mul, 0x800000, 0x800000, 0, 1},		/* 25: Overflow al bit 32 */

	/* Tests operació DIVISIÓ (div) */
 {div, 0, 0, 0, 1},						/* 26: Div/ZERO -> 0.0, i OVERFLOW */
 {div, MAKE_Q14(123.0), 				/* 27: 123.0 / 8.0 = 15.375, ovflow 0 */
	   MAKE_Q14(8.0),
	   MAKE_Q14(15.375), 0},
 {div, MAKE_Q14(123.0), 				/* 28: 123.0 / -8.0 = -15.375, ovflow 0 */
	   MAKE_Q14(-8.0),
	   MAKE_Q14(-15.375), 0},
 {div, MAKE_Q14(-123.0), 				/* 29: -123.0 / 8.0 = -15.375, ovflow 0 */
	   MAKE_Q14(8.0),
	   MAKE_Q14(-15.375), 0},
 {div, MAKE_Q14(-123.0), 				/* 30: -123.0 / -8.0 = 15.375, ovflow 0 */
	   MAKE_Q14(-8.0),
	   MAKE_Q14(15.375), 0},
 {div, MAKE_Q14(123456.125), 			/* 31: Divisió de positius amb OVERFLOW */
	   MAKE_Q14(0.5),
	   0xF1201000, 1},						/* overflow al bit 31 */
 {div, MAKE_Q14(123456.125), 			/* 32: Divisió de positius amb OVERFLOW */
	   MAKE_Q14(0.25),
	   0xE2402000, 1},						/* 0x1 E240 2000 (overflow als bits 31,32) */
 {div, MAKE_Q14(-123456.125), 			/* 33: Divisió de negatius amb OVERFLOW */
	   MAKE_Q14(-0.5),
	   0xF1201000, 1},						/* overflow al bit 31 */
 {div, MAKE_Q14(123456.125), 			/* 34: Divisió negativa amb OVERFLOW */
	   MAKE_Q14(-0.5),
	   0x0EDFF000, 1},						/* overflow als bits 31+ */
 {div, MAKE_Q14(-123456.125), 			/* 35: Divisió negativa amb OVERFLOW */
	   MAKE_Q14(0.25),
	   0x1DBFE000, 1},						/* 0x2 1DBF E000 (overflow a bits 31+) */
 {div, MAKE_Q14(123456.125), 			/* 36: Divisió positiva amb OVERFLOW */
	   MAKE_Q14(0.0625),
	   0x89008000, 1},						/* 0x7 8900 8000 (overflow a bits 31+) */
 {div, MAKE_Q14(123456.125), 			/* 37: Divisió positiva sense overflow */
	   MAKE_Q14(128.0),
	   0x00F12010, 0}						/* 964,5009765625 */
};


int main(void)
{
	unsigned int i;					/* loop index */
	Q14 result;						/* routine results */
	unsigned char overflow;			/* possible overflow */
	unsigned char perf_op;			/* =1 if operation has been performed */
	unsigned int num_ops_ok = 0;	/* number of right tests (op result) */
	unsigned int num_ovf_ok = 0;	/* number of right tests (overflow result) */
	unsigned int num_tests = 		/* total number of tests */
					sizeof(test_case) / sizeof(test_ops_struct);
	int num_errors = 0;				/* number of wrong tests (result or overflow) */

	/********* evaluate the list of test case values *********/
	for (i = 0; i < num_tests; i++)
	{
		perf_op = 1;				// assume operation will be performed
		overflow = 123;				// fake value to be overwritten by routine
		switch (test_case[i].op)
		{
			case add:
				result = add_Q14(test_case[i].num1, test_case[i].num2, &overflow);
				break;
			case sub:
				result = sub_Q14(test_case[i].num1, test_case[i].num2, &overflow);
				break;
			case mul:
				result = mul_Q14(test_case[i].num1, test_case[i].num2, &overflow);
				break;
			case div:
				result = div_Q14(test_case[i].num1, test_case[i].num2, &overflow);
				break;
			default:
/* BREAKPOINT: codi operació incorrecte a test_case[i].op */
				num_errors++;
				perf_op = 0;
				break;
		}
		if (perf_op)	// evaluate return info only when operation performed
		{
			if (result == test_case[i].result)
				num_ops_ok++;
			else
/* BREAKPOINT: resultat operació incorrecte */
				num_errors++;
			
			if (overflow == test_case[i].ovf)
				num_ovf_ok++;
			else
/* BREAKPOINT: resultat overflow incorrecte */
				num_errors++;
		}
	}

/* TESTING POINT: check if number of ok tests (num_ops_ok, num_ovf_ok) 
				  is equal to number of total tests (num_tests)
				  and there ara no errors (num_errors is 0)
	(gdb) disp num_ops_ok
	(gdb) disp num_ovf_ok
	(gdb) disp num_tests
	(gdb) disp num_errors
*/

/* BREAKPOINT */
	return(0);
}
