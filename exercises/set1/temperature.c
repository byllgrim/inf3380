#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {BUFLEN = 24}; /* TODO increase */

struct temperature {
	uint8_t hour; /* hour of day */
	uint8_t min;  /* minute of hour */
	int8_t deg;   /* degrees celcius */
	uint8_t frac; /* fractional part of deg */
};

void
printtemp(struct temperature temp)
{
	printf("%02d:%02d %3d.%d\n",
	       temp.hour, temp.min, temp.deg, temp.frac);
}

struct temperature
parsetemp(char *buf, size_t len)
{
	struct temperature temp = {0};
	char *endptr;
	char *nptr;

	temp.hour = strtol(buf, &endptr, 10);

	nptr = endptr;
	while (!isdigit(*nptr)) /* TODO bounds */
		nptr++;
	temp.min = strtol(nptr, &endptr, 10);

	nptr = endptr;
	while (isspace(*nptr)) /* TODO bounds */
		nptr++;
	temp.deg = strtol(nptr, &endptr, 10);

	nptr = endptr + 1;
	temp.frac = strtol(nptr, &endptr, 10);

	/* TODO error checking */
	return temp;
}

void
readfile(int fd)
{
	char buf[BUFLEN + 1] = {0};
	struct temperature temp = {0};

	read(fd, buf, BUFLEN);
	temp = parsetemp(buf, sizeof(buf) - 1);
	printtemp(temp);

	/* TODO error checking */
}

int
main(int argc, char *argv[])
{
	int fd;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "failed to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	readfile(fd);

	return 0;
}
