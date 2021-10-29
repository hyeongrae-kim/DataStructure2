#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{ //Tree Node 구조체
	char data;
	struct TreeNode *lnode;
	struct TreeNode *rnode;
}TreeNode;

TreeNode* makeNode(TreeNode *l, TreeNode *r, char data){ // TreeNode 생성 함수
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));
	
	tmp->data = data;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

void inorder_print(TreeNode *root){ //중위 순회 출력함수
	if(root){
		inorder_print(root->lnode);
		printf("[%c] ", root->data);
		inorder_print(root->rnode);
	}
}


int main(int argc, char* argv[]){
	
	TreeNode *n3 = makeNode(NULL, NULL, 'b'); //3번째노드
	TreeNode *n2 = makeNode(NULL, NULL, 'a'); //2번째노드
	TreeNode *n1 = makeNode(n2, n3, '+'); //1번째노드

	printf("중위 순회 = "); //중위순회 출력
	inorder_print(n1);
	printf("\n");

	free(n3); //동적할당 해제
	free(n2);
	free(n1);
	return 0;
}

