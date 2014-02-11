/*
 * Exercise 6-5. Write a function undef that will remove a name
 * and definition from the table maintained by lookup and install.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


struct nlist {		/* table entry: */
	struct nlist *next;
	char *name;
	char *defn;
};


#define	HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */


/* hash:  form hash value for string s */
unsigned
hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return (hashval % HASHSIZE);
}


/* lookup:  look for s in hashtab */
struct nlist *
lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)];  np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return (np);		/* found */

	return (NULL);				/* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *
install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc(sizeof (*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return (NULL);
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else					/* already there */
		free((void *) np->defn);	/* free previous defn */

	if ((np->defn = strdup(defn)) == NULL)
		return (NULL);

	return (np);
}

int
undef(char *name)
{
	unsigned hashval;
	struct nlist *np, *nnp;

	hashval = hash(name);
	np = hashtab[hashval];

	if (np == NULL)			/* the string is not there */
		return (0);

	np = hashtab[hashval];
	if (strcmp(np->name, name) == 0) {
		hashtab[hashval] = hashtab[hashval]->next;
		free(np->name);
		free(np->defn);
		free(np);
		return (1);
	}

	nnp = np->next;
	while (nnp) {
		if (strcmp(nnp->name, name) == 0) {
			np->next = nnp->next;
			free(nnp->name);
			free(nnp->defn);
			free(nnp);
			return (1);
		}

		np = nnp;
		nnp = np->next;
	}

	return (0);
}

int main() {
	int i;
	char name[] = "AAA";
	struct nlist *np;


	/* initilize the hash table */
	for (i = 0; i < HASHSIZE; i++) {
		hashtab[i] = NULL;
	}

	while (1) {
		install(name, name);
		name[2]++;

		if (name[2] == 'Z'+1) {
			if (name[1] == 'Z') {
				if (name[0] == 'Z') {
					break;
				}
				name[0]++;
				name[1] = 'A';
				name[2] = 'A';
			} else {
				name[1]++;
				name[2] = 'A';
			}
		}
	}




	strcpy(name, "AAA");
	while (1) {
		if (lookup(name) == NULL) {
			printf("%s was NOT found\n", name);
		} else {
			printf("%s was found\n", name);
		}
		name[2]++;

		if (name[2] == 'Z'+1) {
			if (name[1] == 'Z') {
				if (name[0] == 'Z') {
					break;
				}
				name[0]++;
				name[1] = 'A';
				name[2] = 'A';
			} else {
				name[1]++;
				name[2] = 'A';
			}
		}
	}

	undef("CCC");	/* remove a random name */
	undef("---");	/* remove a name that does not exist */
	undef("AAA");	/* remove a node in hashtab */
	strcpy(name, "AAA");
	while (1) {
		if (lookup(name) == NULL) {
			printf("%s was NOT found\n", name);
		} else {
			printf("%s was found\n", name);
		}
		name[2]++;

		if (name[2] == 'Z'+1) {
			if (name[1] == 'Z') {
				if (name[0] == 'Z') {
					break;
				}
				name[0]++;
				name[1] = 'A';
				name[2] = 'A';
			} else {
				name[1]++;
				name[2] = 'A';
			}
		}
	}
	return (0);
}
