#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "head.h"
#include "queue.h"
#include "hufftree.h"
#include "huff_file.h"
void print_help(void);
//driver program to test above functions
int main(int argc, char *argv[]) {
	int32_t size;
	info *arr;
	wstruct *arrstruct;
	if(argc == 2 && !strcmp(argv[1], "-h")) {
		print_help();
		return 0;
	}
	arr = setfreq(&size, argc, argv);
	arrstruct = (wstruct*)malloc(size * sizeof(wstruct));
	GENERATEandSTORE(arr, size, arrstruct);
	writecodes(argc, argv, arrstruct, size);
	writefile(argv, arr, arrstruct, size);
	return 0;
}
void print_help() {
	printf("To compress file:\n \
			`$ encode filename`\n");
	printf("To decompress file:\n \
			`$ decode filename`\n");	
}
