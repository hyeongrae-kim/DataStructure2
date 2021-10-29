#include <stdio.h>
#include <stdlib.h>
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b) )
#endif

typedef struct Node{
	struct Node *lnode;
	struct Node *rnode;
	int data;
}Node;

Node* makeNode(int data, Node* l, Node* r){
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->lnode = l;
	tmp->rnode = r;
	tmp->data = data;

	return tmp;
}

int sum_node(Node* root){ //전체 노드 합 계산
	int sum=0;

	if(root){
		sum += root->data;
		return sum+sum_node(root->lnode)+sum_node(root->rnode);
	}
	else
		return 0;
}

int count_node(Node* root){ //노드 개수 계산
	int count=0;

	if(root)
		return (++count) + count_node(root->lnode) + count_node(root->rnode);
	else
		return 0;
}

int count_last_node(Node* root){ //단말 노드개수 계산
	if(root){
		if(root->lnode == NULL && root->rnode == NULL)
			return 1;
		else
			return count_last_node(root->lnode) + count_last_node(root->rnode);
	}
}

int print_height(Node* root){ //최고 레벨 프린트
	int height=0;

	if(root){
		height = 1+max(print_height(root->lnode), print_height(root->rnode));
	}

	return height;
}

int main(int argc, char* argv[]){
	Node* n15 = makeNode(15, NULL, NULL);
	Node* n14 = makeNode(14, NULL, NULL);
	Node* n13 = makeNode(13, NULL, NULL);
	Node* n12 = makeNode(12, NULL, NULL);
	Node* n11 = makeNode(11, NULL, NULL);
	Node* n10 = makeNode(10, NULL, NULL);
	Node* n9 = makeNode(9, NULL, NULL);
	Node* n8 = makeNode(8, NULL, NULL);
	Node* n7 = makeNode(7, n14, n15);
	Node* n6 = makeNode(6, n12, n13);
	Node* n5 = makeNode(5, n10, n11);
	Node* n4 = makeNode(4, n8, n9);
	Node* n3 = makeNode(3, n6, n7);
	Node* n2 = makeNode(2, n4, n5);
	Node* n1 = makeNode(1, n2, n3);

	printf("%d\n", sum_node(n1));
	printf("%d\n", count_node(n1));
	printf("%d\n", count_last_node(n1));
	printf("%d\n", print_height(n1));
	return 0;

}
