#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "queue.h"
#define TREE_HT 256 /*upper limit on height of huffman tree*/
/*creates a new node*/
queuenode* CREATEnewnode(char ch, int32_t freq) {
	queuenode *tmp = (queuenode*)malloc(sizeof(queuenode));
	tmp->left = tmp->right = NULL;
	tmp->ch = ch;
	tmp->freq = freq;
	return tmp;
}

/*gets node of character with minimum frequency from two queues*/
queuenode* GETmin(queue *q1, queue *q2) {
	if(qempty(q1)) {
		if(!qempty(q2))
			return dequeue(q2);
		else 
			return NULL;
	}
	if(qempty(q2)) {
		if(!qempty(q1))
			return dequeue(q1);
		else
			return NULL;
	}
	if(GEThead(q1)->freq < GEThead(q2)->freq)
		return dequeue(q1);
	return dequeue(q2);
}

/*check if the node(argument queuenode) is leaf*/
int32_t isleaf(queuenode *node) {
	return !(node->left) && !(node->right);
}

void printarr(info *arr, int32_t i, int32_t top, wstruct *arrstruct) {
	int32_t k = top;
	arrstruct[i].ch = arr[i].ch;
	while(k) {
		k--;
		sprintf(&arrstruct[i].str[top - 1 - k], "%d", (arr[i].code >> k) & 1);
	}
	arrstruct[i].str[top] = '\0';	
}
queuenode* form_HuffTree(info *arr, int32_t size, wstruct *arrstruct) {
	int32_t i = 0;
	queuenode *left, *right, *internal_node;
	queue *q1 = CREATEqueue(size);
	queue *q2 = CREATEqueue(size);
	/*Initially:
	 *first queue has data in non-decreasing order of frequency
	 *the 2nd queue is empty*/
	for(i = 0; i < size; ++i) {
		if(!qfull(q1))
			enqueue(q1, CREATEnewnode(arr[i].ch, arr[i].freq));
	}
	
	/*run while queues contain more than one node finally first queue will be empty
	  and second queue will contain only one node.*/
	while(!(qempty(q1) && qone(q2))) {
		/*dequeue two nodes with the minimum frequency by examining
		  the frequency at the head of the nodes of both queues*/
		left = GETmin(q1, q2);
		right = GETmin(q1, q2);
		if(!left || !right)
			break;
		/*create a new internal node with frequency equal to the sum
		  of the two node frequencies. Enqueue this node to the 2nd queue.*/
		internal_node = CREATEnewnode('$', left->freq + right->freq);
		internal_node->left = left;
		internal_node->right = right;
		if(!qfull(q2))
			enqueue(q2, internal_node);
	}
	return dequeue(q2);
}

/*Copy the huffman codes from the root of Huffman Tree to arrstruct,
 *which will form header of the compressed file
 */
void STOREcodes(queuenode *root, char prar[], int32_t top, info *arr, wstruct *arrstruct) {
	int32_t i = 0, k = top;
	//assign (0 to the left edge / 1 to the right edge) and recur
	if(root->left) {
		prar[top] = '0';
		STOREcodes(root->left, prar, top + 1, arr, arrstruct);
	}
	if(root->right) {
		prar[top] = '1';
		STOREcodes(root->right, prar, top + 1, arr, arrstruct);
	}
	/*if this is a leaf node, then it contains one of the input
	  characters, print the character and its code from arr[]*/
	if(isleaf(root)) {
		prar[top] = '\0';
		while(arr[i].ch != root->ch)
			i++;
		arr[i].code = 0;
		while(k) {
			k--;
			if(prar[top - 1 - k] == '1')
				arr[i].code |= 1 << k;
		}
		printarr(arr, i, top, arrstruct);
	}
}

/*builds the huffman tree and stores the codes by transversing it
 */
void GENERATEandSTORE(info *arr, int32_t size, wstruct *arrstruct) {
	queuenode *root = form_HuffTree(arr, size, arrstruct);
	/*print huffman codes using the huffman tree built above*/
	char prar[TREE_HT];
	int32_t top = 0;
	STOREcodes(root, prar, top, arr, arrstruct);
}

