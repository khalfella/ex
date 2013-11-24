/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

char* strcat(char *s1, char *s2) {
	char* ret = s1;
	if (*s1) {		/* seek to the end of s1 */
		while(*++s1)
			;
	}

	while(*s2) {
		*s1++ = *s2++;
	}

	*s1 = '\0';

	return ret;
}

int main() {
	char a[50] = "khalfella";
	char b[]   = "@gmail.com";

	strcat(a,b);
	printf ("a = %s\n", a);
}


