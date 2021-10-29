#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct Node{ //트리 노드 구조체
	Node* lnode;
	Node* rnode;
	int data;
}Node;

Node* makeNode(int data, Node* l, Node* r){ //트리의 새로운 노드 생성
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = data;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

void print_menu(){ //메뉴 프린트
	printf("1. 입력\n");
	printf("2. 탐색\n");
	printf("3. Level Order\n");
	printf("4. 종료\n");
}

//트리 레벨순회 프린트 함수
void print_levelorder(Node* root){
	queue<Node*> q; //임시 큐 생성
	Node* node = NULL;

	if(root==NULL)
		printf("error!\n");

	q.push(root); //큐에 루트포인터변수 푸쉬
	while(!q.empty()){ //큐가 빌때까지 반복
		node = q.front(); //임시노드에 큐 프론트값 pop
		q.pop();
		printf("%d ", node->data); //임시노드 출력
		if(node->lnode) //큐에서 pop한노드의 lnode 푸쉬
			q.push(node->lnode);
		if(node->rnode) //큐에서 pop한노드의 rnode 푸쉬
			q.push(node->rnode);
	}
}

//노드 탐색함수
void search_bst(Node* root){
	int key=0; //탐색 할 값 저장 변수
	int count = 0; //탐색 카운트 변수

	printf("탐색할 노드?: ");
	scanf("%d", &key);
	
	if(!root){ //트리가 비어있을시 프린트
		printf("트리에 노드가 존재하지 않습니다!!\n");
		return;
	}

	while(root){ //노드 탐색 반복문
		if(key < root->data){ //찾는값이 노드의 데이터값보다 작을때
			count++;
			root = root->lnode; //왼쪽노드로 이동
		}
		else if(key > root->data){ //찾는값이 노드의 데이터값보다 클때
			count++;
			root = root->rnode; //오른쪽노드로 이동
		}
		else{
			count++;
			printf("%d은 %d회 탐색으로 발견\n", root->data, count); //결과물 프린트
			break;
		}
	}

	if(!root){ //끝까지 탐색했는데 값이 존재하지않아 root가 NULL을 가리킬 시 출력
		printf("%d은 존재하지 않습니다.\n", key);
	}
}


//이진탐색트리 입력 함수
Node* push_bst(Node* node, int val){
	if(!node) return makeNode(val, NULL, NULL); //입력할 위치 도달
 	
	if(val < node->data) //입력할려는 값이 현재노드의 data보다 작을때
		node->lnode = push_bst(node->lnode, val); //lnode에 푸쉬
	else if(val > node->data) //입력할려는 값이 현재노드의 data보다 클때
		node->rnode = push_bst(node->rnode, val); //rnode에 푸쉬

	return node;	
}

//이진탐색트리 데이터를 사용자로부터 입력 받는 함수
Node* get_bst_val(Node* root){
	int val=0;

	while(1){ //-1입력받기 전까지 입력받음
		printf("입력 (종료는 -1): ");
		scanf("%d", &val);
		if(val==-1)
			break;
		root = push_bst(root, val);
	}

	return root;
}


//트리 말소 함수, 레벨순회로 트리 말소
void delete_tree(Node* root){
	queue<Node*> q; //임시 큐 생성
	int count=0; //말소하는 노드 수 카운트 변수

	q.push(root); //큐를 활용한 레벨순회
	while(!q.empty()){
		root = q.front();
		q.pop();
		if(root->lnode)
			q.push(root->lnode);
		if(root->rnode)
			q.push(root->rnode);

		printf("%d 노드 free됨.\n", root->data);
		free(root); //노드 해제
		++count;
	}

	printf("총 %d개의 노드가 free됨.\n", count);
}

void select_menu(){ //메뉴 선택 함수
	Node* root = NULL; //초기 트리노드
	int n = 0; //메뉴 선택 변수

	while(1){
		print_menu();
		printf("번호를 넣으세요: ");
		scanf("%d", &n);
		switch(n){
			case 1: //이진탐색트리 입력
				root = get_bst_val(root);
				printf("[Level] ");
				print_levelorder(root);
				printf("\n");
				break;
			
			case 2: //노드탐색
				search_bst(root);
				break;

			case 3: //트리 프린트
				if(!root){
					printf("트리에 노드가 존재하지 않습니다!!\n");
					break;
				}
				printf("[Level] ");
				print_levelorder(root);
				printf("\n");
				break;

			case 4: //종료
				delete_tree(root);
				root = NULL; //남아있는 데이터를 확실하게 지워줌
				printf("[종료]\n");
				return;
		}
	}
}

int main(int argc, char* argv[]){
	select_menu();
	return 0;
}
