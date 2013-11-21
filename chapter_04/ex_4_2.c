/*
 * Exercise 4-2. Extend atof to handle scientific notation of the
 * form 123.45e-6 where a floating-point number may be followed by
 * e or E and an optionally signed exponent.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof:  convert string s to double */
double a_to_f(char s[])
{
	double val, power,exp;
	int i, sign,exps;

	for (i = 0; isspace(s[i]); i++)  /* skip white space */
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	/* handle the exponent part */
	exp = 0;
	if (s[i] == 'e' || s[i] == 'E')
		i++;

	exps = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	while(isdigit(s[i])) {
		exp = exp * 10+(s[i] - '0');
		i++;
	}

	return sign * ( (val / power) * pow(10,exps*exp));
}


int main() {
	double res;
	res = a_to_f("10.33E-1");
	printf ("res = %llf\n", res);
	return 0;
}
