#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {DATALEN = 2048};

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
writebinary(uint16_t* buf, size_t len, char *filename)
{
	int fd;
	size_t nb;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00600);
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
writeascii(uint16_t* buf, size_t len, char *filename)
{
	FILE *file;
	size_t i;

	file = fopen(filename, "w");
	if (!file) {
		fprintf(stderr, "writeascii: failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < len; i++)
		fprintf(file, "%05d", buf[i]);

	fclose(file);
}

void
readbinary(char *filename)
{
	int fd;
	uint16_t *buf;

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "readbinary: failed to open file\n");
		exit(EXIT_FAILURE);
	}

	buf = malloc(BUFSIZ);
	if (!buf) {
		fprintf(stderr, "readbinary: mallocing buf failed\n");
		exit(EXIT_FAILURE);
	}

	for (; read(fd, buf, BUFSIZ) > 0;)
		;

	free(buf);
	close(fd);
}

void
readascii(char *filename)
{
	FILE *file;
	int *buf;
	size_t i;

	file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "readascii: failed to open file\n");
		exit(EXIT_FAILURE);
	}

	buf = malloc(BUFSIZ);
	if (!buf) {
		fprintf(stderr, "readascii: failed to malloc buf\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; !feof(file); i++)
		fscanf(file, "%05d", &buf[i]);

	free(buf);
	fclose(file);
}

int
main(void)
{
	uint16_t *data = (void *)0;
	char *binname = "binary.dat";
	char *asciiname = "ascii.dat";
	size_t i;

	data = generatedata(DATALEN);
	for (i = 0; i < 1000; i++) {
		writebinary(data, DATALEN, binname);
		writeascii(data, DATALEN, asciiname);
		readbinary(binname);
		readascii(asciiname);
	}

	if (data)
		free(data);
	return 0;
}
