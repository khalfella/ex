#include <stdio.h>
#include <string.h>


#define SWAP(t,x,y)	do { 			\
			t  _tmp_;		\
			_tmp_	= 	x;	\
			x	=	y;	\
			y	=	_tmp_;	\
			} while (0)
			

void reverse(char s[], int len) {
	char c;
	if (len > 1) {
		SWAP(char,s[0],s[len-1]);

		reverse(&s[1], len - 2);
	}

}

int main() {
	char str[] = "mohamed abc";
	reverse(str, strlen(str));
	printf ("reverse is %s\n", str);
}
