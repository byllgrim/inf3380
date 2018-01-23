#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int
parselength(int argc, char *args[])
{
	long int n;
	char *endptr;
	char *nptr;
	size_t conv;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", args[0]);
		exit(EXIT_FAILURE);
	}

	nptr = args[1];
	endptr = nptr;

	errno = 0;
	n = strtol(nptr, &endptr, 10);
	conv = endptr - nptr;
	if (errno || conv < strlen(nptr)) {
		fprintf(stderr, "n is not an int\n");
		exit(EXIT_FAILURE);
	}

	return n;
}

int
main(int argc, char *args[])
{
	long int n;

	n = parselength(argc, args); /* TODO parsen? */
	printf("n = %ld\n", n);

	return 0;
}
