#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int m = 2;
	int n = 3;
	int *Adata;
	int **A;
	int i;
	int j;

	Adata = malloc(m * n * sizeof(*Adata));
	A = malloc(m * sizeof(*A));
	for (i = 0; i < m; i++)
		A[i] = &Adata[i * n];

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			A[i][j] = i*n + j;
	}

	for (i = 0; i < m; i++) {        /* rows */
		for (j = 0; j < n; j++){ /* cols */
			/* printf("%d ", A[i][j]); */
			printf("%d ", *(*(A + i) + j));
		}
		printf("\n");
	}

	printf("\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			/* printf("%d ", A[j][i]); */
			printf("%d ", *(*(A + j) + i));
		printf("\n");
	}

	if (Adata)
		free(Adata);
	if (A)
		free(A);
	return 0;
}
