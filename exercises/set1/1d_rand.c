#include <assert.h> /* TODO assert.h suck */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct minmax {
	int min;
	int max;
};

long int
parselength(int argc, char *args[])
{
	long int n;
	char *endptr;
	char *nptr;
	size_t conv;

	assert(argc == 2);

	nptr = args[1];
	endptr = nptr;

	errno = 0;
	n = strtol(nptr, &endptr, 10);
	conv = endptr - nptr;

	assert(!errno);
	assert(conv == strlen(nptr));
	return n;
}

int *
createarray(long int n)
{
	int *arr = 0;

	assert(n);
	arr = malloc(n * sizeof(*arr));

	assert(arr);
	return arr;
}

void
printarr(int *arr, long int n)
{
	long int i;

	assert(arr);
	assert(n);
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

void
fillrand(int *arr, long int n)
{
	long int i;
	int tmp;

	assert(arr);
	assert(n);
	for (i = 0; i < n; i++)
		arr[i] = rand() % 100;

	/* TODO seed rand */
}

struct minmax
findminmax(int *arr, long int n)
{
	struct minmax minmax;
	int min;
	int max;
	long int i;

	assert(arr);
	assert(n);

	min = arr[0];
	max = arr[0];
	for (i = 0; i < n; i++) {
		arr[i] < min ? min = arr[i] : (void)0;
		arr[i] > max ? max = arr[i] : (void)0;
	}

	minmax.min = min;
	minmax.max = max;
	return minmax;
}

int
main(int argc, char *args[])
{
	long int n;
	int *arr = 0;
	struct minmax minmax;

	n = parselength(argc, args); /* TODO parsen? */
	arr = createarray(n);
	fillrand(arr, n);

	printarr(arr, n);
	minmax = findminmax(arr, n);
	printf("min %d\n", minmax.min);
	printf("max %d\n", minmax.max);

	if (arr)
		free(arr);
	return 0;
}
