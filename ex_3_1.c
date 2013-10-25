/*
 * Exercise 3-1. Our binary search makes two tests
 * inside the loop, when one would suffice (at the
 * price of more tests outside.) Write a version with
 * only one test inside the loop and measure the
 * difference in run-time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 10000

int arr[ARRAYSIZE];

int gen_arr() {
	int i;
	srand (time(NULL));

	for (i = 0; i < ARRAYSIZE; i++) {
		arr[i] = (int) (rand()/2);
	}
	
	return 0;
}

/*
 * this is a dummy bobble sort, it could be better
 */
int sort() {
	int i,j,t;
	for (i = 0; i < ARRAYSIZE - 1; i++) {
		for (j = i+1; j < ARRAYSIZE; j++ ) {
			if ( arr[i] > arr[j] ) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
	return 0;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid - 1;
		else if (x  > v[mid])
			low = mid + 1;
		else    /* found match */
			return mid;
	}

	return -1;   /* no match */
}

int binsearch2(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	if (v[low] > x || v[high] < x)
		return -1;

	while (low < high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	if (low == high && v[low] == x )
		return low;
	

	return -1;   /* no match */
}

int main() {
	int r,p;
	gen_arr();
	sort();

	/* now we need to find a random value */
	r = (int) (rand()/2);
	p = binsearch2(r,arr,ARRAYSIZE);
	printf("%d found at position %d\n", r, p );
	
	return 0;
}
