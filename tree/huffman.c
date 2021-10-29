#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode *lnode;
	struct TreeNode *rnode;
} TreeNode;

typedef struct{
	TreeNode* ptree;
	char ch;
	int key;
} element;

typedef struct{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create(){
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h){
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item){
	int i;
	i = ++(h->heap_size);

	while((i!=1) && (item.key < h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /=2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h){
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	while(child <= h->heap_size){
		if((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
			child++;

		if(temp.key < h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}

TreeNode* make_tree(TreeNode* l, TreeNode* r){
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->lnode = l;
	node->rnode = r;

	return node;
}

void destroy_tree(TreeNode* root){
	if(!root) return;
	destroy_tree(root->lnode);
	destroy_tree(root->rnode);
	free(root);
}

int is_leaf(TreeNode* root){
	return !(root->lnode) && !(root->rnode);
}

void print_array(int codes[], int n){
	for(int i=0; i<n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top){
	//1을 저장하고 순환호출 한다.
	if(root->lnode){
		codes[top] = 1;
		print_codes(root->lnode, codes, top+1);
	}

	//0을 저장하고 순환호출 한다.
	if(root->rnode){
		codes[top] = 0;
		print_codes(root->rnode, codes, top+1);
	}

	//단말노드이면 코드를 출력한다.
	if(is_leaf(root)){
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

void huffman_tree(int freq[], char ch_list[], int n){
	int i;
	TreeNode *node, *x;
	HeapType *heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for(i = 0; i<n; i++){
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for(i=1; i<n; i++){
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key+e2.key;
		e.ptree = x;
		printf("%d+%d->%d\n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap);
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);
}

int main(int argc, char* argv[]){
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	huffman_tree(freq, ch_list, 5);

	return 0;
}
