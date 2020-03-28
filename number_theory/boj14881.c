#include <stdio.h>

int gcd(int a, int b) {
	int r = a % b; 
	if (r == 0)
		return b;
	else
		gcd(b, r); 
}

void canMake(int a, int b, int c) {
	int k = gcd(a, b);
	if (c % k == 0)
		printf("YES\n");
	else
		printf("NO\n");
	return;
}

int main(void) {
	int testcaseN; 
	scanf("%d", &testcaseN); 

	int a, b, c; 
	for (int i = 0; i < testcaseN; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (b > a) {
			int temp = a;
			a = b;
			b = temp;
		}
		if (a < c)
			printf("NO\n"); 
		else {
			canMake(a, b, c); 
		}
	}
	return 0; 
}