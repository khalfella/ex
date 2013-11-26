/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	int c;
	int tst = 8;

	int tab;
	int off = 0;
	int col = 0;


	while (*++argv) {
		if ( strcmp(*argv, "-m") == 0 && *++argv) {
			tst = atoi(*argv);
		} else  if ( strcmp(*argv, "-n") == 0 && *++argv) {
			col = atoi(*argv);
		}
	}


	tab = tst;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {

			if (off < col) {
				putchar(c);
				off += tst - (off%tst);
				tab = tst;
				continue;
			}
			

			while (tab--) {
				putchar(' ');
				off++;
			}
			tab = tst;

		} else if (c == '\n') {
			putchar(c);
			tab = tst;
			off = 0;
		} else {
			tab = (--tab)?tab:tst;
			putchar (c);
			off++;
		}
	}

	return 0;
}
