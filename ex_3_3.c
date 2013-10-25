/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int expand(char* s1, char* s2) {

	char beg,end,c;
	int dash,direction;
	int i,j;
	i = j = 0;

	beg = end = '\0';
	dash = 0;
	
	while(s1[i] != '\0') {
		if( isalpha(s1[i]) || isdigit(s1[i])  ) {
			if (dash) { /* we have a complete experssion */
				end = s1[i];
				/* do we need to expand the expression */
				if ( (isupper(beg) && isupper(end)) ||
				    (islower(beg) && islower(end)) ||
				    (isdigit(beg) && isdigit(end))) {

					direction = (beg < end)?1:-1;
					c = beg;
					do {
						s2[j++] = c;
						c+=direction;
					} while(c != end+direction);
				} else {
					/* invalid expression, just dump it as it is */
					s2[j++] = beg; s2[j++] = '-'; s2[j++] = end;
				}

				/* in both cases, clear all */
				beg = end = '\0'; dash = 0;

			} else {
				/* we have a new begining */
				if(beg) {
					s2[j++] = beg;
				}

				beg = s1[i];
			}

		} else if (s1[i] == '-') {
			if (beg) {
				dash = 1;
			} else {
				s2[j++] = '-';
			}
		} else {
			/* flush all */
			if (beg) {
				s2[j++] = beg;
				beg = '\0';
			}
			if (dash) {
				s2[j++] = '-';
				dash = 0;
			}
			s2[j++] = s1[i];
		}

		i++;
	}


	if(beg) {
		s2[j++] = beg;
	}

	if(dash) {
		s2[j++] = '-';
	}

	s2[j] = '\0';

	return 0;
}


int main(int argc, char** argv) {
	int len;
	char* s;
	
	if (argc > 1 ) {
		len = strlen(argv[1]);
		s = malloc(26*len);
		expand(argv[1],s);

		printf ("%s\n",s);

	}


	return 0;
}
