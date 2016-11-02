/* A Huffman Tree node */
typedef struct info {
	char ch;
	int32_t freq;
	int32_t code;
}info;
/*A Huffman structure to be written to the header of the compressed file 
 *to read back the code during decompression
 */
typedef struct wstruct {
	char ch;
	char str[32];
}wstruct;

info* setfreq(int32_t *size, int32_t argc, char *argv[]);
void mergesort(info *arr, int32_t l, int32_t r);
void writecodes(int argc, char *argv[], wstruct *arrstruct, int32_t size);
void writefile(char *argv[], info *arr, wstruct *arrstruct, int32_t size);
