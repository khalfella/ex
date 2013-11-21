#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>
#include "include/input.h"

int buf[BUFSIZE];    /* buffer for ungetch */
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

void ungets(char s[]) {
	int i = 0;
	while (s[i] != '\0' && bufp < BUFSIZE) {
		buf[bufp++] = s[i];
	}
}

/* getop:  get next character or numeric operand */
int getop(char s[]) {
	int i,len, c;
	i = 0;
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == EOF)
		return NONE;

	s[i++] = c;

	if (c == '\n') {
		s[i] = '\0';
		return OPERATOR;
	}

	while ((c = getch()) != ' ' && c != '\t' && c != '\n' && c != EOF) {
		s[i++] = c;
	}

	ungetch(c);		/* ungetch the last character even if it is EOF */

	s[i] = '\0';
	len = i;

	if(len == 1 && !isalpha(s[0]) && !isdigit(s[0]) && s[0] != '.') {
		return OPERATOR;
	} else if (isdigit(s[0]) || s[0] == '-' || s[0] == '.') {
		return NUMBER;
	} 

	return IDENTIFIER;

}
