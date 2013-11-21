#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>

#ifndef _INPUT_H_
#define _INPUT_H_

#define MAXOP   100  /* max size of operand or operator */
#define BUFSIZE 100


#define	NONE		0	/* none was found just EOF */
#define NUMBER		1	/* a number was found */
#define	OPERATOR	2	/* an operator was found */
#define IDENTIFIER	3	/* an identifier was found */




int getch(void);  /* get a (possibly pushed-back) character */
void ungetch(int c);   /* push character back on input */
void ungets(char s[]); /* push a string of characters to input */
int getop(char s[]);


#endif	/* _INPUT_H_ */
