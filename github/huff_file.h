info* setfreq(int32_t *size, int argc, char *argv[]);
void writecodes(int argc, char *argv[], wstruct *arrstruct, int32_t size);
int32_t calculatepadding(info *arr, wstruct *arrstruct, int32_t size);
void writefile(char *argv[], info *arr, wstruct *arrstruct, int32_t size);

