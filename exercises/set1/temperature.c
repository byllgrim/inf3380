#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {BUFLEN = 4}; /* TODO increase */

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
