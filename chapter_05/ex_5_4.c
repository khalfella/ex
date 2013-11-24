/*
 * Exercise 5-4. Write the function strend(s,t),
 * which returns 1 if the string t occurs at the
 * end of the string s, and zero otherwise.
 */


#include <stdio.h>

int strend(char *s, char *t) {
	char* s0 = s;
	char* t0 = t; /* save the orginal values of s and t */


	if (*t == '\0') /* empty string is always at the end of any string */
		return 1;

	if (*s == '\0') /* empty string can't contain a non-empty string */
		return 0;


	/* move s and t to the end of the string */
	while (*s) {
		s++;
	}

	while (*t) {
		t++;
	}

	while (s >= s0 && t >= t0 && *s == *t) {
		s--; t--;
	}

	if (t < t0) {
		return 1;
	}


	return 0;
}


int main() {

	char a[] = "mohamed.khalfella";
	char b[] = "khalfella";

	if(strend(a,b)) {
		printf ("OK\n");
	}
}
