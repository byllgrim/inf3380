#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
realcpy(void *dst, void *src, size_t n)
{
	memcpy(dst, src, n);
}

void
shitcpy(char *dst, char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
		dst[i] = src[i];
}

int
main(void)
{
	char *buf1;
	char *buf2;
	size_t i;

	buf1 = malloc(BUFSIZ);
	buf2 = malloc(BUFSIZ);

	for (i = 0; i < 1000; i++) {
		realcpy(buf1, buf2, BUFSIZ);
		shitcpy(buf1, buf2, BUFSIZ);
	}

	return EXIT_SUCCESS;
}
