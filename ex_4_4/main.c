/*
 * Exercise 4-4. Add the commands to print the top elements
 * of the stack without popping, to duplicate it, and to swap
 * the top two elements. Add a command to clear the stack.
 */

/*
 * @ to print the top element of the stack
 * # to duplicate the top element on the stack
 * $ to swap the top two elements, if we have more than two
 * ^ to clear the stack
 */


#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include "include/input.h"
#include "include/stack.h"

/* reverse Polish calculator */
main()
{
	int type;
	double op1,op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
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
	}

	return 0;
}
