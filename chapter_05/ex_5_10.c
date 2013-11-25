/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse
 * Polish expression from the command line, where each operator
 * or operand is a separate argument. For example,
 */



#include <stdio.h>

#define	STACK_SIZE 100	

int stack[STACK_SIZE];
int sp = 0;

int push(int x) {
	if (sp < STACK_SIZE - 1) {
		stack[sp++] = x;
		return 1;
	}
	return 0;
}


int pop(void) {
	if (sp) {
		return stack[--sp];
	}

	return 0;
}



int main(int argc, char** argv) {

	int a,x;
	int op2;

	if (argc < 2 ) {
		printf ("Usage : %s num1 num2 op ..\n", argv[0] );
		return 1;
	}

	while (*++argv) {
		if (isdigit(a = **argv)) {
			x = a - '0';
			while (isdigit(a = *++argv[0])) 
				x = x * 10 + (a - '0');

			push (x);
			continue;
		}

		/* here we assume that we are having an operator */
		switch (**argv) {
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				push(pop() / op2);
				break;
		}
		
	}

	printf ("%d\n", pop());

	
}
