#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct tnode;
struct lnode;

struct wnode {
	char *word;
	int count;
	struct tnode *tn;
	struct lnode *ln;
};

struct tnode {
	struct wnode *wn;
	struct tnode *left;
	struct tnode *right;
	struct tnode *parent;
};

struct lnode {
	struct wnode *wn;
	struct lnode *next;
	struct lnode *prev;
};

struct words {
	struct tnode *troot;
	struct lnode *lroot;
};


struct tnode *tnodealloc() {
	struct tnode *t;
	t = (struct tnode*) malloc(sizeof(struct tnode));
	t->left = t->right = t->parent = NULL;
	t->wn = NULL;
	return t;
};

struct lnode* lnodealloc() {
	struct lnode *ln;
	ln = (struct lnode*) malloc(sizeof(struct lnode));
	ln->prev = ln->next = NULL;
	ln->wn = NULL;
	return ln;
};

struct wnode* wnodealloc() {
	struct wnode *wn;
	wn = (struct wnode*) malloc(sizeof(struct wnode));
	wn->word = NULL;
	wn->count = 0;
	wn->ln = NULL;
	wn->tn = NULL;
	return wn;
};


int lnodes_inorder(struct lnode *x, struct lnode *y) {
	if (x == NULL || y == NULL)
		return 1;
	if (x->wn->count < y->wn->count)
		return 1;
	if (x->wn->count == y->wn->count && strcmp(x->wn->word, y->wn->word) <= 0)
		return 1;

	return 0;
}


void swap_lnodes(struct lnode *x, struct lnode *y) {
	struct wnode* wn;
	struct lnode* ln;
	if (x == NULL || y == NULL)
		return;

	wn = x->wn;
	x->wn = y->wn;
	y->wn = wn;


	ln = x->wn->ln;
	x->wn->ln = y->wn->ln;
	y->wn->ln = ln;
}


void balance_word_list (struct lnode *ln) {
	/* make sure that we maintain the list ordered */
	struct lnode *cn;

	if (ln == NULL)
		return;

	cn = ln;

	while (cn != NULL && !lnodes_inorder(cn, cn->next)) {
		swap_lnodes(cn, cn->next);
		cn = cn->next;
	}
}

void add_to_word_list (struct wnode *wn, struct lnode *lroot ) {
	/* add this word node to the list */

	struct lnode *ln;

	if (lroot == NULL) {
		printf ("error, lroot can't be NULL\n");
		exit(1);
	}


	/* wn should be added as the second element in the list */

	ln = lnodealloc();
	ln->wn = wn;
	wn->ln = ln;
	ln->prev = lroot;
	ln->next = lroot->next;

	swap_lnodes(lroot, ln);

	if (lroot->next) {
		lroot->next->prev = ln;
	}

	lroot->next = ln;
	
}
void insert(struct words *w, char *word) {


	struct wnode *wn;
	struct tnode *tn, *cn;
	int cond;
	if (!w || (!w->troot && w->lroot) || (!w->lroot && w->troot))
		return;


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


	/* search the tree, and insert the node */

	tn = w->troot;

	while (1) {
		wn = tn->wn;

		if ((cond = strcmp(wn->word, word)) == 0) {
			/* well we have found the wnode */
			wn->count++;
			balance_word_list(wn->ln);
			break;

		} else if (cond < 0 ) {
			/* insert in the left subtree */
			if (tn->left) {
				tn = tn->left;
				continue;
			}
			/* allocate a new wnode */
			wn = wnodealloc();
			wn->word = strdup(word);
			wn->count = 1;

			cn = tnodealloc();
			cn->wn = wn;
			cn->parent = tn;
			tn->left = cn;
			wn->tn = cn;
			add_to_word_list(wn,w->lroot);
			break;
			
			
		} else {
			/* add to the right subtree */
			if (tn->right) {
				tn = tn->right;
				continue;
			}

			/* allocate a new wnode */
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
	printf ("word = %s, count = %d\n", troot->wn->word, troot->wn->count);
	printtree(troot->right);
}


void printlist (struct lnode *lroot) {
	while (lroot) {
		printf ("word = %s count = %d\n", lroot->wn->word, lroot->wn->count);
		lroot = lroot->next;
	}
}


int main() {
	struct words w;
	w.troot = NULL;
	w.lroot = NULL;
	insert(&w,"me");
	insert(&w,"me");
	insert(&w,"you");
	insert(&w,"you");
	insert(&w,"you");
	insert(&w,"your");
	insert(&w,"me");
	insert(&w,"me");
	insert(&w,"he");


	/*
	 * printf ("print the tree\n");
	 * printtree(w.troot);
	 */
	printf ("print the list\n");
	printlist(w.lroot);


	return 0;
}
