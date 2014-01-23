#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAXWORD 100
#define MAXVAR 100



struct lnode {
	int line;
	struct lnode *next;
};

struct tnode {
	char *word;
	struct lnode *lines;
	struct tnode *left;
	struct tnode *right;
};

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct lnode *lnodealloc(void) {
	return (struct lnode *) malloc(sizeof(struct lnode));
}

char *str_dup(char *s)   /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}


struct tnode *addword(struct tnode *p, char *word, int line)
{
	int cond;
	struct lnode *l;

	if (p == NULL) {	
		p = talloc();
		p->left = p->right = NULL;
		p->word = str_dup(word);
		l = p->lines = lnodealloc();
		l->line = line;
		l->next = NULL;
	} else if ((cond = strcmp(word, p->word)) == 0) {
		l = p->lines;
		while (l->next) {
			l = l->next;
		}
		l->next = lnodealloc();
		l = l->next;
		l->line = line;
		l->next = NULL;
	}
	else if (cond < 0)		/* less than into left subtree */
		p->left = addword(p->left, word, line);
	else				/* greater than into right subtree */
		p->right = addword(p->right, word, line);
	return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
	struct lnode *l;

	if (p != NULL) {
		treeprint(p->left);
		puts(p->word);

		putchar('{');
		l = p->lines;
		while (l) {
			printf("%d, ", l->line);
			l = l->next;
		}
		puts("}\n");

		treeprint(p->right);
	}
}

#define BUFSIZE 100
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;	   /* next free position in buf */

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

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	while (isspace(c = getch()) && c != '\n')
		;

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return (c);
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}

	*w = '\0';
	return (word[0]);
}


int main(int argc, char **argv)
{
	int n = 0;
	char word[MAXWORD+1];
	int line = 1;

	struct tnode *root = NULL;

	while (getword(word, MAXWORD) != EOF) {
		if (strcmp(word, "\n") == 0) {
			line++;
			continue;
		}

		root = addword(root, word, line);
	}

	treeprint(root);

	return 0;
}
