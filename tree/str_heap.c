#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200

typedef struct{
	char *str;
}element;

typedef struct{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

int compare(char* str, char* root){
	int i=0;
	
	while(1){
		if(str[i] < root[i])
			return 0;
		else if(str[i] > root[i])
			return 1;

		i++;
	}

	return -1;
}

void insert_max_heap(HeapType *h, char* str){
	int i;
	i = ++(h->heap_size);
	
	while((i!=1) && (compare(str, h->heap[i/2].str))){
		h->heap[i].str = h->heap[i/2].str;
		i /= 2;
	}
	h->heap[i].str = str;
}

HeapType* make_heap(char* str_arr[], int count){
	HeapType *h = (HeapType*)malloc(sizeof(HeapType));
	h->heap_size = 0;
	for(int i=0; i<count; i++)
		insert_max_heap(h, str_arr[i]);

	return h;
}

element delete_max_heap(HeapType* h){
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size){
		if((child < h->heap_size) && !(compare(h->heap[child].str, h->heap[child+1].str)))
			child++;

		if(compare(temp.str, h->heap[child].str)) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}

void free_arr(char *str_arr[], int count){
	count = count-1;
	while(count>=0){
		printf("free->(%s)\n", str_arr[count]);
		free(str_arr[count--]);
	}
}

int main(int argc, char* argv){
	char str[100];
	char *str_arr[100];
	int i=0;
	printf("INPUT: ");
	scanf(" %[^\n]s", str);
	
	char *tmp = strtok(str, " ");
	while(tmp){
		str_arr[i] = (char*)malloc(sizeof(tmp));
		strcpy(str_arr[i++], tmp);
		tmp = strtok(NULL, " ");	
	}
	HeapType* h = make_heap(str_arr, i);
	element e1 = delete_max_heap(h);
	printf("%s\n", e1.str);
	element e2 = delete_max_heap(h);
	printf("%s\n", e2.str);
	element e3 = delete_max_heap(h);
	printf("%s\n", e3.str);
	element e4 = delete_max_heap(h);
	printf("%s\n", e4.str);
	free_arr(str_arr, i);

	
	return 0;
}
