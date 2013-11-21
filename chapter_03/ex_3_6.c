/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead
 * of two. The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough.
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
void my_itoa(int n, char s[], int mw)
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

	while( i < mw) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}

int main() {
	int x = 0x80000000;
	char s[100];
	my_itoa(x,s,22);

	printf ("s = %s\n", s);

	return 0;
}
