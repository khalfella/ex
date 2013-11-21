/*
 * Exercise 4-6. Add commands for handling variables.
 * (It's easy to provide twenty-six variables with single-letter names.)
 * Add a variable for the most recently printed value.
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
					}
				break;
		}
	}

	return 0;
}
