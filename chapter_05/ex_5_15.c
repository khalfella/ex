


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	MAXLINES 5000	  /* max #lines	to be sorted */
#define MAXLEN	 1000	  /* max line length */


char *lineptr[MAXLINES];  /* pointers to text lines */
int readlines(char *lineptr[], int nlines);

void writelines(char *lineptr[], int nlines);
void q_sort(void	*v[], int	left, int right,
	int (*comp)(void *, void *));

void q_sort_r(void	*v[], int	left, int right,
	int (*comp)(void *, void *));
int numcmp(char	*, char	*);


/* sort	input lines */
int main(int argc, char *argv[])
{
	int nlines;	   /* number of	input lines read */
	int numeric = 0;   /* 1	if numeric sort	*/
	int reverse = 0;   /* 1 if sort in reverse order */
	int fold = 0;	   /* 1 if case insensitive order */
	int (*cmp)(void*, void*);
	void (*sort)(void*, int, int, int (*)(void*,void*));


	while (*++argv) {
		if (strcmp(*argv, "-n") == 0)
			numeric = 1;
		if (strcmp(*argv, "-r") == 0)
			reverse = 1;
		if (strcmp(*argv, "-f") == 0)
			fold = 1;
	}

	
	sort = (reverse)?q_sort_r:q_sort;
	cmp = (int (*)(void*,void*))strcmp;
	
	if (numeric) {
		cmp = (int (*)(void*,void*))numcmp;
	} else if (fold) {
		cmp = (int (*)(void*,void*))strcasecmp;
	}
	

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		(*sort)((void**) lineptr, 0, nlines-1,cmp);

		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}


int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[],  int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* q_sort:  sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right,
              int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right)    /* do  nothing if array contains */
		return;           /* fewer than two elements */

	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right;  i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	q_sort(v, left, last-1, comp);
	q_sort(v, last+1, right, comp);
}


/* q_sort_r:  sort v[left]...v[right] into decreasing order */
void q_sort_r(void *v[], int left, int right,
              int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right)    /* do  nothing if array contains */
		return;           /* fewer than two elements */

	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right;  i++)
		if ((*comp)(v[i], v[left]) >= 0)
			swap(v, ++last, i);

	swap(v, left, last);
	q_sort_r(v, left, last-1, comp);
	q_sort_r(v, last+1, right, comp);
}

int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr [],	int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0) {

		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] =	'\0'; /* delete	newline	*/
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

int get_line(char s [], int lim)
{
	int c, i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c	!= '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void writelines(char *lineptr [], int nlines)
{
	int i;
        for (i = 0; i < nlines; i++)
                printf("%s\n", lineptr[i]);
}
