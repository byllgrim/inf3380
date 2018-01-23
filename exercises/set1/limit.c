#include <math.h>
#include <stdio.h>

int
main(void)
{
	int n; /* TODO initialize all vs not? */
	int i;
	double lim;
	int sign;
	double denom; /* TODO fastest: int mult vs float mult? */
	double coeff;

	/* 1 - 1/2^2 + 1/2^4 - 1/2^6 + ... */
	/* +1/2^0 - 1/2^2 + 1/2^4 - 1/2^6 + ... */
	/* +1/1 - 1/4 + 1/16 - 1/64 + ... */
	/* sum_0^n (-1)^i 1/2^(2i) */

	n = 10;
	lim = 0;
	sign = 1;
	denom = 1;
	coeff = 1;
	/* TODO define @ declare vs use? */
	for (i = 0; i <= n; i++) {
		/* lim += pow(-1, i) * 1 / pow(2, 2*i); */

		/* lim += sign * 1 / pow(2, 2*i); */

		/* lim += sign * 1 / denom; */

		/*
		lim += sign / denom;
		denom *= 4;
		*/
		(void)denom;

		lim += sign * coeff;
		coeff *= 0.25;
		sign *= -1;
	}

	printf("4/5 = %f\n", 4.0/5.0);
	printf("limit = %f\n", lim);
	return 0;
}
