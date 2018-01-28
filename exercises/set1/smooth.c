#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
readmagic(void)
{
	char magic[8];

	read(STDIN_FILENO, magic, sizeof(magic));

	if (memcmp(magic, "farbfeld", sizeof(magic))) {
		fprintf(stderr, "bad magic\n");
		exit(EXIT_FAILURE);
	}
}

uint32_t
readwidth(void)
{
	uint32_t width;

	read(STDIN_FILENO, &width, sizeof(width));

	return width;
}

void
readimage(void)
{
	uint32_t width;

	readmagic();
	width = readwidth();
}

int
main(void)
{
	readimage();

	return EXIT_SUCCESS;
}
