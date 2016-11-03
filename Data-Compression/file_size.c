#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*Return size of file specified by path in bytes*/
unsigned int file_size(char *path) {
	struct stat file_status;
	int fd;
	
	fd = open(path, O_RDONLY);
	if(fd == -1) {
		fprintf(stderr, "unable to determine size of %s : %s\n", path, strerror(errno));
		exit(errno);
	}
	if(fstat(fd, &file_status) || !S_ISREG(file_status.st_mode)) {
		fprintf(stderr, "%s is not a regular file\n", path);
		exit(errno);
	}
	return file_status.st_size;
}

