/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s.
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
void my_itob(int n, char s[],int base)
{
	int i, sign;
	int digit;
	char start;
	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {
		digit = n%base;
		digit = (digit < 0)? -digit:digit;
		start = (digit > 9)?'a':'0';

		s[i++]= digit + start; /*getnextdigit*/

	} while ((n /= base) != 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main() {
	int x = 0x80000000;
	char s[100];
	my_itob(x,s,2);

	printf ("s = %s\n", s);

	return 0;
}
