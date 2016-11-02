
void GENERATEandSTORE(info *arr, int32_t size, wstruct *arrstruct);
queuenode* CREATEnewnode(char ch, int32_t freq);
queuenode* form_HuffTree(info *arr, int32_t size, wstruct *arrstruct);
queuenode* GETmin(queue *q1, queue *q2);
int32_t isleaf(queuenode *node);
void printarr(info *arr, int32_t i, int32_t top, wstruct *arrstruct);
void STOREcodes(queuenode *root, char prar[], int32_t top, info *arr, wstruct *arrstruct);

