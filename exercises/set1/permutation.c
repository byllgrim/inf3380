#include <stdio.h>

void
swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void
sort(int arr[], int beg, int end)
{
	int piv;
	int l;
	int r;

	if (end <= beg + 1)
		return;

	piv = arr[beg];
	l = beg + 1;
	r = end;
	for (; l < r; ) {
		if (arr[l] <= piv)
			l++;
		else
			swap(&arr[l], &arr[--r]);
	}

	swap(&arr[--l], &arr[beg]);
	sort(arr, beg, l);
	sort(arr, r, end);
}

void
sortperm(int arr[], int perm[], int beg, int end)
{
	int piv;
	int l;
	int r;

	if (end <= beg + 1)
		return;

	piv = arr[perm[beg]];
	l = beg + 1;
	r = end;
	for (; l < r; ) {
		if (arr[perm[l]] <= piv)
			l++;
		else
			swap(&perm[l], &perm[--r]);
	}

	swap(&perm[--l], &perm[beg]);
	sortperm(arr, perm, beg, l);
	sortperm(arr, perm, r, end);
}

int
main(void)
{
	size_t i;
	int arr[] = {5, 2, 3, 1, 4, 6};
	int perm[] = {0, 1, 2, 3, 4, 5};

	sortperm(arr, perm, 0, 5);
	for (i = 0; i < 6; i++)
		printf("[%02d] %02d\n", i, arr[i]);
	printf("\n");
	for (i = 0; i < 6; i++)
		printf("[%02d] %02d\n", i, arr[perm[i]]);

	return 0;
}
