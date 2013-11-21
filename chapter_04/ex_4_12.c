#include <stdio.h>
#include <math.h>

void my_itoa(int n, char s[])
{
	int i, sign;

	i = 0;
	s[0] = '\0';
	if (n / 10) {
		my_itoa(n/10,s);
		while(s[i]) {
			i++;
		}

		s[i++] = abs(n%10) + '0';
	} else {
		sign = (n > 0)? 1:0;
		if(!sign) {
			s[i++] = '-';
		}
		s[i++] = abs(n) - 0 + '0';
	}

	s[i] = '\0';
}

int main() {

	int n = -12;
	char s[100];

	my_itoa(n,s);
	printf("s = %s\n", s);

	return 0;
}
