/* C program for Huffman Decompression */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

#define FOUND 1
#define NOTFOUND 0

/*structure in the header of the compressed file*/
typedef struct wstruct {
	char ch;
	char str[32];
}wstruct;

/*struct used as key for decompressing the compressed file
 *clen->added to increase the speed of decompression
 */
typedef struct cmpstruct {
	char ch;
	char str[32];
	int16_t clen;
}cmpstruct;

/* Reads the header and forms the decompression table
 * containing character with its corresponding Huffman Code
 */
wstruct* readstruct(int argc, char *argv[], uint32_t *size) {
	uint32_t i = 0;
	uint32_t n;
	uint32_t fdr;
	wstruct *arrstruct;
	if(argc < 2) {
		errno = EINVAL;
		perror("[!]");
		exit(errno);
	}
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1) {	
		perror("[!] open failed");
		exit(errno);
	}
	read(fdr, &n, sizeof(n));
	*size = n;
	arrstruct = malloc(n * sizeof(wstruct));
	while(i < n) {
		read(fdr, &arrstruct[i], sizeof(wstruct));
		i++;
	}
	close(fdr);
	return arrstruct;
}

/*Forms the table to be used for reading compressed file using table obtained from header*/
cmpstruct* SETcmparr(wstruct *arrstruct, uint8_t size) {
	uint8_t k = size;
	cmpstruct* cmparr = (cmpstruct*)malloc(size * sizeof(cmpstruct));
	while(k) {
		k--;
		cmparr[size - 1 - k].ch = arrstruct[k].ch;
		strcpy(cmparr[size - 1 - k].str, arrstruct[k].str);
		cmparr[size - 1 - k].clen = strlen(arrstruct[k].str);
	}
	return cmparr;
}

/* Looks for the character corresponding to the code read from compressed file */
uint32_t MYstrcmp(char *str, cmpstruct *cmparr, uint32_t size, uint32_t *j) {
	uint32_t i = 0;
	uint32_t l = strlen(str);
	uint32_t match = NOTFOUND;
	while(i < size && cmparr[i].clen != l) {
		i++;
	}
	while(i < size && l == cmparr[i].clen) {
		if(!strcmp(cmparr[i].str, str)) {
			match = FOUND;
			break;
		}
		else
			i++;
	}
	*j = i;
	return match;	
}

/*Decodes the compressed file*/
void decodefile(char *argv[], wstruct *arrstruct, uint32_t size) {
	uint32_t fdr, fdw, len;
	uint64_t pos;
	uint32_t bit, padding, BitsBuffer, BitsInBuffer, Match, x = 1;
	uint32_t i;
	char str[32] = "\0", name[128];
	cmpstruct *cmparr;
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1) {	
		perror("[!] open failed");
		exit(errno);
	}
	pos = sizeof(size) + size * sizeof(wstruct);
	strcpy(name, argv[1]);
	name[(len = strlen(name)) - 5] = '-';
	name[len - 4] = '\0';
	/*Sets the position to start reading actual data in the file
	 *after the table is formed
	 */
	lseek(fdr, pos, 0);
	fdw = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IRUSR);
	if(fdr == -1) {	
		perror("[!] open failed");
		exit(errno);
	}
	read(fdr, &padding, sizeof(padding));
	/* Padding -> bits to be skipped from the start*/
	BitsInBuffer = padding;
	cmparr = SETcmparr(arrstruct, size);
	while(read(fdr, &BitsBuffer, sizeof(BitsBuffer))) {
		while(x) {
			Match = NOTFOUND;
			while(Match == NOTFOUND) {
				if(BitsInBuffer == 32) {
					x = read(fdr, &BitsBuffer, sizeof(BitsBuffer));
					if(x == 0)
						break;
					BitsInBuffer = 0;
				}
				bit = (BitsBuffer >> (31 - BitsInBuffer)) & 1;
				if(bit == 1)
					strcat(str, "1");
				else
					strcat(str, "0");
				Match = MYstrcmp(str, cmparr, size, &i);
				BitsInBuffer++;
			}
			if(Match == FOUND)
				write(fdw, &cmparr[i].ch, sizeof(char));
			strcpy(str, "\0");
		}
	}
}
int main(int argc, char *argv[]) {
	uint32_t size;
	wstruct *arrstruct;
	arrstruct = readstruct(argc, argv, &size);
	decodefile(argv, arrstruct, size);
	return 0;
}
