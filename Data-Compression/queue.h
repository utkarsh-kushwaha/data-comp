#include <inttypes.h>
typedef struct queuenode {
	uint8_t ch;
	uint32_t freq;
	struct queuenode *left, *right;
}queuenode;

typedef struct queue {
	uint32_t head, tail;
	uint32_t size;
	queuenode **arr;	
}queue;

queue* CREATEqueue(uint32_t size);
uint32_t qempty(queue *q);
void enqueue(queue *q, queuenode *d);
uint32_t qfull(queue *q);
queuenode* dequeue(queue *q);
uint32_t qone(queue *q);
queuenode* GEThead(queue *q);
