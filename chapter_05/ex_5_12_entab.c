/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {

	int c;
	int tst = 8;
	int col = 0;
	int spaces = 0;
	int offset = 0;

	while (*++argv) {
		if ( strcmp(*argv, "-m") == 0 && *++argv) {
			tst = atoi(*argv);
		} else  if ( strcmp(*argv, "-n") == 0 && *++argv) {
			col = atoi(*argv);
		}
	}


	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			spaces++;
			offset++;
			if(offset%tst == 0 && offset > col) {
				putchar ('\t');
				spaces = 0;
			}
		} else {
			while(spaces) {
				putchar (' ');
				spaces--;
			}

			putchar(c);
			offset++;
			if (c == '\n') {
				offset = 0;
			}

			if (c == '\t' && offset%tst != 0) {
				offset += tst - (offset%tst);
			}
			
		}
		
	}

	while(spaces) {
		putchar(' ');
		spaces--;
	}

	return 0;
}
