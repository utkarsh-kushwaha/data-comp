typedef struct queuenode {
	char ch;
	int32_t freq;
	struct queuenode *left, *right;
}queuenode;

typedef struct queue {
	int32_t head, tail;
	int32_t size;
	queuenode **arr;	
}queue;

queue* CREATEqueue(int32_t size);
int32_t qempty(queue *q);
void enqueue(queue *q, queuenode *d);
int32_t qfull(queue *q);
queuenode* dequeue(queue *q);
int32_t qone(queue *q);
queuenode* GEThead(queue *q);
