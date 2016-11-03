#ifndef __ECODE_H
#define __ECODE_H
#include "dictionary.h"
#define MAX 65535

typedef struct string {
	uint8_t str[100000];
	uint32_t len;
}string;

uint16_t search(dictionary *d, string *spc); 
void addentry(dictionary *d, string *spc); 

#endif
