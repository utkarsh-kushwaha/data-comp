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
#include "file_size.h"

#define FOUND 1
#define NOTFOUND 0

void* _memcat(void *dest, uint32_t size_dest, void *src, uint32_t size_src) {
	dest = (uint8_t*)dest + size_dest;
	memcpy(dest, src, size_src);
	return dest;
}
/*struct used as key for decompressing the compressed file
 *len->added to increase the speed of decompression
 */
/*structure in the header of the compressed file*/
typedef struct wstruct {
	uint8_t ch;
	uint8_t str[32];
	uint16_t len;
}wstruct;
/* Reads the header and forms the decompression table
 * containing character with its corresponding Huffman Code
 */
wstruct* readstruct(char *input_file, uint32_t *size) {
	uint32_t i = 0;
	uint32_t n;
	int fdr;
	wstruct *cmparr;
	fdr = open(input_file, O_RDONLY);
	if(fdr == -1) {	
		perror("[!] Failed to open input file");
		exit(errno);
	}
	read(fdr, &n, sizeof(n));
	*size = n;
	cmparr = (wstruct*)malloc(n * sizeof(wstruct));
	while(i < n) {
		read(fdr, &cmparr[i], sizeof(wstruct));
		i++;
	}
	close(fdr);
	return cmparr;
}
/* Looks for the character corresponding to the code read from compressed file */
uint32_t MYstrcmp(uint8_t *str, uint16_t len, wstruct *cmparr, uint32_t size, uint32_t *j) {
	uint32_t i = size - 1;
	uint32_t match = NOTFOUND;
	while(i > 0 && cmparr[i].len != len) {
		i--;
	}
	while(len == cmparr[i].len) {
		if(!memcmp(cmparr[i].str, str, len)) {
			match = FOUND;
			break;
		}
		else {
			if(!i)
				break;
			i--;
		}
	}
	*j = i;
	return match;	
}

/*Decodes the compressed file*/
void decodefile(char* input_file, char *output_file, wstruct *cmparr, uint32_t size) {
	int fdr, fdw;
	uint32_t pos;
	uint32_t i, bit, padding, BitsBuffer, BitsInBuffer, Match, x = 1;
	uint8_t str[32], one = 1, zero = 0;
	uint16_t len = 0;
	unsigned int j = 0, bytes_read = 0, fsize = file_size(input_file);
	unsigned int percent = 0, val_percent = fsize / 100;

	fdr = open(input_file, O_RDONLY);
	if(fdr == -1) {	
		perror("[!] Failed to open input file");
		exit(errno);
	}
	pos = sizeof(size) + size * sizeof(wstruct);
	/*Sets the position to start reading actual data in the file
	 *after the table is formed
	 */
	lseek(fdr, pos, SEEK_CUR);
	fdw = open(output_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fdr == -1) {	
		perror("[!] Failed to open output file");
		exit(errno);
	}
	read(fdr, &padding, sizeof(padding));
	/* Padding -> bits to be skipped from the start*/
	BitsInBuffer = padding;
	while(read(fdr, &BitsBuffer, sizeof(BitsBuffer))) {
		while(x) {
			Match = NOTFOUND;
			while(Match == NOTFOUND) {
				if(BitsInBuffer == 32) {
					x = read(fdr, &BitsBuffer, sizeof(BitsBuffer));

					bytes_read += x;
					if(bytes_read >= val_percent) {
						printf("\rDecompressing %s [%d%%] ", input_file, percent++);
						bytes_read = 0;
					}
					if(j == 5000)
						printf("\b\\");
					else if(j == 10000)
						printf("\b|");
					else if(j == 15000)
						printf("\b/");
					else if(j == 20000) {
						printf("\b-");
						j = 0;
					}
					fflush(stdout);
					j++;

					if(x == 0)
						break;
					BitsInBuffer = 0;
				}
				bit = (BitsBuffer >> (31 - BitsInBuffer)) & 1;
				if(bit == 1)
					_memcat(str, len, &one, 1);
				else
					_memcat(str, len, &zero, 1);

				len++;
				Match = MYstrcmp(str, len, cmparr, size, &i);
				BitsInBuffer++;
			}
			if(Match == FOUND)
				write(fdw, &cmparr[i].ch, sizeof(uint8_t));
			len = 0;
		}
	}
	fflush(stdout);
	printf("\rDecompressing %s [%d%%] Done...\n", input_file, 100);
}

void dehuffman(char *input_file, char *output_file) {
	uint32_t size;
	wstruct *cmparr;
	cmparr = readstruct(input_file, &size);
	decodefile(input_file, output_file, cmparr, size);
}
