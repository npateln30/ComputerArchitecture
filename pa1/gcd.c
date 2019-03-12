
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	if ((argc - 1) != 2) {
		return 0;
	}

	int gcd = 1;
	int i;

	int one = atoi(argv[1]);
	int two = atoi(argv[2]);
	for (i = 1; i <= fmin(one, two); i++) {
		if (one % i == 0 && two % i == 0) {
			gcd = fmax(gcd, i);
		}
	}

	printf("%d\n", gcd);

	return 0;
}
