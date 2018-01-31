#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {DATASIZ = 1024};

uint16_t *
generatedata(size_t siz)
{
	size_t i;
	uint16_t *buf;

	buf = malloc(siz);
	if (!buf) {
		fprintf(stderr, "generatedata: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < siz; i++) {
		buf[i] = i;
	}

	return buf;
}

void
writebinary(uint16_t* buf, size_t siz)
{
	int fd;

	fd = open("binary.dat", O_WRONLY | O_CREAT | O_TRUNC, 00600);
	if (fd == -1) {
		fprintf(stderr, "writebinary: open failed\n");
		exit(EXIT_FAILURE);
	}

	/* TODO write data */

	close(fd);
}

int
main(void)
{
	uint16_t *data;

	data = generatedata(DATASIZ);
	writebinary(data, DATASIZ);

	free(data);
	return 0;
}
