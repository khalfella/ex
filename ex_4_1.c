/*
 * Exercise 4-1. Write the function strindex(s,t) which returns the
 * position of the rightmost occurrence of t in s, or -1 if there is none.
 */


#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

int get_line(char s[], int lim);
int strindex(char source[], char searchfor[]);
char pattern[] = "ould";   /* pattern to search for */



/* find all lines matching pattern */
main()
{
	char line[MAXLINE];
	int found = 0;
	while (get_line(line, MAXLINE) > 0) {

		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}

/* getline:  get line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';
	return i;
}


/* strindex:  return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
	int i, j, k;
	int slen = strlen(s);
	int tlen = strlen(t);

	for (i = slen - tlen - 1; i >= 0 ; i--) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;

	if (k > 0 && t[k] == '\0')
		return i;
	}

	return -1;
}
