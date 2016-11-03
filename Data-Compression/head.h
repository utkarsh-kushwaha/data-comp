/* A Huffman Tree node */
typedef struct info {
	uint8_t ch;
	uint32_t freq;
	uint32_t code;
}info;
/*A Huffman structure to be written to the header of the compressed file 
 *to read back the code during decompression
 */
typedef struct wstruct {
	uint8_t ch;
	uint8_t str[32];
	uint16_t len;
}wstruct;

void mergesort(info *arr, uint32_t l, uint32_t r);

info* setfreq(uint32_t *size, char *input_file);

void writecodes(char *output_file, wstruct *arrstruct, uint32_t size);

void writefile(char *input_file, char *output_file, info *arr, wstruct *arrstruct, uint32_t size);                                                              
