/*
 * Exercise 5-13. Write the program tail, 
 * which prints the last n lines of its input. 
 * By default, n is set to 10, let us say, 
 * but it can be changed by an optional argument so that
 *            tail -n
 * prints the last n lines. 
 * The program should behave rationally no matter how unreasonable 
 * the input or the value of n. 
 * Write the program so it makes the best use of available storage; 
 * lines should be stored as in the sorting program of Section 5.6, 
 * not in a two-dimensional array of fixed size.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAIL 10
#define MAX_LINE 1000



int main(int argc, char **argv) {
	int c;
	int m,n = TAIL;
	char **lines;
	int cur = 0,idx = 0;

	while (*++argv) {
		if (**argv == '-') {
			n = atoi(++argv[0]);
			n = (n <= 0)? TAIL: n;
		}
	}

	/* allocate the pointers of pointers array */
	if ((lines = malloc(sizeof(char*) * n)) == NULL)
		return 1;

	/* initialize the array pointer */
	for (cur = 0; cur < n ; cur++)
		lines[cur] = 0;


	/* now receive the input and store the last n lines in the array */
	cur = 0;
	while ((c = getchar()) != EOF) {

		/* allocate the next line if not allocated yet */
		if (!lines[cur] && (lines[cur] = malloc(MAX_LINE)) == NULL)
			return 1;

		/* store the character in the line */
		lines[cur][idx++] = c;

		if (c == '\n') {
			/* terminate the line */
			lines[cur][idx] = '\0';

			/* prepare to move to a new line */
			cur = (cur+1)%n;
			idx = 0;

		}
	
	}

	/*
	 * terminate the curent line in case it contains data
	 * and move to the next line
	 */
	if (idx && lines[cur]) {
		lines[cur][idx] = '\0';
		cur = (cur+1)%n;
	}


	m = n ;

	while(m--) {
		if (lines[cur]) {
			printf ("%s", lines[cur]);
		}
		cur = (cur+1)%n;	
	}
	


	return 0;
}
