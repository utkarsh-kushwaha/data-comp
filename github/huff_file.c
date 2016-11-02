#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include "head.h"
#include "huff_file.h"

/*calculates and sets frequency of each unique character in original file*/
info* setfreq(int32_t *size, int argc, char *argv[]) {
	typedef struct charc {
		char ch;
		int32_t freq;
	}charc;
	charc *p = (charc*)malloc(sizeof(charc));
	char c;
	int32_t fd, i, n = 0, x;
	info *arr;
	if(argc != 2) {
		errno = EINVAL;
		perror("[!]");
		exit(errno);
	}
	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror("[!] Can't open");
		exit(errno);
	}
	while((x = read(fd, &c, sizeof(c)))) {
		i = 0;
		while(i < n) {
			if(c == p[i].ch) {	/*check if the char exists in */
				p[i].freq++;	/*the array of unique char in the text */
				break;
			}
			else
				i++;
		}
		if(i == n) {
			p[n].ch = c;
			p[n].freq = 1;
			p = (charc*)realloc(p, sizeof(charc) * (n + 1) * 2);
			n++;
		}
	}
	close(fd);
	i = 0;
	*size = n;
	arr = (info*)malloc(sizeof(info) * n);
	while(i < n) {
		arr[i].ch = p[i].ch;
		arr[i].freq = p[i].freq;
		i++;
	}
	free(p);
	mergesort(arr, 0, n - 1);
	return arr;
}
/*write Header structures containing characters and codes to compressed file*/
void writecodes(int argc, char *argv[], wstruct *arrstruct, int32_t size) {
	
	int32_t i = 0;
	int fd;
	char name[64];
	strcpy(name, argv[1]);
	strcat(name, ".huff");
	if(argc < 2) {
		errno = EINVAL;
		perror("[!]");
		exit(errno);
	}
	fd = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {	
		perror("[!] open failed");
		exit(errno);
	}
	write(fd, &size, sizeof(size));
	while(i < size) {
		write(fd, &arrstruct[i], sizeof(wstruct));
		i++;
	}
}
int calculatepadding(info *arr, wstruct *arrstruct, int size) {
	int i = 0, buffer = 0;
	while(i < size) {
		buffer += arr[i].freq * strlen(arrstruct[i].str);
		i++;
	}
	/*total bits in compressed file corresponding to actual file */
	buffer = 32 - buffer % 32;
	return buffer;
}

void writefile(char *argv[], info *arr, wstruct *arrstruct, int size) {
	int fdr, fdw;
	int32_t padding, BitsBuffer = 0, BitsInBuffer;
	int32_t i, k, top;
	char ch;
	char name[64];
	strcpy(name, argv[1]);
	strcat(name, ".huff");
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1) {
		perror("[!] open failed");
		exit(errno);
	}
	fdw = open(name, O_RDWR);
	if(fdw == -1) {
		perror("[!] open failed");
		exit(errno);
	}
	/*Start writing data converted to Huffman codes at the end of header*/
	lseek(fdw, 0L, 2);
	padding = calculatepadding(arr, arrstruct, size);
	/* number of bits to be buffered before actual file data starts */
	BitsInBuffer = padding;
	write(fdw, &padding, sizeof(padding));
	while(read(fdr, &ch, sizeof(ch))) {
		i = 0;
		while(i < size) {
			if(ch == arrstruct[i].ch)
				break;
			else
				i++;
		}
		top = strlen(arrstruct[i].str);
		k = 0;
		while(k != top) {
			if(arrstruct[i].str[k] == '1')
				BitsBuffer |= (1 << (31 - BitsInBuffer));
			else
				BitsBuffer &= ~(1 << (31 - BitsInBuffer));
			k++;
			BitsInBuffer++;
			if(BitsInBuffer == 32) {
				write(fdw, &BitsBuffer, sizeof(BitsBuffer));
				BitsInBuffer = 0;	/*clear buffer and buffercount*/
			}
		}
	}
}
