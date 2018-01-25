#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void
swapend32(char *b)
{
	(void)b;
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
	printf("width = %d\n", width);

	read(STDIN_FILENO, &height, sizeof(height));
	printf("height = %d\n", height);

	return 0;
}
