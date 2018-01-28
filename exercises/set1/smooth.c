#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
readffmagic(void)
{
	char magic[8];

	read(STDIN_FILENO, magic, sizeof(magic));

	if (memcmp(magic, "farbfeld", sizeof(magic))) {
		fprintf(stderr, "bad magic\n");
		exit(EXIT_FAILURE);
	}
}

uint32_t
endian32(uint32_t value)
{
	uint32_t flipped = 0;

	flipped |= (value & 0x000000FF) << 24;
	flipped |= (value & 0x0000FF00) << 8;
	flipped |= (value & 0x00FF0000) >> 8;
	flipped |= (value & 0xFF000000) >> 24;

	return flipped;
}

void
readsize(uint32_t *width, uint32_t *height)
{
	read(STDIN_FILENO, width, sizeof(*width));
	*width = endian32(*width);

	read(STDIN_FILENO, height, sizeof(*height));
	*height = endian32(*height);
}

int
main(void)
{
	uint32_t width;
	uint32_t height;

	readffmagic();
	readsize(&width, &height);

	return EXIT_SUCCESS;
}
