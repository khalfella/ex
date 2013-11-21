#include <stdio.h>
#include <string.h>


void reverse(char s [])
{
	int len = strlen(s);
	char first, last;
	int i;
	if (len < 2 ) {
		return;
	}
	first = s[0];
	last = s[len - 1];

	if (len == 2) {
		s[0] = last;
		s[1] = first;
		return;
	}

	/*
	 * if the string is longer than 2 character
	 * then shift it left one step and terminate the first len - 2
	 * then reverse it
	 */
	for (i = 0 ; i < len - 2; i++) {
		s[i] = s[i + 1];
	}
	s[len - 2] = '\0';
	reverse(s);

	/* shift it back */
	for (i = len - 2 ; i > 0 ; i--) {
		s[i] = s[i - 1];
	}

	/* restore the first the last charachter*/
	s[0] = last;
	s[len - 1] = first;
		
}
int  main()
{
        char s[] = "abcdefghijklmnopqrstuvwxyz";
        reverse(s); printf("%s\n", s);
        reverse(s); printf("%s\n", s);
        reverse(s); printf("%s\n", s);
        reverse(s); printf("%s\n", s);

	return 0;
}
