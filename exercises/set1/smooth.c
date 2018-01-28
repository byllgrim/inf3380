#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *
ecalloc(size_t nmemb, size_t size)
{
	void *mem;

	mem = calloc(nmemb, size);
	if (!mem) {
		fprintf(stderr, "alloc failed\n");
	}

	return mem;
}

void
readffmagic(void)
{
	char magic[8];
	size_t nb;

	nb = read(STDIN_FILENO, magic, sizeof(magic));

	if (nb != sizeof(magic)) {
		fprintf(stderr, "failed to read magic\n");
		exit(EXIT_FAILURE);
	}

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
	size_t nb;

	nb = read(STDIN_FILENO, width, sizeof(*width));
	if (nb != sizeof(*width)) {
		fprintf(stderr, "failed to read width\n");
		exit(EXIT_FAILURE);
	}
	*width = endian32(*width);

	read(STDIN_FILENO, height, sizeof(*height));
	if (nb != sizeof(*height)) {
		fprintf(stderr, "failed to read height\n");
		exit(EXIT_FAILURE);
	}
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
	size_t nb;

	pxls1d = ecalloc(width * height, sizeof(*pxls1d));
	pxls2d = ecalloc(height, sizeof(*pxls2d));
	for (i = 0; i < height; i++)
		pxls2d[i] = &pxls1d[i *width];

	rowsiz = width * 4 * sizeof(uint16_t);
	buf = ecalloc(rowsiz, 1);

	for (i = 0; i < height; i++) {
		nb = fread(buf, 1, rowsiz, stdin);
		if (nb < rowsiz) {
			fprintf(stderr, "reading row %d failed\n", i);
			exit(EXIT_FAILURE);
		}

		for (j = 0; j < width; j++) {
			pxl = buf[4 * j];
			pxl = endian16(pxl);
			pxls2d[i][j] = pxl;
		}
	}

	return pxls2d;
}

void
printff(uint32_t width, uint32_t height, uint16_t **pxls)
{
	uint16_t pxl;
	size_t i;
	size_t j;
	uint16_t alpha = 0xFFFF;
	ssize_t nb;

	nb = write(STDOUT_FILENO, "farbfeld", 8);
	if (nb != 8) {
		fprintf(stderr, "failed to write magic\n");
		exit(EXIT_FAILURE);
	}

	width = endian32(width);
	nb = write(STDOUT_FILENO, &width, sizeof(width));
	if (nb != sizeof(width)) {
		fprintf(stderr, "failed to write width\n");
		exit(EXIT_FAILURE);
	}
	width = endian32(width);

	height = endian32(height);
	nb = write(STDOUT_FILENO, &height, sizeof(height));
	if (nb != sizeof(height)) {
		fprintf(stderr, "failed to write height\n");
		exit(EXIT_FAILURE);
	}
	height = endian32(height);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			pxl = pxls[i][j];
			pxl = endian16(pxl);
			write(STDOUT_FILENO, &pxl, sizeof(pxl));
			write(STDOUT_FILENO, &pxl, sizeof(pxl));
			write(STDOUT_FILENO, &pxl, sizeof(pxl));
			write(STDOUT_FILENO, &alpha, sizeof(alpha));
		}
	}
}

void
smooth(uint32_t width, uint32_t height, uint16_t **pxls)
{
	size_t i;
	size_t j;
	uint16_t *tmp1d;
	uint16_t **tmp2d;
	uint16_t now;
	uint16_t left;
	uint16_t right;
	uint16_t up;
	uint16_t down;
	int32_t new;
	double c = 0.16;

	tmp1d = ecalloc(width * height, sizeof(*tmp1d));
	memcpy(tmp1d, *pxls, width * height * sizeof(*tmp1d));

	tmp2d = ecalloc(height, sizeof(*tmp2d));
	for (i = 0; i < height; i++)
		tmp2d[i] = &tmp1d[i * width];

	for (i = 1; i < height - 1; i++) {
		for (j = 1; j < width - 1; j++) {
			now = tmp2d[i][j];
			left = tmp2d[i][j - 1];
			right = tmp2d[i][j + 1];
			up = tmp2d[i - 1][j];
			down = tmp2d[i + 1][j];
			new = now + c * (up + left - 4 * now + right + down);
			new = new > 0xFFFF ? 0xFFFF : new;
			new = new < 0 ? 0 : new;
			pxls[i][j] = new;
		}
	}

	free(tmp1d);
	free(tmp2d);
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

	smooth(width, height, pxls);
	printff(width, height, pxls);

	return EXIT_SUCCESS;
}
