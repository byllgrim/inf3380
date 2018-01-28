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

uint16_t
endian16(uint16_t value)
{
	uint16_t flipped = 0;

	flipped |= (value & 0x00FF) << 8;
	flipped |= (value & 0xFF00) >> 8;

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

uint16_t **
readpxls(uint32_t width, uint32_t height)
{
	uint16_t *pxls1d;
	uint16_t **pxls2d;
	size_t i;
	size_t rowsiz;
	uint16_t *buf;
	size_t j;
	uint16_t pxl;

	pxls1d = malloc(width * height * sizeof(*pxls1d));
	pxls2d = malloc(height * sizeof(*pxls2d));
	for (i = 0; i < height; i++)
		pxls2d[i] = &pxls1d[i *width];

	rowsiz = width * 4 * sizeof(uint16_t);
	buf = malloc(rowsiz);

	for (i = 0; i < height; i++) {
		read(STDIN_FILENO, buf, rowsiz);
		for (j = 0; j < width; j++) {
			pxl = buf[4 * j];
			pxl = endian16(pxl);
			pxls2d[i][j] = pxl;
		}
	}

	return pxls2d;
}

int
main(void)
{
	uint32_t width;
	uint32_t height;
	uint16_t **pxls;

	readffmagic();
	readsize(&width, &height);
	pxls = readpxls(width, height);

	return EXIT_SUCCESS;
}
