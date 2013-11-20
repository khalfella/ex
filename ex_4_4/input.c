#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>
#include "include/input.h"

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

/* getop:  get next character or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c !='-')
		return c;      /* not a number */

	i = 0;
	if (isdigit(c) || c == '-')    /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')      /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);

	if (s[0] == '-' && !isdigit(s[1]) && s[1] !='.' ){	/* we have only get '-' */
		return '-';
	}
	return NUMBER;
}
