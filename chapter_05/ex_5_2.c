/*
 * Exercise 5-2. Write getfloat, the floating-point
 * analog of getint.
 * What type does getfloat return as its function value?
 */

#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>

#define	BUFSIZE	1024

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */




int getch(void)  /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)   /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getfloat(float *pn)
{
	int c, sign;
	float fr;

	while (isspace(c = getch()))	/* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-')? -1 : 1;
	if (c == '-' || c == '+') {
		c = getch();
		if (!isdigit(c) && c != '.') {
			ungetch(c);
			return 0;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.') {
		c = getch();
		for (fr = 10; isdigit(c); c = getch(), fr *= 10) {
			*pn += (c - '0')/fr;
		}
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);

	return c;

}

int main() {
	float a;
	if(getfloat(&a)) {
		printf ("got a = %f\n", a);
	}

	return 0;
}
