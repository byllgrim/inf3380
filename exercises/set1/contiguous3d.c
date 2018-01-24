#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int nx = 3;
	int ny = 3;
	int nz = 3;
	int *A1d;
	int **A2d;
	int ***A3d;
	int i;
	int j;
	int k;

	A1d = malloc(nx * ny * nz * sizeof(*A1d));
	A2d = malloc(nx * ny * sizeof(*A2d));
	A3d = malloc(nx * sizeof(*A3d));

	for (k = 0; k < nx * ny * nz; k++) {
		A1d[k] = k;
	}
	for (j = 0; j < nx * ny; j++) {
		A2d[j] = &A1d[j * nz];
	}
	for (i = 0; i < nx; i++) {
		A3d[i] = &A2d[i * ny];
	}

	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			for (k = 0; k < nz; k++) {
				printf("%2d ", A3d[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	free(A1d);
	free(A2d);
	free(A3d);
	return 0;
}
