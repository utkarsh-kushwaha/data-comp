#include <inttypes.h>
#include "head.h"
void merge(info arr[], int32_t l, int32_t m, int32_t r);
/*l->left index
 *r->right index of the array to be sorted
 */
void mergesort(info arr[], int32_t l, int32_t r) {
	int m;
	if(l < r) {
		m = l +  (r - l)/2;
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
/*merges two sub-arrays arr[l,....,m] and arr[m + 1,......,r]*/
void merge(info arr[], int32_t l, int32_t m, int32_t r) {
	int32_t i, j, k;
	int32_t n1 = m - l + 1;
	int32_t n2 = r - m;
	/*create temp arrays*/
	info L[n1], R[n2];
	/*copy data to temp arrays L[] and R[]*/
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for(j = 0; j < n2; j++)
		R[j] = arr[m + j + 1];
	/*merge the temp arrays back into arr[l......r]*/
	i = 0; j = 0;
	k = l; 	      /*initial index of the merged subarray*/
	while(i < n1 && j < n2) {
		if(L[i].freq <= R[j].freq) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	/*copy the remaining elements of L[i] or R[i]
	  if there are any*/
	while(i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while(j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
