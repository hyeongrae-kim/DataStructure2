#include <stdio.h>
#include <stdlib.h>

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

Node* bst_search(Node* root, int key){ //이진탐색트리 탐색 반복 알고리즘
	while(root){
		if(root->data == key) return root;
		else if (root->data < key)
			root = root->rnode;
		else
			root = root->lnode;
	}
	return NULL; //탐색 실패시 null 반환
}

Node* bst_search_r(Node* root, int key){ //이진탐색트리 탐색 순회 알고리즘
	if(!root) return NULL;

	if(root->data == key) return root;
	else if(root->data > key)
		root = bst_search_r(root->lnode, key);
	else
		root = bst_search_r(root->rnode, key);
}

void bst_push(int val, Node* root){ //이진탐색트리 삽입 반복 알고리즘
	Node *tmp = root;

	while(1){
		if(val==tmp->data){
			printf("이미 같은 값이 존재합니다!!\n");
			break;
		}
		else if(val > tmp->data){
			if(tmp->rnode == NULL){
				tmp->rnode = makeNode(val, NULL, NULL);
				break;
			}
			else
				tmp = tmp->rnode;
		}
		else{
			if(tmp->lnode == NULL){
				tmp->lnode = makeNode(val, NULL, NULL);
				break;
			}
			else
				tmp = tmp->lnode;
		}
	}
}

Node* bst_push_r(int val, Node *root){  //이진탐색트리 삽입 순회 알고리즘
	if(!root)
		return makeNode(val, NULL, NULL);

	if(val>root->data)
		root->rnode = bst_push_r(val, root->rnode);
	else if(val<root->data)
		root->lnode = bst_push_r(val, root->lnode);
	else{
		printf("같은값이 이미 존재합니다!!\n");
		return root;
	}

	return root;
}

Node* max_node(Node* root){
	while(root->rnode)
		root = root->rnode;

	return root;
}

Node* delete_node(Node* root, int val){ //노드 삭제 함수
	if(root==NULL){
		printf("삭제할려는 노드가 존재하지 않습니다!!\n");
		return root;
	}

	if(val<root->data)
		root->lnode = delete_node(root->lnode, val);
	else if(val>root->data)
		root->rnode = delete_node(root->rnode, val);
	else{
		if(root->lnode == NULL){ //자식이 하나만있거나, 둘다 없는경우
			Node* tmp = root->rnode;
			free(root);
			return tmp;
		}
		else if(root->rnode == NULL){
			Node* tmp = root->lnode;
			free(root);
			return tmp;
		}
		//자식이 둘 다 있을경우
		Node *tmp = max_node(root->lnode);
		root->data = tmp->data;
		root->lnode = delete_node(root->lnode, tmp->data);
	}
	return root;
}

//전위순회
void preorder(Node *root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->lnode);
		preorder(root->rnode);
	}
}

int main(int argc, char* argv[]){
	//50 30 15 20 47 69 BST 생성
	
	Node *root = makeNode(50, NULL, NULL);
	bst_push(30, root);
	bst_push(15, root);
	bst_push(20, root);
	bst_push(47, root);
	bst_push(69, root);
	bst_push(32, root);
	preorder(root);
	printf("\n");
	root = delete_node(root, 32);
	preorder(root);
	printf("\n");
}
