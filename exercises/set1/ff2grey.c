#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct image {
	uint32_t width;
	uint32_t height;
	uint16_t *data; /* row-major greyscale values */
};

void
swapend32(char *b)
{
	uint32_t n;

	n = *(uint32_t *)b;

	b[0] = ((char *)&n)[3];
	b[1] = ((char *)&n)[2];
	b[2] = ((char *)&n)[1];
	b[3] = ((char *)&n)[0];
}

void
swapend16(char *b)
{
	uint16_t n;

	n = *(uint16_t *)b;

	b[0] = ((char *)&n)[1];
	b[1] = ((char *)&n)[0];
}

uint16_t
greyavg(uint16_t *rgba)
{
	uint32_t sum = 0;

	swapend16((char *)&rgba[0]);
	swapend16((char *)&rgba[1]);
	swapend16((char *)&rgba[2]);

	sum += 2*rgba[0] + 3*rgba[1] + 1*rgba[2];

	return sum / 6;
}

void
readrow(uint16_t *row, size_t width)
{
	uint16_t *buf;
	size_t bufsiz;
	size_t i;
	uint16_t pxl;
	uint16_t alpha = 0xFFFF;

	bufsiz = 4 * sizeof(*buf); /* RGBA */
	buf = malloc(bufsiz);

	for (i = 0; i < width; i++) {
		read(STDIN_FILENO, buf, bufsiz);
		pxl = greyavg(buf);
		swapend16((char *)&pxl);
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &alpha, sizeof(alpha));
	}
	(void)row; /* TODO assign to array */
}

void
readallrows(struct image image)
{
	size_t i;

	for (i = 0; i < image.height; i++) {
		readrow(&(image.data[i * image.width]), image.width);
	}
}

struct image
readff()
{
	struct image image;
	char magic[8+1];
	uint32_t width;
	uint32_t height;

	read(STDIN_FILENO, magic, sizeof(magic) - 1);
	magic[sizeof(magic) - 1] = '\0';
	write(STDOUT_FILENO, magic, 8);

	read(STDIN_FILENO, &width, sizeof(width));
	write(STDOUT_FILENO, &width, 4);
	swapend32((char *)&width);
	image.width = width; /* TODO omit redundant variables? */

	read(STDIN_FILENO, &height, sizeof(height));
	write(STDOUT_FILENO, &height, 4);
	swapend32((char *)&height);
	image.height = height; /* TODO omit redundant variables? */

	image.data = malloc(width * height * sizeof(*(image.data)));
	readallrows(image);

	return image;
}

int
main(void)
{
	readff(); /* TODO why refactor? */

	return 0;
}
