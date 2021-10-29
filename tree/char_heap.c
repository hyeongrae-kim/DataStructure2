#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 200
typedef struct{
	char key;
}element;

typedef struct{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void insert_min_heap(HeapType* h, element item){
	int i;
	i = ++(h->heap_size);

	while((i!=1) && (item.key < h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h){
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size){
		if((child < h->heap_size) && (h->heap[child].key) > h->heap[child+1].key)
			child++;
		if(temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}

void heap_sort(element a[], int n){
		int i;
		HeapType *h;
		h = (HeapType*)malloc(sizeof(HeapType));
		h->heap_size = 0;

		for(i = 0; i<n; i++)
			insert_min_heap(h, a[i]);

		for(i = 0; i<=n-1; i++)
			a[i] = delete_min_heap(h);

		free(h);
}

void make_elem(element tmp[], char *str, int len){
	int count=0;
	for(int i=0; i<len; i++){
		if(str[i] != ' ')
			tmp[count++].key = str[i];
	}
}



int main(int argc, char* argv[]){
	char str[MAX_ELEMENT];
	int count=0;
	int k=0;

	printf("INPUT: ");
	scanf(" %[^\n]s", str);
	element result[strlen(str)];
	make_elem(result, str, strlen(str));
	while(1){
		if(result[k++].key)
			count++;
		else
			break;
	}
	heap_sort(result, count);
	for(int i=0; i<count; i++){
		printf("%c ", result[i].key);
	}
	printf("\n");
	return 0;
}

