#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct data {
	char word[128];
	char code[13];
}data;
void setcode(int i, char *code) {
	int bit;
	int j = 0;
	while(j < 12) {
		bit = (i >> j) & 1;
		if(bit == 1)
			code[12 - j - 1] = '1';
		else
			code[12 - j - 1] = '0';
		j++;
	}
}
void init(data *arr) {
	char str[2];
	char ch = '\0';
	char code[13];
	int i = 0, j, bit;
	while(i < 256) {
		str[0] = ch++;
		str[1] = '\0';
		strcpy(arr[i].word, str);
		setcode(i, arr[i].code);
		i++;
	}
}
int search(data *arr, char *tmp, int MAX) {
	int i = 0;
	while(i < MAX) {
		if(!strcmp(arr[i].word, tmp))
			return i;
		i++;
	}
	return 0;
}
void insert(data *arr, char *tmp, int MAX) {
	setcode(MAX, arr[MAX].code);
	strcpy(arr[MAX].word, tmp);
}
int main(int argc, char *argv[]) {
	char str[128], tmp[128], ch[2];
	int MAX = 256, pos;
	data arr[4096];
	FILE *fr, *fw;
	if(argc != 3) {
		errno = EINVAL;
		perror("Usage: ./lzw <filename>");
		exit(errno);
	} 
	fr = fopen(argv[1], "r"); 
	if(fr == NULL) {
		perror("[!] Can't open");
		exit(errno);
	}
	fw = fopen(argv[2], "w"); 
	if(fw == NULL) {
		perror("[!] Can't open");
		exit(errno);
	}
	init(arr);
	fread(str, 1, sizeof(char), fr);
	str[1] = '\0';
	while(fread(ch, 1, sizeof(char), fr)) {
		ch[1] = '\0';
		strcpy(tmp, str);
		strcat(tmp, ch);
		if((pos = search(arr, tmp, MAX)))
			strcpy(str, tmp);
		else {
			fwrite(arr[search(arr, str, MAX)].code, 12, sizeof(char), fw);
			insert(arr, tmp, MAX);
			MAX++;
			strcpy(str, ch);
		}
	}
	fwrite(arr[search(arr, str, MAX)].code, 12, sizeof(char), fw);
	fclose(fr);
	fclose(fw);
	return 0;
}
