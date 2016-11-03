#ifndef __DICTONARY_H
#define __DICTONARY_H
typedef struct entry {
	uint8_t *word;
	uint32_t len;
}entry;
typedef struct dictionary {
	entry *e;
	uint32_t entry_count;	//no of entries in the dictornary
	uint32_t max_limit;
}dictionary;
#endif
