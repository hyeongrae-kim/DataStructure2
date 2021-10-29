#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct Node{
	Node* lnode;
	Node* rnode;
	int data;
}Node;

Node* makeNode(int data, Node* l, Node* r){
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = data;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

void print_menu(){
	printf("1. 입력\n");
	printf("2. 탐색\n");
	printf("3. Level Order\n");
	printf("4. 종료\n");
}

//트리 레벨순회 프린트 함수
void print_levelorder(Node* root){
	queue<Node*> q;
	Node* node = NULL;

	if(root==NULL)
		printf("error!\n");

	q.push(root);
	while(!q.empty()){
		node = q.front();
		q.pop();
		printf("%d ", node->data);
		if(node->lnode)
			q.push(node->lnode);
		if(node->rnode)
			q.push(node->rnode);
	}
}

void search_bst(Node* root){
	int key=0;
	int count = 0;

	printf("탐색할 노드?: ");
	scanf("%d", &key);
	
	if(!root){
		printf("트리에 노드가 존재하지 않습니다!!\n");
		return;
	}

	while(root){
		if(key < root->data){
			count++;
			root = root->lnode;
		}
		else if(key > root->data){
			count++;
			root = root->rnode;
		}
		else{
			count++;
			printf("%d은 %d회 탐색으로 발견\n", root->data, count);
			break;
		}
	}

	if(!root){
		printf("%d은 존재하지 않습니다.\n", key);
	}
}


//이진탐색트리 입력 함수
Node* push_bst(Node* node, int val){
	if(!node) return makeNode(val, NULL, NULL);
 	
	if(val < node->data)
		node->lnode = push_bst(node->lnode, val);
	else if(val > node->data)
		node->rnode = push_bst(node->rnode, val);

	return node;	
}

//이진탐색트리 데이터를 사용자로부터 입력 받는 함수
Node* get_bst_val(Node* root){
	int val=0;

	while(1){
		printf("입력 (종료는 -1): ");
		scanf("%d", &val);
		if(val==-1)
			break;
		root = push_bst(root, val);
	}

	return root;
}


//트리 말소 함수
void delete_tree(Node** root){
	queue<Node*> q;
	int count=0;

	q.push(*root);
	while(!q.empty()){
		*root = q.front();
		q.pop();
		if((*root)->lnode)
			q.push((*root)->lnode);
		if((*root)->rnode)
			q.push((*root)->rnode);

		printf("%d 노드 free됨.\n", (*root)->data);
		free((*root));
		++count;
	}

	printf("총 %d개의 노드가 free됨.\n", count);
}

void select_menu(){
	Node* root = NULL;
	int n = 0; //메뉴 선택 변수
	
	while(1){
		print_menu();
		printf("번호를 넣으세요: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				root = get_bst_val(root);
				break;
			
			case 2:
				search_bst(root);
				break;

			case 3:
				if(!root){
					printf("트리에 노드가 존재하지 않습니다!!\n");
					break;
				}
				printf("[Level] ");
				print_levelorder(root);
				printf("\n");
				break;

			case 4:
				delete_tree(&root);
				if(root)
					printf("%d\n", root->rnode->data);
				return;
		}
	}
}

int main(int argc, char* argv[]){
	select_menu();
	return 0;
}
