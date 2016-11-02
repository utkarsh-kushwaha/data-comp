#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct data {
	char word[128];
	char code[13];
}data;
int revert(data *arr, char *code) {
	int num = 0, v = 1;
	int j = 0;
	while(j < 12) {
		if(code[12 - j - 1] == '1')
			num += v;
		v *= 2;
		j++;
	}
	return num;
}
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
char* search(data *arr, char *code, int MAX) {
	int i = revert(arr, code);
	if(i < MAX)
		return arr[i].word;
	else
		return NULL;
}
void insert(data *arr, char *tmp, int MAX) {
        setcode(MAX, arr[MAX].code);
        strcpy(arr[MAX].word, tmp);
}
int main(int argc, char *argv[]) {
	FILE *fr, *fw;
	char old_code[13], *p;
	char string[256], new_code[128], ch[2];
	int MAX = 256;
	data arr[4096];
	if(argc < 3) {
		errno = EINVAL;
		perror("Usage: ./dlzw filename");
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
	fread(old_code, 12, sizeof(char), fr);
	old_code[12] = '\0';
	p = search(arr, old_code, MAX);
	fwrite(p, 1, sizeof(char), fw);
	while(fread(new_code, 12, sizeof(char), fr)) {
		new_code[12] = '\0';
		p = search(arr, new_code, MAX);
		if(p)
			strcpy(string, p);
		else {
			p = search(arr, old_code, MAX++);
			strcpy(string, p);
			strcat(string, ch);
		}
		fwrite(string, strlen(string), sizeof(char), fw);
		ch[0] = string[0];
		ch[1] = '\0';
		strcpy(old_code, search(arr, old_code, MAX));
		strcat(old_code, ch);
		insert(arr, old_code, MAX);
		MAX++;
		strcpy(old_code, new_code);
	}
	fclose(fr);
	fclose(fw);
	return 0;
}
