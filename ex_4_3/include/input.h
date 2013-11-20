#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>

#ifndef _INPUT_H_
#define _INPUT_H_

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */
#define BUFSIZE 100




int getch(void);  /* get a (possibly pushed-back) character */
void ungetch(int c);   /* push character back on input */
int getop(char s[]);


#endif	/* _INPUT_H_ */
