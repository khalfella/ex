/*
 * Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters.
 */


#include <stdio.h>

int escape(char* s, char* t) {
	int i,j;
	i = j = 0;
	while (t[i] != '\0') {
		switch (t[i]) {
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			default:
				s[j++] = t[i];
				break;
		}

		i++;
	}

	s[j] = '\0';
	return 0;
}

/* 
 * converts escape sequences to real characters
 * right now, only supports \t and \n
 */

int descape(char* s, char* t) {
	int i,j,escaping;
	i = j = 0;
	escaping = 0;

	while (t[i] != '\0') {
		switch (t[i]) {
			case '\\':
				if (escaping) {
					s[j++] = '\\';
					escaping = 0;
				} else {
					escaping = 1;
				}
				break;
			case 'n':
				if (escaping) {
					s[j++] = '\n';
					escaping = 0;
				} else {
					s[j++] = 'n';
				}
				break;
			case 't':
				if (escaping) {
					s[j++] = '\t';
					escaping = 0;
				} else {
					s[j++] = 't';
				}
				break;
			default:
				if (escaping) {
					/*escaping a not supported character*/
					s[j++] = '\\';
					s[j++] = t[i];
					escaping = 0;
				} else {
					s[j++] = t[i];
				}
				break;
		}
		i++;
	}

	if (escaping) {
		s[j++] = '\\';
	}

	s[j] = '\0';
	return 0;
}

int main() {
	char t[] = "tab\t new line\n";
	char s[100];

	escape (s,t);
	printf ("t = %s s = %s\n", t,s);

	descape (t,s);
	printf ("t = %s s = %s\n", t,s);
	return 0;
	
}
