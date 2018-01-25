#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
readrow(uint32_t width)
{
	uint16_t buf[4]; /* RGBA */
	size_t i;
	uint16_t pxl;
	uint16_t alpha = 0xFFFF;

	for (i = 0; i < width; i++) {
		read(STDIN_FILENO, buf, sizeof(buf));
		pxl = greyavg(buf);
		swapend16((char *)&pxl);
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &pxl, sizeof(pxl));
		write(STDOUT_FILENO, &alpha, sizeof(alpha));
	}
}

void
readallrows(uint32_t height, uint32_t  width)
{
	size_t i;

	for (i = 0; i < height; i++) {
		readrow(width);
	}
}

int
main(void)
{
	char magic[8];
	uint32_t width;
	uint32_t height;

	read(STDIN_FILENO, magic, sizeof(magic));
	write(STDOUT_FILENO, magic, sizeof(magic));

	read(STDIN_FILENO, &width, sizeof(width));
	write(STDOUT_FILENO, &width, 4);
	swapend32((char *)&width);

	read(STDIN_FILENO, &height, sizeof(height));
	write(STDOUT_FILENO, &height, 4);
	swapend32((char *)&height);

	readallrows(height, width);

	return 0;
}
