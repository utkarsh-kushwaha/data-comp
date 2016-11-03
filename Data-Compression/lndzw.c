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
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "lzw.h"
#include "lndzw.h"
#include "dictionary.h"

/* Adds new string spc->str to dictionary */
void addentry(dictionary *d, string *spc) {
	if(d->entry_count == d->max_limit) {
		d->max_limit += 4096;
		d->e = (entry*)realloc(d->e, d->max_limit * sizeof(entry));
		if(!d->e) {
			perror("File too large to compress");
			exit(1);
		}
	}
	d->e[d->entry_count].word = (uint8_t*)malloc(spc->len * sizeof(uint8_t));
	memcpy(d->e[d->entry_count].word, spc->str, spc->len);
	d->e[d->entry_count].len = spc->len;
	d->entry_count++;
}
/* concatenates the src to dest */
void* memcat(void *dest, uint32_t size_dest, void *src, uint32_t size_src) {
	dest = (uint8_t*)dest + size_dest;
	memcpy(dest, src, size_src);
	return dest;
}
/* Allocates the space for dictionary */
/* Initializes all the first 256 elements of dictionary to their corresponding index */
dictionary* init(void) {
	int i = 0;
	uint8_t ch = 0;
	uint16_t len = 1;
	
	dictionary *d = (dictionary*)malloc(sizeof(dictionary));
	d->e = (entry*)malloc(4096 * sizeof(entry));
	d->entry_count = 256;
	d->max_limit = 4000;

	for(i = 0; i < 256; i++) {
		d->e[i].word = (uint8_t*)malloc(sizeof(uint8_t));
		d->e[i].word[0] = ch++;
		d->e[i].len = len;
	}
	return d;
}
/* opens file at given path and handles errors if any */
FILE* file_open(char *path, char *mode) {
	FILE *fp;
	fp = fopen(path, mode);
	if(!fp) {
		/*display corresponding error message */
		fprintf(stderr, "[!] Failed to open %s : %s\n", path, strerror(errno));
		exit(errno);
	}
	return fp;
}
/* to free memory allocated to pointers of dictionary */
void free_dictionary(dictionary *d) {
	uint16_t i = 0;
	for(i = 0; i < d->entry_count; i++)
		free(d->e[i].word);
	free(d->e);
	free(d);
}

