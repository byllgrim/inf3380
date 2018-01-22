#include <math.h>
#include <stdio.h>

int
main(void)
{
	int n = 10;
	int i = 0; /* TODO omit initializations? */
	double lim = 0.0;

	/* 1 - 1/2^2 + 1/2^4 - 1/2^6 + ... */
	/* +1/2^0 - 1/2^2 + 1/2^4 - 1/2^6 + ... */
	/* sum_0^n (-1)^i 1/2^(2i) */

	lim = 0.0;
	for (i = 0; i <= n; i++)
		lim += pow(-1, i) * 1 / pow(2, 2*i);

	printf("4/5 = %f\n", 4.0/5.0);
	printf("limit = %f\n", lim);
	return 0;
}
