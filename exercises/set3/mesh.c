#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * This algorithm is extremely unpleasant
*/

int
main(int argc, char **argv)
{
	int M;
	int N;
	int P;
	int Q;
	ssize_t i;
	ssize_t j;
	char *board;
	int xcount;
	int ycount;

	if (argc != 5)
		fprintf(stderr, "usage: %s M N P Q\n", argv[0]);
	M = atoi(argv[1]);
	N = atoi(argv[2]);
	P = atoi(argv[3]);
	Q = atoi(argv[4]);
	board = calloc(M * N, sizeof(*board));

	xcount = ycount = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (xcount < P)
				board[i*M + j] = 1;
			else
				board[i*M + j] = 0;

			if (xcount >= 2*P - 1)
				xcount = 0;
			else
				xcount++;
		}

		if (ycount < Q - 1)
			xcount = 0;
		else
			xcount = P;

		if (ycount >= 2*Q - 2)
			ycount = 0;
		else
			ycount++;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			printf("%d ", board[i*M + j]);
		}
		puts("");
	}

	return 0;
}
