/*
 * Exercise 4-7. Write a routine ungets(s) that will push back
 * an entire string onto the input. Should ungets know about
 * buf and bufp, or should it just use ungetch?
 */

/*
 * @ to print the top element of the stack
 * # to duplicate the top element on the stack
 * $ to swap the top two elements, if we have more than two
 * ^ to clear the stack
 */

/*
 * variables in the format <a is the value of a
 * variables in the format >a store to a
 */


#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <math.h>
#include <string.h>
#include "include/input.h"
#include "include/stack.h"

/* reverse Polish calculator */
main()
{
	int type;
	double op1,op2;
	char s[MAXOP];
	double var[26];
	int i;

	for (i = 0; i < 26; i++) {
		var[i] = 0;
	}

	
	while ((type = getop(s)) != NONE) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case OPERATOR:
				switch (s[0]) {
					case '+':
						push(pop() + pop());
						break;
					case '*':
						push(pop() * pop());
						break;
					case '-':
						op2 = pop();
						push(pop() - op2);
						break;
					case '/':
						op2 = pop();
						if (op2 != 0.0)
							push(pop() / op2);
						else
							printf("error: zero divisor\n");
						break;
					case '%':
						op2 = pop();
						push((long)pop() % (long)op2);
						break;
					case '@':
						op1 = pop();
						printf("\t top element = %.8g\n", op1);
						push(op1);
						break;
					case '#':
						op1 = pop();
						push(op1); push(op1);
						break;
					case '$':
						op1 = pop(); op2 = pop();
						push(op1);   push(op2);
						break;
					case '^':
						clear();
						break;
					case '\n':
						printf("\t%.8g\n", pop());
						break;
					default:
						printf("error: unknown command %s\n", s);
					break;
				}
				break;
			case IDENTIFIER:
					if (strcmp(s,"sin") == 0) {
						push(sin(pop()));
					} else if (strcmp(s,"exp") == 0) {
						push(exp(pop()));
					} else if (strcmp(s,"pow") == 0) {
						op1 = pop(); op2 = pop();
						push(pow(op2,op1));
					} else if (strlen(s) > 1 && s[0] == '>') {
						var[tolower(s[1]) - 'a'] = pop();
					} else if (strlen(s) > 1 && s[0] == '<') {
						push (var[tolower(s[1]) - 'a']);
					}
				break;
		}
	}

	return 0;
}
