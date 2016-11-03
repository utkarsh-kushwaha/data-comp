void GENERATEandSTORE(info *arr, int32_t size, wstruct *arrstruct);

queuenode* CREATEnewnode(uint8_t ch, int32_t freq);

queuenode* form_HuffTree(info *arr, int32_t size);

queuenode* GETmin(queue *q1, queue *q2);

int32_t isleaf(queuenode *node);

void copyarr(info *arr, int32_t i, int32_t top, wstruct *arrstruct);

void STOREcodes(queuenode *root, uint8_t prar[], int32_t top, info *arr, wstruct *arrstruct);
