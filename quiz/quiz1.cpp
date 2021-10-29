#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct Node{ //트리 노드 구조체
	int data;
	struct Node *lnode;
	struct Node *rnode;
}Node;

Node* new_node(int data, Node *l, Node *r){ //트리의 새로운 노드 생성
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->data = data;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

Node* make_tree(){ //퀴즈 문제에서 나온 트리 구현
	Node *n7 = new_node(7, NULL, NULL);
	Node *n6 = new_node(6, NULL, NULL);
	Node *n5 = new_node(5, NULL, n7);
	Node *n4 = new_node(4, NULL, NULL);
	Node *n3 = new_node(3, n5, n6);
	Node *n2 = new_node(2, n4, NULL);
	Node *root = new_node(1, n2, n3);

	return root;
}

void level_order(Node* root){ //레벨순회 방식의 트리 프린트
	queue<Node*> q; //임시 큐 생성

	printf("[Level order] ");
	q.push(root); //큐에 루트 포인터 변수(첫번째 트리 노드) 푸쉬
	while(!q.empty()){ //큐가 빌때까지 반복
		root = q.front(); //큐의 프론트값 pop
		q.pop();
		printf("%d ", root->data); //데이터 값 출력
		if(root->lnode) //lnode 존재 시 큐에 푸쉬
			q.push(root->lnode);
		if(root->rnode) //rnode 존재 시 큐에 푸쉬
			q.push(root->rnode);
	}
	printf("\n");
}

void print_pre_order(Node* root){ //전위순회 방식의 트리 프린트
	if(root){
		printf("%d ", root->data); //데이터 값 출력
		print_pre_order(root->lnode); //lnode recursion
		print_pre_order(root->rnode); //rnode recursion
	}
}

void pre_order(Node* root){ //preorder 제목 출력 위한 함수
	printf("[Pre order] ");
	print_pre_order(root);
	printf("\n");
}

void print_leaf_nodes(Node* root){ //트리의 말단 노드 출력 함수
	if(root){ //NULL이 아닐 때
		if(root->lnode == NULL && root->rnode == NULL){ //자식 노드가 없을 경우 데이터 출력
			printf("%d ", root->data);
		}
		print_leaf_nodes(root->lnode); //lnode recursion
		print_leaf_nodes(root->rnode); //rnode recursion
	}
}

void find_leaf_nodes(Node* root){ //말단노드 출력 제목 출력위한 함수
	printf("[Leaf nodes] ");
	print_leaf_nodes(root);
	printf("\n");
}

void delete_tree(Node* root){ //전체 트리 삭제, 후위순회 방식으로 해제해준다
	if(root){
		delete_tree(root->lnode);
		delete_tree(root->rnode);
		printf("%d->free\n", root->data);
		free(root);
	}
}

void find_max(Node* root){ //레벨순회 방식으로 max값 노드 출력 함수
	queue<Node*> q; //레벨순회 위한 임시 큐 생성
	int max = 0; //max값 저장할 변수
	Node* n1 = root; //끝나고 메모리 free하기위해 첫번째 노드 기록

	q.push(root); //첫번째 노드 푸쉬
	while(!q.empty()){
		root = q.front(); //큐 pop
		q.pop();
		if(root->lnode) //lnode 존재시 푸쉬
			q.push(root->lnode);
		if(root->rnode) //rnode 존재시 푸쉬
			q.push(root->rnode);
		
		if(root->data > max) //data가 맥스값보다 클 경우
			max = root->data; //max에 데이터값 저장
	}

	printf("[Max] %d\n", max); //맥스 값 출력

	delete_tree(n1); //동적할당 삭제
}

int main(int argc, char* argv[]){
	Node *root = make_tree();	
	level_order(root);
	pre_order(root);
	find_leaf_nodes(root);
	find_max(root);
	return 0;
}
