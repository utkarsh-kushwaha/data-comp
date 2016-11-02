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
	char curr_ch, prev_ch;
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	fdw = open(strcat(argv[1], ".myrle"), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fdw == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	read(fdr, &prev_ch, sizeof(prev_ch));
	runcount++;
	while((x = read(fdr, &curr_ch, sizeof(curr_ch)))) {
		if(curr_ch == prev_ch) {
			runcount++;
			continue;
		}
		write(fdw, &runcount, sizeof(runcount));
		write(fdw, &prev_ch, sizeof(prev_ch));
		prev_ch = curr_ch;
		runcount = 1;
	}
	write(fdw, &runcount, sizeof(runcount));
	write(fdw, &prev_ch, sizeof(prev_ch));
	close(fdr);
	close(fdw);
	return 0;
}
