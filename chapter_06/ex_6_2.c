#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAXWORD 100
#define MAXVAR 100



struct varnode {
	char *vname;
	struct varnode *next;
};

struct tnode {
	struct varnode *var;
	struct tnode *left;
	struct tnode *right;
};

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct varnode *varalloc(void) {
	return (struct varnode *) malloc(sizeof(struct varnode));
}

char *str_dup(char *s)   /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}


/* add the variable vname to the tree */
struct tnode *addvar(struct tnode *p, char *vname, int n)
{
	int cond;
	struct varnode *v;

	if (p == NULL) {	
		p = talloc();
		p->left = p->right = NULL;
		v = p->var = varalloc();
		v->vname = str_dup(vname);
		v->next = NULL;
	} else if ((cond = strncmp(vname, p->var->vname, n)) == 0) {
		/* add the variable to this node */
		v = p->var;
		while (v->next) {
			v = v->next;
		}
		v->next = varalloc();
		v = v->next;
		v->vname = str_dup(vname);
		v->next = NULL;
	}
	else if (cond < 0)		/* less than into left subtree */
		p->left = addvar(p->left, vname, n);
	else				/* greater than into right subtree */
		p->right = addvar(p->right, vname, n);
	return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
	struct varnode *v;
	if (p != NULL) {
		treeprint(p->left);
		v = p->var;

		putchar('{');
		while (v) {
			printf("%s, ", v->vname);
			v = v->next;
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
	while (isspace(c = getch()))
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

int getvariable(char* vname) {
	int decl =  0;
	char w[MAXVAR];

	while (getword(w,MAXWORD) != EOF) {
		if (decl) {
			strcpy(vname,w);
			return strlen(vname);
		}
		if (strcmp(w,"int") == 0 || strcmp(w,"char") == 0)
			decl = 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	int n = 0;
	if (*++argv) {
		n = atoi(*argv);
	}
	n = (n)?n:6;

	struct tnode *root;
	char vname[MAXVAR];
	root = NULL;

	while (getvariable(vname)) {
			root = addvar(root, vname, n);
	}

	treeprint(root);

	return 0;
}
