#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define MAX_WORD 200

using namespace std;

FILE *fp; //파일포인터 변수 fp 생성

int WordCount; //파일 내 단어갯수 count 전역변수


typedef struct{
	int count_meanings;
	char eng[MAX_WORD];
	char kor[MAX_WORD];
	char means[4][MAX_WORD];
} element;

typedef struct Node{
	element* word;
	struct Node* lnode;
	struct Node* rnode;	
} Node;

element* make_element(){
	return (element*)malloc(sizeof(element));
}

//영단어 순서를 비교한다.
int cmpWord(char* word, char* root){
	int i=0;

	while(word[i]){
		if(word[i] < root[i])
			return 0; //작을때 거짓 반환
		else if(word[i] > root[i])
			return 1; //크면 참 반환

		i++;
	}
	if(root[i]) 
		return 1; //i번째까지 같은 단어인데 root길이가 더 길 경우 word를 큰 경우로 본다
	else
		return -1; //두 단어가 완전히 같을 때 -1을 반환한다.
}

//root기준으로 가장 우측에있는 maximum node 반환 함수
Node* maxNode(Node* root){
	while(root->rnode)
		root = root->rnode;
	return root;
}

//삭제 할때 tree node만 free 해주는 함수
Node* deleteOnlyNode(Node* root, char* key){
	if(cmpWord(key, root->word->eng)==0)
		root->lnode = deleteOnlyNode(root->lnode, key);
	else if(cmpWord(key, root->word->eng)==1)
		root->rnode = deleteOnlyNode(root->rnode, key);
	else if(cmpWord(key, root->word->eng)==-1){
		if(root->lnode == NULL && root->rnode == NULL){
			free(root);
			root = NULL;
			printf("삭제 완료 되었습니다\n");
			return root;
		}
	}
}

//recursion 활용한 bst노드 삭제 함수
Node* deleteNode(Node* root, char* key){
	if(!root){ 
		printf("삭제할려는 노드가 존재하지 않습니다!!\n");
		return root;
	}
	if(cmpWord(key, root->word->eng)==0)
		root->lnode = deleteNode(root->lnode, key);
	else if(cmpWord(key, root->word->eng)==1)
		root->rnode = deleteNode(root->rnode, key);
	else if(cmpWord(key, root->word->eng)==-1){
		if(root->lnode == NULL){
			Node* tmp = root->rnode;
			free(root->word);
			free(root);
			printf("삭제 완료 되었습니다\n");
			return tmp;
		}
		else if(root->rnode == NULL){
			Node* tmp = root->lnode;
			free(root->word);
			free(root);
			printf("삭제 완료 되었습니다.\n");
			return tmp;
		}
		//자식이 둘 다 있을 경우
		Node* tmp = maxNode(root->lnode);
		printf("%s\n", tmp->word->eng);
		free(root->word); //1
		root->word = tmp->word;
		root->lnode = deleteOnlyNode(root->lnode, tmp->word->eng); //1
	}

	return root;
}

//bst node 생성 함수
Node* makeNode(element* word, Node* l, Node* r){
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->word = word;
	tmp->lnode = l;
	tmp->rnode = r;

	return tmp;
}

//bst에 node push 함수
Node* pushNode(Node* root, element* word){
	if(!root) return makeNode(word, NULL, NULL);
	
	if(cmpWord(word->eng, root->word->eng) == -1){
		printf("같은 단어가 존재합니다!!\n");
	}
	else if(!cmpWord(word->eng, root->word->eng))
		root->lnode = pushNode(root->lnode, word);
	else if(cmpWord(word->eng, root->word->eng))
		root->rnode = pushNode(root->rnode, word);

	return root;
}

//영단어를 검색하여 한국어 뜻을 출력하는 함수
void searchEtoK(Node* root){
	char key[MAX_WORD];
	printf("검색할 영단어 입력: ");
	scanf(" %s", key);

	if(!root){
		printf("단어장이 비어있습니다!!\n");
		return;
	}

	printf("검색과정: ");
	while(root){
		if(cmpWord(key, root->word->eng)==-1){
			printf("%s : %s", root->word->eng, root->word->kor);
			for(int i=1; i < root->word->count_meanings; i++)
				printf(", %s", root->word->means[i]);
			printf("\n");
			return;
		}
		else if(cmpWord(key, root->word->eng)){
			printf("%s - ", root->word->eng);
			root = root->rnode;
		}
		else{
			printf("%s - ", root->word->eng);
			root = root->lnode;
		}
	}

	printf("없음\n");
}

//새로운 단어를 tree에 추가하는 함수
Node* insertWordToTree(Node* root){
	char ch;
	element *tmp = make_element();
	int i=0;

	printf("추가할 단어(영어 한글): ");
	scanf(" %s %s", tmp->eng, tmp->kor);

	tmp->count_meanings = 1;
	while(1){
		printf("다른뜻이 있을경우 추가할 수 있습니다. 추가하시겠습니까? (y/n) ");
		scanf(" %c", &ch);
		if(ch=='y'){
			printf("다른 뜻을 입력하세요: ");
			scanf(" %[^\n]s", tmp->means[tmp->count_meanings]);
			tmp->count_meanings++;
		}
		else if(ch=='n')
			break;
		else 
			printf("입력한 문자를 다시 확인해주세요.\n");
	}
	root = pushNode(root, tmp);

	return root;
}

//tree에 저장된 단어를 삭제하는 함수
Node* deleteWordToTree(Node *root){
	char key[MAX_WORD];
	printf("삭제할 영어단어를 입력하세요: ");
	scanf("%s", key);
	root = deleteNode(root, key);

	return root;
}

//초기에 파일에서 데이터를 트리로 불러오는 함수
Node* FileToTree(char* filename){
	Node* root = NULL;
	element *tmp= NULL;
	char str[MAX_WORD];

	fp = fopen(filename, "r");
	if(fp==NULL){ //파일열 때 에러 발생시
		fprintf(stderr, "사전 파일을 불러올 수 없습니다!!\n"); //에러문구 출력
		return NULL;
	}
	WordCount = 0; //단어장에 저장되어있는 단어 수 세는 전역변수 초기화

	//파일에서 binary search tree node로 옮기는 함수
	while(!feof(fp)){
		if(feof(fp))  break; // 파일의 끝에 도달할 시 break
		tmp = make_element();
		fscanf(fp, "%d %s %s\n", &(tmp->count_meanings), tmp->eng, tmp->kor);

		for(int i=1; i<tmp->count_meanings; i++){ //뜻이 여러가지일 경우 for구문으로 받음
			fscanf(fp, " %[^\n]s\n", tmp->means[i]);
			//strcpy(tmp->means[i], str);
		}
		if(tmp->count_meanings == 0){
			free(tmp);
		 	break;
		}

		WordCount++; //단어수 카운트하는 전역변수 +1
		root = pushNode(root, tmp); //bst에 push
	}
	fclose(fp); //파일 종료

	return root; //bst root 반환
}

//프로그램 종료 시 bst에서 파일로 단어를 저장하는 함수
void TreeToFile(Node* root, char* filename){
	fp = fopen(filename, "w");
	if(fp==NULL){ //파일열 떄 에러 발생시
		fprintf(stderr, "사전 파일을 불러올 수 없습니다!!\n"); //에러문구 출력
		return;
	}
	
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		root = q.front();
		q.pop();
		fprintf(fp, "%d %s %s\n", root->word->count_meanings, root->word->eng, root->word->kor);
		for(int i=1; i < root->word->count_meanings; i++){
			fprintf(fp, "%s\n", root->word->means[i]);
		}
		
		if(root->lnode)
			q.push(root->lnode);
		if(root->rnode)
			q.push(root->rnode);
	}
	fclose(fp);
}

void print_menu(){
	printf("**** 메뉴 ****\n");
	printf("1. 영->한 검색\n");
	printf("2. 한->영 검색\n"); //추가 점수 내용
	printf("3. 단어 추가\n");
	printf("4. 단어 삭제\n");
	printf("5. 성능 평가\n"); //점수없는 첼린지
	printf("6. 종료\n");
}

Node* select_menu(Node* root){
	int choice;
	do{
		print_menu();
		printf("입력: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1: 
				searchEtoK(root); 
				break;
			case 2: 
				break;
			case 3: 
				root = insertWordToTree(root); 
				break;
			case 4: 
				root = deleteWordToTree(root);
				break;
			case 5: 
				break;
			case 6: 
				printf("단어장 프로그램을 종료합니다.\n"); 
				return root;
			
			default: printf("번호를 다시한번 확인해 주세요.\n");
		}
	}while(choice!=6);

	return root;
}

//트리 및 element 동적할당 말소 함수
void eraseTree(Node* root){
	if(root){
		eraseTree(root->lnode);
		eraseTree(root->rnode);
		free(root->word);
		free(root);
	}
}

int main(int argc, char* argv[]){
	char* filename = argv[1];
	printf("%s 파일 로드중...\n", filename);
	Node* root = FileToTree(filename);
	printf("총 %d개 데이터 로드 완료.\n\n", WordCount);
	
	root = select_menu(root);

	TreeToFile(root, filename);
	eraseTree(root);
	root = NULL;

	return 0;
}
