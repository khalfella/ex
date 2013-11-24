/*
 * Exercise 5-5. Write versions of the library functions
 * strncpy, strncat, and strncmp, which operate on at most the first
 * n characters of their argument strings.
 * For example, strncpy(s,t,n) copies at most n characters
 * of t to s. Full descriptions are in Appendix B.
 */

#include <stdio.h>

char* strn_cpy(char *s, char *t, int n) {
	char* ret = s;

	while ( n-- && (*s++ = *t++) ) { }

	if(n < 0) {
		*s = '\0';
	}
	return ret;
}

char* strn_cat(char *s, char *t, int n) {
	char* ret = s;

	while(*s) {
		s++;
	}

	while ( n-- && (*s++ = *t++) ) { }

	if(n < 0) {
		*s = '\0';
	}

	return ret;
	
}

int strn_cmp(char *s, char *t, int n) {
	while (n-- && (*s++ == *t++) ) {
		if (s[-1] == '\0') {
			return 0;
		}
	}
	if (n < 0) {
		return 0;
	}

	return s[-1] - t[-1];
}

int main() {
	char s[50] = "";
	char s1[]  = "mohamed";
	char s2[] = "@gmail.com";

	int comp;

	strn_cpy(s,s1,100);
	strn_cat(s,s2,100);

	comp = strn_cmp("sami","mohamed",200);

	printf ("s = %s comp = %d\n", s, comp);

	return 0;
}
