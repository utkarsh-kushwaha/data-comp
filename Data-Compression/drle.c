#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void drle(char *input_file, char *output_file) {
	int fdr, fdw;
	int x, runcount = 0;
	char ch;
	fdr = open(input_file, O_RDONLY);
	if(fdr == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	fdw = open(output_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
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
}
