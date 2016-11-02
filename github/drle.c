#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int fdr, fdw;
	int x, runcount = 0;
	char ch;
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	fdw = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fdw == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	while((x = read(fdr, &runcount, sizeof(runcount)))) {
		read(fdr, &ch, sizeof(ch));
		while(runcount--)
			write(fdw, &ch, sizeof(ch));
	}
	close(fdr);
	close(fdw);
	return 0;
}
