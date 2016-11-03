info* setfreq(uint32_t *size, char *input_file);

void writecodes(char *output_file, wstruct *arrstruct, uint32_t size);

uint32_t calculatepadding(info *arr, wstruct *arrstruct, uint32_t size);

void writefile(char *input_file, char *output_file, info *arr, wstruct *arrstruct, uint32_t size);
