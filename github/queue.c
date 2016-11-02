#include <stdlib.h>
#include "queue.h"
/*creates queue of given size as max-size of the queue*/
queue* CREATEqueue(int32_t size) {
	queue *q = (queue*)malloc(sizeof(queue));
	q->head = q->tail = 0;
	q->size = size;
	q->arr = (queuenode**)malloc(size * sizeof(queuenode*));
	return q;
}
int32_t qfull(queue *q) {
	return q->tail < 0 || (q->tail == q->size && q->head == 0);
}
void enqueue(queue *q, queuenode *d) {
	q->arr[q->tail] = d;
	if(q->tail == q->size)
		q->tail = 0;
	else if(q->head - q->tail == 1)
		q->tail = -(q->tail);
	else
		(q->tail)++;
}
int32_t qempty(queue *q) {
	return q->head == q->tail;
}
queuenode* dequeue(queue *q) {
	if(q->tail < 0) {
		q->tail = -(q->tail);
		(q->tail)++;
	}
	else if(q->head == q->size)
		q->head = 0;
	(q->head)++;
	return q->arr[q->head - 1];
}
int32_t qone(queue *q) {
	return (q->tail - q->head) == 1 || (q->tail == 1 && q->head == q->size);
}
queuenode* GEThead(queue *q) {
	if(q->head == q->size)
		return q->arr[0];
	else
		return q->arr[q->head];
}
