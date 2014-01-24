#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct tnode;
struct lnode;


/* this is the core data structure that stores the words */
struct wnode {
	char *word;		/* a pointer to the word */
	int count;		/* frequency of the word */
	struct tnode *tn;	/* which tree node this wnode is connected to */
	struct lnode *ln;	/* pointer to lnode */
};

/* tree node */
struct tnode {
	struct wnode *wn;	/* each tnode is connected to a wnode */
	struct tnode *left;	/* left child */
	struct tnode *right;	/* right child */
	struct tnode *parent;	/* parent node */
};

/* linked list node */
struct lnode {
	struct wnode *wn;	/* pointer to wnode */
	struct lnode *next;	/* next element in the list */
	struct lnode *prev;	/* prev element in the list */
};

/* a container that contain both the tree and the linked list */
struct words {
	struct tnode *troot;	/* alphabeticaly ordered tree */
	struct lnode *lroot;	/* word list ordered by count */
};


/* allocate a new tree node and initialize it */
struct tnode *tnodealloc() {
	struct tnode *t;
	t = (struct tnode *) malloc(sizeof (struct tnode));
	t->left = t->right = t->parent = NULL;
	t->wn = NULL;
	return (t);
};

/* allocate a new linked list node and initialize it */
struct lnode *lnodealloc() {
	struct lnode *ln;
	ln = (struct lnode *) malloc(sizeof (struct lnode));
	ln->prev = ln->next = NULL;
	ln->wn = NULL;
	return (ln);
};

/* allocate a new word node and intialize it */
struct wnode *wnodealloc() {
	struct wnode *wn;
	wn = (struct wnode *) malloc(sizeof (struct wnode));
	wn->word = NULL;
	wn->count = 0;
	wn->ln = NULL;
	wn->tn = NULL;
	return (wn);
};


/*
 * check two liked list nodes, usually they are adjacent such as y = x->next
 */

int lnodes_inorder(struct lnode *x, struct lnode *y) {
	if (x == NULL || y == NULL)
		return (1);
	if (x->wn->count < y->wn->count)
		return (1);
	if (x->wn->count == y->wn->count &&
		strcmp(x->wn->word, y->wn->word) <= 0)
		return (1);

	return (0);
}

/*
 * If two nodes in the list are not in order, then we need to swap them
 * this is used to maintain the linked list ordered by frequency (count)
 * We don't swap the nodes themselves, just the wnode pointers (wn), we also
 * need to update the wnode structure to tell them about their new lnodes
 */
void swap_lnodes(struct lnode *x, struct lnode *y) {
	struct wnode *wn;
	struct lnode *ln;
	if (x == NULL || y == NULL)
		return;

	/* swap the wnode pointers */
	wn = x->wn;
	x->wn = y->wn;
	y->wn = wn;

	/* update the wnodes with their new lnodes */
	ln = x->wn->ln;
	x->wn->ln = y->wn->ln;
	y->wn->ln = ln;
}

/*
 * This function is called each time a new word is found already in the tree
 * As the linked list may no longer be in order,
 * we need to fix this to maintain the order
 */
void balance_word_list(struct lnode *ln) {
	/* make sure that we maintain the list ordered */
	struct lnode *cn;

	if (ln == NULL)
		return;

	cn = ln;
	/* compare the node with its next, and walk forward */
	while (cn != NULL && !lnodes_inorder(cn, cn->next)) {
		/* the nodes are not in order, then swap them */
		swap_lnodes(cn, cn->next);
		/* progress forward in the linked list */
		cn = cn->next;
	}
}

/*
 * every time we add a new word to the tree, we need to add it
 * also to the liked list.  add_to_word_list() will do this.
 * It will add the node is the first position in the list
 */

void add_to_word_list(struct wnode *wn, struct lnode *lroot) {

	struct lnode *ln;

	if (lroot == NULL) {
		printf("error, lroot can't be NULL\n");
		exit(1);
	}


	ln = lnodealloc();	/* allocate a new linked list element */
	ln->wn = wn;		/* attach the wnode to this new element */
	wn->ln = ln;		/* tell the wnode which lnode points to it */
	ln->prev = lroot;	/* add the node as the second element */
	ln->next = lroot->next;

	/*
	 * swap the root of the liked list with the second element
	 * this has the effect of adding the new element as the
	 * first element in the list. We take all this overhead as
	 * we can't change the pointer to the first element in the
	 * liked list
	 */
	swap_lnodes(lroot, ln);

	/*
	 * if there were more that one element in the list,
	 * then update the second element to point to this newly added lnode
	 */
	if (lroot->next) {
		lroot->next->prev = ln;
	}

	/* finally, set the new element as the second element in the list */
	lroot->next = ln;
}


/*
 * This function is called each time we want to add a new word
 */
void insert(struct words *w, char *word) {


	struct wnode *wn;
	struct tnode *tn, *cn;
	int cond;
	if (!w || (!w->troot && w->lroot) || (!w->lroot && w->troot))
		return;

	/* is this the first word to be added */
	if (!w->troot && !w->lroot) {
		wn = wnodealloc();
		w->troot = tnodealloc();
		w->lroot = lnodealloc();

		w->troot->wn = wn;
		w->lroot->wn = wn;

		wn->tn = w->troot;
		wn->ln = w->lroot;
		wn->word  = strdup(word);
		wn->count = 1;

		return;
	}


	tn = w->troot;	/* tn points to the root of the tree */

	/*
	 * this is an infinite loop as we will break the loop
	 * once we add the new word
	 */
	while (1) {

		wn = tn->wn;	/* get the wnode associated with this tnode */

		if ((cond = strcmp(wn->word, word)) == 0) {
			/* well we have found the wnode */
			/* increment the wnode counter */
			wn->count++;
			/* make sure that the linked list is balanced */
			balance_word_list(wn->ln);
			break;

		} else if (cond < 0) {
			/* insert in the left subtree */
			if (tn->left) {
				tn = tn->left;
				continue;
			}

			wn = wnodealloc();	 /* allocate a new wnode */
			wn->word = strdup(word); /* copy the word */
			wn->count = 1;		 /* initialize the count to 1 */

			cn = tnodealloc();	/* allocate a new tnode */
			cn->wn = wn;		/* point to the wnode */
			cn->parent = tn;	/* set the parent */
			tn->left = cn;		/* link the parent to the cn */
			wn->tn = cn;		/* link the wnode to the tree */

			/* add this wnode to the liked list */
			add_to_word_list(wn, w->lroot);
			break;

		} else {
			/* add to the right subtree */
			if (tn->right) {
				tn = tn->right;
				continue;
			}

			wn = wnodealloc();
			wn->word = strdup(word);
			wn->count = 1;


			cn = tnodealloc();
			cn->wn = wn;
			cn->parent = tn;
			tn->right = cn;
			wn->tn = cn;
			add_to_word_list(wn, w->lroot);
			break;
		}

	}

}


void printtree(struct tnode *troot) {
	if (!troot)
		return;

	printtree(troot->left);
	printf("word = %s, count = %d\n", troot->wn->word, troot->wn->count);
	printtree(troot->right);
}


void printlist(struct lnode *lroot) {
	while (lroot) {
		printf("word = %s count = %d\n",
			lroot->wn->word, lroot->wn->count);
		lroot = lroot->next;
	}
}


int main() {
	struct words w;
	w.troot = NULL;
	w.lroot = NULL;
	insert(&w, "me");
	insert(&w, "me");
	insert(&w, "you");
	insert(&w, "you");
	insert(&w, "you");
	insert(&w, "your");
	insert(&w, "me");
	insert(&w, "me");
	insert(&w, "he");


	/*
	 * printf ("print the tree\n");
	 * printtree(w.troot);
	 */
	printf("print the list\n");
	printlist(w.lroot);


	return (0);
}
