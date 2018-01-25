#include <stdint.h>
#include <stdio.h>
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

int
main(void)
{
	char magic[8+1] = {0};
	uint32_t width;
	uint32_t height;

	read(STDIN_FILENO, magic, sizeof(magic) - 1);
	printf("magic = '%s'\n", magic);

	read(STDIN_FILENO, &width, sizeof(width));
	swapend32((char *)&width);
	printf("width = %d\n", width);

	read(STDIN_FILENO, &height, sizeof(height));
	swapend32((char *)&height);
	printf("height = %d\n", height);

	return 0;
}
