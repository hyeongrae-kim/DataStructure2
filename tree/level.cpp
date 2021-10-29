#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct TreeNode{
	struct TreeNode *lnode;
	struct TreeNode *rnode;
	int data;
}TreeNode;

TreeNode* makeNode(int data, TreeNode* l, TreeNode* r){
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));
	tmp->data = data;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

//전위순회
void preorder(TreeNode *root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->lnode);
		preorder(root->rnode);
	}
}

//후위순회
void postorder(TreeNode *root){
	if(root != NULL){
		postorder(root->lnode);
		postorder(root->rnode);
		printf("%d ", root->data);
	}
}

//중위순회
void inorder(TreeNode* root){
	if(root != NULL){
		inorder(root->lnode);
		printf("%d ", root->data);
		inorder(root->rnode);
	}
}

//레벨순회
void level_order(TreeNode* root){
	queue<TreeNode*> q;
	if(!root)
		return;
	
	q.push(root);
	while(!q.empty()){
		root = q.front();
		q.pop();
		printf("%d ", root->data);
		if(root->lnode)
			q.push(root->lnode);
		if(root->rnode)
			q.push(root->rnode);
	}
	
}

int main(int argc, char* argv[]){
	
	
	TreeNode* n15 = makeNode(15, NULL, NULL);
	TreeNode* n14 = makeNode(14, NULL, NULL);
	TreeNode* n13 = makeNode(13, NULL, NULL);
	TreeNode* n12 = makeNode(12, NULL, NULL);
	TreeNode* n11 = makeNode(11, NULL, NULL);
	TreeNode* n10 = makeNode(10, NULL, NULL);
	TreeNode* n9 = makeNode(9, NULL, NULL);
	TreeNode* n8 = makeNode(8, NULL, NULL);
	TreeNode* n7 = makeNode(7, n14, n15);
	TreeNode* n6 = makeNode(6, n12, n13);
	TreeNode* n5 = makeNode(5, n10, n11);
	TreeNode* n4 = makeNode(4, n8, n9);
	TreeNode* n3 = makeNode(3, n6, n7);
	TreeNode* n2 = makeNode(2, n4, n5);
	TreeNode* n1 = makeNode(1, n2, n3);

	level_order(n1);


	free(n15);
	free(n14);
	free(n13);
	free(n12);
	free(n11);
	free(n10);
	free(n9);
	free(n8);
	free(n7);
	free(n6);
	free(n5);
	free(n4);
	free(n3);
	free(n2);
	free(n1);

	return 0;
}
