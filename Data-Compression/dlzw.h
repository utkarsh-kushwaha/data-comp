#ifndef __ECODE_H
#define __ECODE_H
#include "dictionary.h"

typedef struct string {
	uint8_t str[100000];
	uint16_t code;
	uint32_t len;
}string;

void _addentry(dictionary *d, string *new_word);
#endif
