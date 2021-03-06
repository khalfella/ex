/*
 * Exercise 6-1. Our version of getword does not properly
 * handle underscores, string constants, comments, or
 * preprocessor control lines. Write a better version.
 */

/*
 * I have only implemented support for underscores and string constants
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	MAXWORD 200

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	/* ... */
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

#define	NKEYS (sizeof keytab / sizeof (keytab[0]))

#define	BUFSIZE	100
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int
getch(void)  /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void
ungetch(int c)   /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}


int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
main()
{
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
				keytab[n].count, keytab[n].word);
	return (0);
}

int
binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return (mid);
	}

	return (-1);
}

/* getword:  get next word or character from input */
int
getword(char *word, int lim)
{
	int c;
	char *w = word;
	while (isspace(c = getch()))
		;

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '_' && c != '"' && c != '/') {
		*w = '\0';
		return (c);
	}
	for (; --lim > 0; w++) {
		*w = getch();


		if (word[0] == '/') {
			if (word[1] != '*') { /* it looks like a comment but it is not */
				ungetch(word[1]);
				word[1] = '\0';
				return (word[0]);
			}

			/* we in a comment, are we exiting */
			if (w[-1] == '*' && *w == '/') {
				w++;
				break;
			}
			/* anything else is allowed inside a comment */
			continue;
		}

		if (word[0] == '"') { /* are we in quotes */
			/* are we exiting */
			if ( *w == '"' && w[-1] != '\\') {
				w++;
				break;
			}

			/* everyting else is permitted in quotes */
			continue;
		}

		if (isalnum(*w) ||  *w == '_')
			continue;

		/* we are not in quotes and this is not alphanum */
		ungetch(*w);
		break;
	}

	*w = '\0';
	return (word[0]);
}
