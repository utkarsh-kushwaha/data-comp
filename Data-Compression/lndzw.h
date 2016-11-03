#include "dictionary.h"
void* memcat(void *dest, uint32_t size_dest, void *src, uint32_t size_src);

dictionary* init(void);

FILE* file_open(char *path, char *mode);

void free_dictionary(dictionary *d);

void addentry(dictionary *d, string *spc);
