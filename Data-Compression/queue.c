/*
 **********************************************************************
 * Copyright (C) 2016  Utkarsh Kushwaha (111503037)

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *********************************************************************** */
#include <stdlib.h>
#include "queue.h"
/*creates queue of given size as max-size of the queue*/
queue* CREATEqueue(uint32_t size) {
	queue *q = (queue*)malloc(sizeof(queue));
	q->head = q->tail = 0;
	q->size = size;
	q->arr = (queuenode**)malloc(size * sizeof(queuenode*));
	return q;
}
uint32_t qfull(queue *q) {
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
uint32_t qempty(queue *q) {
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
uint32_t qone(queue *q) {
	return (q->tail - q->head) == 1 || (q->tail == 1 && q->head == q->size);
}
queuenode* GEThead(queue *q) {
	if(q->head == q->size)
		return q->arr[0];
	else
		return q->arr[q->head];
}
