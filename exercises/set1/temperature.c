#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {BUFLEN = 4}; /* TODO increase */

struct temperature {
	uint8_t hour; /* hour of day */
	uint8_t min;  /* minute of hour */
	uint8_t deg;  /* degrees celcius */
	uint8_t frac; /* fractional part of deg */
};

int
main(int argc, char *argv[])
{
	int fd;
	char buf[BUFLEN + 1] = {0};

	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "failed to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	read(fd, buf, BUFLEN);
	printf("read '%s'\n", buf);

	return 0;
}
