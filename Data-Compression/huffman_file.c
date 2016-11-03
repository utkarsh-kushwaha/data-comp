/*
 **********************************************************************
 * Copyright (C) 2016  Utkarsh Kushwaha (111503037)

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *********************************************************************** */
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
#include "huffman_file.h"
#include "file_size.h"

/*calculates and sets frequency of each unique character in original file*/
info* setfreq(uint32_t *size, char *input_file) {
	typedef struct charc {
		uint8_t ch;
		uint32_t freq;
	}charc;
	charc *p = (charc*)malloc(sizeof(charc));
	uint8_t c;
	uint32_t i, n = 0, x;
	int fd;
	info *arr;
	fd = open(input_file, O_RDONLY);
	if(fd == -1) {
		perror("[!] Failed to open input file");
		exit(errno);
	}
	while((x = read(fd, &c, sizeof(uint8_t)))) {
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
	*size = n;
	arr = (info*)malloc(sizeof(info) * n);
	i = 0;
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
void writecodes(char *output_file, wstruct *arrstruct, uint32_t size) {
	
	uint32_t i = 0;
	int fd;
	fd = open(output_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {	
		perror("[!] Failed to open input file");
		exit(errno);
	}
	write(fd, &size, sizeof(size));
	while(i < size) {
		write(fd, &arrstruct[i], sizeof(wstruct));
		i++;
	}
}
uint32_t calculatepadding(info *arr, wstruct *arrstruct, uint32_t size) {
	uint32_t i = 0, buffer = 0;
	while(i < size) {
		buffer += arr[i].freq * arrstruct[i].len;
		i++;
	}
	/*total bits in compressed file corresponding to actual file */
	buffer = 32 - buffer % 32;
	return buffer;
}

void writefile(char *input_file, char *output_file, info *arr, wstruct *arrstruct, uint32_t size) {
	int fdr, fdw;
	uint32_t padding, BitsBuffer = 0, BitsInBuffer;
	uint32_t i, k, top;
	uint8_t ch, one = 1;
	unsigned int j = 0, bytes_read = 0, fsize = file_size(input_file);
	unsigned int percent = 0, val_percent = fsize / 100;
	fdr = open(input_file, O_RDONLY);
	if(fdr == -1) {
		perror("[!] open failed");
		exit(errno);
	}
	fdw = open(output_file, O_RDWR);
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
		top = arrstruct[i].len;
		k = 0;
		while(k != top) {
			if(arrstruct[i].str[k] == one)
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
                bytes_read++;
		if(bytes_read == val_percent) {
	                printf("\rCompressing %s [%d%%] ", input_file, percent++);
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
	}
	fflush(stdout);
	printf("\rCompressing %s [%d%%] \n", input_file, 100);
}
