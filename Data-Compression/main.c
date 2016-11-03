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
#include <errno.h>
#include "algorithm.h"

void help(void);

int main(int argc, char *argv[]) {

	if(argc != 2 && argc != 5) {
		errno = EINVAL;
		perror("usage: ./project [OPTION] [METHOD] path(input file) path(output file)");
		fprintf(stderr, "Try `-h, --help` [OPTION] for more help\n");
		exit(errno);
	}

	/*Display help and exit*/
	if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
		help();

	if(!strcmp(argv[1], "-c")) {
		if(!strcasecmp(argv[2], "huffman"))
			huffman(argv[3], argv[4]);
		else if(!strcasecmp(argv[2], "lzw"))
			lzw(argv[3], argv[4]);
		else if(!strcasecmp(argv[2], "rle"))
			rle(argv[3], argv[4]);
		else
			help();
	} else if (!strcmp(argv[1], "-x")) {
		if(!strcasecmp(argv[2], "huffman"))
			dehuffman(argv[3], argv[4]);
		else if(!strcasecmp(argv[2], "lzw"))
			dlzw(argv[3], argv[4]);
		else if(!strcasecmp(argv[2], "rle"))
			drle(argv[3], argv[4]);
		else
			help();
	} else
		help();
	return 0;
}

void help(void) {
	printf("\n\
usage: ./project [OPTION] [METHOD] path(input file) path(output file)\n\n\
	[OPTION]\n\
	\t-c 		Compress the input file\n\
	\t-x 		Decompress the input file\n\
	\t-h,--help 	For help\n\
	\n\
	[METHOD]\n\
	\thuffman 	execute [OPTION] using Huffman\n\
	\tlzw		execute [OPTION] using LZW\n\
	\trle		execute [OPTION] using RLE\n");
	exit(0);
}
