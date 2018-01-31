#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {DATALEN = 1024};

uint16_t *
generatedata(size_t len)
{
	size_t i;
	uint16_t *buf;

	buf = malloc(len * sizeof(*buf));
	if (!buf) {
		fprintf(stderr, "generatedata: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < len; i++) {
		buf[i] = i;
	}

	return buf;
}

void
writebinary(uint16_t* buf, size_t len)
{
	int fd;
	size_t nb;

	fd = open("binary.dat", O_WRONLY | O_CREAT | O_TRUNC, 00600);
	if (fd == -1) {
		fprintf(stderr, "writebinary: open failed\n");
		exit(EXIT_FAILURE);
	}

	/* TODO write several times */
	nb = write(fd, buf, len * sizeof(*buf));
	if (nb != len * sizeof(*buf)) {
		fprintf(stderr, "writebinary: write failed %d %d\n", nb, len);
		exit(EXIT_FAILURE);
	}

	close(fd);
}

void
writeascii(uint16_t* buf, size_t len)
{
	FILE *file;
	size_t i;

	file = fopen("ascii.dat", "w");
	if (!file) {
		fprintf(stderr, "writeascii: failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < len; i++)
		fprintf(file, "%05d", buf[i]);

	fclose(file);
}

int
main(void)
{
	uint16_t *data = (void *)0;

	data = generatedata(DATALEN);
	writebinary(data, DATALEN);
	writeascii(data, DATALEN);

	if (data)
		free(data);
	return 0;
}
