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
#include <stdint.h>
#include <errno.h>
#include "dlzw.h"
#include "lndzw.h"

/* LZW Decompression */
void dlzw(char *input_file, char *output_file) {
	FILE *fpr, *fpw;
	dictionary *d;
	
	uint16_t pW, cW;
	string s;
	uint8_t c[1];
	uint32_t len_c = 1;

	fpr = file_open(input_file, "r");
	fpw = file_open(output_file, "w");	
	d = init();
	
	fread(&cW, sizeof(uint16_t), 1, fpr);
	fwrite(d->e[cW].word, sizeof(uint8_t), d->e[cW].len, fpw);
	pW = cW;

	while(fread(&cW, sizeof(uint16_t), 1, fpr)) {
		if(cW < d->entry_count) {
			fwrite(d->e[cW].word, sizeof(uint8_t), d->e[cW].len, fpw);
			memcpy(s.str, d->e[pW].word, s.len = d->e[pW].len);
			c[0] = d->e[cW].word[0];
			memcat(s.str, s.len, c, len_c);
			s.len += len_c;
			_addentry(d, &s);
		} else {
			memcpy(s.str, d->e[pW].word, s.len = d->e[pW].len);
			c[0] = d->e[pW].word[0];
			memcat(s.str, s.len, c, len_c);
			s.len += len_c;
			fwrite(s.str, sizeof(uint8_t), s.len, fpw);
			_addentry(d, &s);
		}
		pW = cW;
	}
        printf("\rDecompressing %s [%d%%] Done...\n", input_file, 100);
	free_dictionary(d);
	fclose(fpr);
	fclose(fpw);
}
/* Reallocates the space if the dictionary limit is reached
 * Appends the string new_word->str to dictionary at d->entry count
 * and increments the count */
void _addentry(dictionary *d, string *new_word) {
	if(d->entry_count == d->max_limit) {
		d->max_limit += 4096;
		d->e = (entry*)realloc(d->e, d->max_limit * sizeof(entry));
		if(!d->e) {
			perror("File too large to decompress");
			exit(1);
		}
	}
	d->e[d->entry_count].word = (uint8_t*)malloc(new_word->len * sizeof(uint8_t));
	memcpy(d->e[d->entry_count].word, new_word->str, new_word->len);
	d->e[d->entry_count].len = new_word->len;
	d->entry_count++;
}

