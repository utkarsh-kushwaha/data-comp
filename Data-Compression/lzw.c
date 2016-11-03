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
#include "lzw.h"
#include "lndzw.h"
#include "file_size.h"

/* LZW compression */
void lzw(char *input_file, char *output_file) {
	FILE *fpr, *fpw;
	string s, spc;
	uint8_t c[1];
	uint32_t len_c;
	uint16_t v;
	unsigned int j = 0, bytes_read = 0, size = file_size(input_file);
	unsigned int percent = 0, val_percent = size / 100;
	dictionary *d;
	fpr = file_open(input_file, "r");
	fpw = file_open(output_file, "wb");
	d = init();

	s.len = 0;
	len_c = 1;

	while(fread(c, sizeof(uint8_t), 1, fpr)) {	//read first character from the character string 	
		memcat(memcpy(spc.str, s.str, s.len), s.len, c, len_c);	//spc = s + c
		spc.len = s.len + len_c;
		v = search(d, &spc);
		if(v != MAX) {
			memcpy(s.str, spc.str, s.len = spc.len);
		}
		else {
			v = search(d, &s);
			fwrite(&v, sizeof(uint16_t), 1, fpw);
			addentry(d, &spc);
			memcpy(s.str, c, s.len = len_c);
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
        printf("\rCompressing %s [%d%%] Done...\n", input_file, 100);

	v = search(d, &s);
	fwrite(&v, sizeof(uint16_t), 1, fpw);
	free_dictionary(d);
	fclose(fpr);
	fclose(fpw);
}
/* Searches the dictionary for spc->str 
 * Returns MAX if not found else returns 
 * index of found occurence */
uint16_t search(dictionary *d, string *spc) {
	if(spc->len == 1)
		return spc->str[0];
	int i, max = d->entry_count;
	for(i = max - 1; i > -1; i--) {
		if(d->e[i].len == spc->len) {
			if (!memcmp(d->e[i].word, spc->str, d->e[i].len)) {
				return i;
			}
		}
	}
	return MAX;
}


