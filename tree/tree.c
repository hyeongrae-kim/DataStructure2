#include <stdio.h>
#include <stdlib.h>

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

//node 총 합 구하기
int calc_all_node(TreeNode* root){
	 int l_size, r_size;

	 if(!root) return 0;

	 l_size = calc_all_node(root->lnode);
	 r_size = calc_all_node(root->rnode);

	 return (root->data + l_size + r_size);
}

//node 총 개수 구하기
int calc_count_node(TreeNode* root){
	int count = 0;

	if(root)
		count = 1+calc_count_node(root->lnode) + calc_count_node(root->rnode);

	return count;
}

//node 층 구하기
int calc_level_node(TreeNode* root){
	int level=0;

	while(root){
		if(root)
			level += 1;
		
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
	
	preorder(n1);
	printf("\n");

	postorder(n1);
	printf("\n");

	inorder(n1);
	printf("\n");

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
