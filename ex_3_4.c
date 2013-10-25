/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2wordsize-1). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs.
 */


/*
 * The reason here becase the minimum integer when negated will result in another
 * negative integer with the same value. This happen because we use the two-complement
 * system of representing negative integers. More on that in 
 * http://en.wikipedia.org/wiki/Two's_complement
 */

#include <stdio.h>
#include <string.h>


int reverse(char* s) {
	int len;
	int i;
	char c;
	len = strlen(s);

	for (i = 0; i < len/2; i++) {
		c = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = c;
	}
}



/* itoa:  convert n to characters in s */
void my_itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {      /* generate digits in reverse order */
		s[i++]=((n%10 < 0)?(-1*(n%10)):(n%10)) + '0'; /*getnextdigit*/
	} while ((n /= 10) != 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main() {
	int x = 0x80000000;
	char s[100];
	my_itoa(x,s);

	printf ("s = %s\n", s);

	return 0;
}
