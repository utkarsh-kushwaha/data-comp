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
#include <inttypes.h>
#include "head.h"
void merge(info arr[], uint32_t l, uint32_t m, uint32_t r);
/*l->left index
 *r->right index of the array to be sorted
 */
void mergesort(info arr[], uint32_t l, uint32_t r) {
	uint32_t m;
	if(l < r) {
		m = l +  (r - l)/2;
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
/*merges two sub-arrays arr[l,...,m] and arr[m + 1,...,r]*/
void merge(info arr[], uint32_t l, uint32_t m, uint32_t r) {
	uint32_t i, j, k;
	uint32_t n1 = m - l + 1;
	uint32_t n2 = r - m;
	/*create temp arrays*/
	info L[n1], R[n2];
	/*copy data to temp arrays L[] and R[]*/
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for(j = 0; j < n2; j++)
		R[j] = arr[m + j + 1];
	/*merge the temp arrays back into arr[l,...,r]*/
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
