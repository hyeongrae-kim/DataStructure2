#include <stdio.h> //printf, scanf, 파일입출력 등을 위한 헤더파일 삽입
#include <stdlib.h> //동적할당 해제 위한 헤더파일 삽입
#include <queue> //stl queue를 사용하기위해 삽입
#include <string.h> //한글문자열 비교위한 strcmp 함수 사용위해 헤더파일 삽입
#define MAX_WORD 200 //한 단어 최대길이 200으로 지정

using namespace std; //c++ 코드에서 stl queue만 사용하므로 std::를 각각 지정안하고 using namespace std를 사용 

FILE *fp; //파일포인터 변수 fp 생성
int WordCount; //파일 내 단어갯수 count 전역변수


typedef struct{
	int count_meanings; //단어 뜻 개수
	char eng[MAX_WORD]; //영단어
	char kor[MAX_WORD]; //한글 뜻
	char means[4][MAX_WORD]; //그 외 단어의미, 최대 4개의 뜻 추가 가능
} element; //tree node 내 word element 구조체

typedef struct Node{
	element* word;
	struct Node* lnode;
	struct Node* rnode;	
} Node; //bst tree node

element* make_element(){  //element 동적할당 생성
	return (element*)malloc(sizeof(element));
}

//영단어 순서를 비교하는 함수
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
	if(cmpWord(key, root->word->eng)==0) //key단어가 root위치 단어보다 작을때
		root->lnode = deleteOnlyNode(root->lnode, key);
	else if(cmpWord(key, root->word->eng)==1) //key단어가 root위치 단어보다 클때
		root->rnode = deleteOnlyNode(root->rnode, key);
	else if(cmpWord(key, root->word->eng)==-1){ //key단어가 root위치 단어와 같을때
		if(root->lnode == NULL && root->rnode == NULL){ //이 경우는 자식노드가 없는 경우 뿐
			free(root); //element는 해제안하고 root만 동적할당 해제
			root = NULL; //NULL을 한번 더 주어 확실하게 데이터를 날려준다
			printf("삭제 완료 되었습니다\n");
			return root; //root 반환
		}
	}
}

//recursion 활용한 bst노드 삭제 함수
Node* deleteNode(Node* root, char* key){
	if(!root){ //삭제할 노드가 없을때 경고문구 출력
		printf("삭제할려는 노드가 존재하지 않습니다!!\n");
		return root;
	}
	if(cmpWord(key, root->word->eng)==0) //key단어가 root위치 단어보다 작을때
		root->lnode = deleteNode(root->lnode, key); //lnode 재귀
	else if(cmpWord(key, root->word->eng)==1) //key단어가 root 위치 단어보다 클때
		root->rnode = deleteNode(root->rnode, key); //rnode 재귀
	else if(cmpWord(key, root->word->eng)==-1){ //단어가 같을때
		if(root->lnode == NULL){ //lnode가 비어있으면
			Node* tmp = root->rnode; //rnode 임시노드로 이동
			free(root->word); //root위치 word element 동적할당 해재
			free(root); //root node 동적할당 해재
			root = NULL; //NULL을 주어 확실하게 데이터 제거
			printf("삭제 완료 되었습니다\n");
			return tmp; //rnode가 담긴 tmp를 return함으로써 rnode의 level 한칸 올려줌
		}
		else if(root->rnode == NULL){ //rnode가 비어있으면
			Node* tmp = root->lnode; //임시노드는 lnode를 가리킴
			free(root->word); //word element 동적할당 해재
			free(root); //root node 동적할당 해재
			root = NULL; //NULL을 주어 확실하게 data 제거
			printf("삭제 완료 되었습니다.\n");
			return tmp; //lnode가 담긴 tmp를 return함으로써 lnode의 level 한칸 올려줌
		}
		//자식이 둘 다 있을 경우
		Node* tmp = maxNode(root->lnode); //root보다 작은 lnode들 중 가장 큰 값을 tmp가 가리키게 함
		free(root->word); //root위치 word element 해재
		root->word = tmp->word; //현재위치의 word에 tmp를 줌
		root->lnode = deleteOnlyNode(root->lnode, tmp->word->eng); //tmp가 담긴 원래 위치를 삭제하기 위해 노드만 제거하는 함수 호출
	}

	return root; //삭제 후 root값 반환
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
	if(!root) return makeNode(word, NULL, NULL); //같은단어가 존재하지 않을시
	
	if(cmpWord(word->eng, root->word->eng) == -1){ //같은단어 존재시
		printf("같은 단어가 존재합니다!!\n");
	}
	else if(!cmpWord(word->eng, root->word->eng)) //word element의 영단어가 root위치의 영단어보다 작을시
		root->lnode = pushNode(root->lnode, word); //lnode로 재귀호출
	else if(cmpWord(word->eng, root->word->eng)) //word element의 영단어가 root위치의 영단어보다 클시
		root->rnode = pushNode(root->rnode, word); //rnode로 재귀호출

	return root;
}

//한글 뜻 순서 bst에 node push 함수
Node* pushNode_kor(Node* root2, element* word){
	if(!root2) return makeNode(word, NULL, NULL); //같은단어가 존재하지 않을시
	
	if(strcmp(word->kor, root2->word->kor) == 0){ //같은단어 존재시
		printf("같은 단어가 존재합니다!!\n");
	}
	else if(strcmp(word->kor, root2->word->kor)<0) //word element의 단어가 root위치의 한글뜻보다 작을시
		root2->lnode = pushNode_kor(root2->lnode, word); //lnode로 재귀호출
	else if(strcmp(word->kor, root2->word->kor)>0) //word element의 단어가 root위치의 한글뜻보다 클시
		root2->rnode = pushNode_kor(root2->rnode, word); //rnode로 재귀호출

	return root2;
}

//영단어를 검색하여 한국어 뜻을 출력하는 함수
void searchEtoK(Node* root){
	char key[MAX_WORD];
	printf("검색할 영단어 입력: ");
	scanf(" %s", key); //key 변수에 사용자로부터 검색할 영단어 입력받음

	if(!root){ //단어장 트리가 비었을때 오류문구 출력
		printf("단어장이 비어있습니다!!\n");
		return;
	}

	printf("검색과정: ");
	while(root){ //검색과정 출력하는 반복구문
		if(cmpWord(key, root->word->eng)==-1){ //같은단어 찾았을 때
			printf("%s : %s", root->word->eng, root->word->kor); //해당단어 출력
			for(int i=1; i < root->word->count_meanings; i++) //추가 뜻이 있을때 프린트
				printf(", %s", root->word->means[i]); //추가 뜻을 구분위한 , 출력
			printf("\n"); //개행문자 출력
			return; //함수 종료
		}
		else if(cmpWord(key, root->word->eng)){ //찾을려는 단어가 root위치의 단어보다 클때
			printf("%s - ", root->word->eng); //root위치 단어 출력
			root = root->rnode; //rnode로 이동
		}
		else{ //찾을려는 단어가 root위치의 단어보다 작을때
			printf("%s - ", root->word->eng); //root위치 단어 출력
			root = root->lnode; //lnode로 이동
		}
	}

	printf("없음\n"); //root로 검색을 했는데 null이 나와 단어가 없을 시 없다는 문구 출력
}

//한국어를 검색하여 영어 뜻을 출력하는 함수
void searchKtoE(Node* root2){
	char key[MAX_WORD];
	printf("검색할 단어의 한글 뜻 입력: ");
	scanf(" %s", key); //key 변수에 사용자로부터 검색할 영단어 입력받음

	if(!root2){ //단어장 트리가 비었을때 오류문구 출력
		printf("단어장이 비어있습니다!!\n");
		return;
	}

	printf("검색과정: ");
	while(root2){ //검색과정 출력하는 반복구문
		if(strcmp(key, root2->word->kor)==0){ //같은단어 찾았을 때
			printf("%s", root2->word->kor); //해당단어 출력
			for(int i=1; i < root2->word->count_meanings; i++) //추가 뜻이 있을때 프린트
				printf(", %s", root2->word->means[i]); //추가 뜻을 구분위한 , 출력
			printf(" : %s\n", root2->word->eng); //해당 영어단어 출력
			return; //함수 종료
		}
		else if(strcmp(key, root2->word->kor)>0){ //찾을려는 단어가 root위치의 단어보다 클때
			printf("%s - ", root2->word->kor); //root위치 단어 출력
			root2 = root2->rnode; //rnode로 이동
		}
		else{ //찾을려는 단어가 root위치의 단어보다 작을때
			printf("%s - ", root2->word->kor); //root위치 단어 출력
			root2 = root2->lnode; //lnode로 이동
		}
	}

	printf("없음\n"); //root로 검색을 했는데 null이 나와 단어가 없을 시 없다는 문구 출력
}

//새로운 단어를 tree에 추가하는 함수
Node* insertWordToTree(Node* root, Node** root2){
	char ch; //단어 뜻 추가여부 받을 변수
	element *tmp = make_element(); //element형 tmp변수 동적할당

	printf("추가할 단어(영어 한글): ");
	scanf(" %s %s", tmp->eng, tmp->kor); //추가할 단어 받음

	tmp->count_meanings = 1; //뜻 개수 카운터 변수 1로 초기화
	while(1){ //추가 뜻 받는 반복구문
		printf("다른뜻이 있을경우 추가할 수 있습니다. 추가하시겠습니까? (y/n) ");
		scanf(" %c", &ch);
		if(ch=='y'){
			printf("다른 뜻을 입력하세요: ");
			scanf(" %[^\n]s", tmp->means[tmp->count_meanings]); //tmp 동적할당 구조체에 추가 뜻 저장
			tmp->count_meanings++; //뜻 개수 카운터 변수 +1
		}
		else if(ch=='n') //뜻 추가 중지
			break;
		else 
			printf("입력한 문자를 다시 확인해주세요.\n");
	}
	root = pushNode(root, tmp); //영한 트리에 단어 추가
	(*root2) = pushNode_kor(*root2, tmp); //한영 트리에 단어 추가

	return root;
}

//tree에 저장된 단어를 삭제하는 함수
Node* deleteWordToTree(Node *root){
	char key[MAX_WORD];
	printf("삭제할 영어단어를 입력하세요: ");
	scanf("%s", key); //삭제할 영어단어를 변수 key에 입력받음
	root = deleteNode(root, key); //key와 root를 노드삭제 함수에 매개변수로 전달해 노드 삭제

	return root;
}

//초기에 파일에서 데이터를 트리로 불러오는 함수
Node* FileToTree(char* filename){
	Node* root = NULL;
	element *tmp= NULL;

	fp = fopen(filename, "r"); //파일오픈
	if(fp==NULL){ //파일열 때 에러 발생시
		fprintf(stderr, "사전 파일을 불러올 수 없습니다!!\n"); //에러문구 출력
		return NULL;
	}
	WordCount = 0; //단어장에 저장되어있는 단어 수 세는 전역변수 초기화

	//파일에서 binary search tree node로 옮기는 함수
	while(!feof(fp)){
		if(feof(fp))  break; // 파일의 끝에 도달할 시 break
		tmp = make_element(); //임시 element형 변수 tmp 동적할당
		fscanf(fp, "%d %s %s\n", &(tmp->count_meanings), tmp->eng, tmp->kor); //첫 줄 받아옴

		for(int i=1; i<tmp->count_meanings; i++){ //뜻이 여러가지일 경우 for구문으로 받음
			fscanf(fp, " %[^\n]s\n", tmp->means[i]); //tmp의 means 배열에 추가 뜻 저장
		}
		if(tmp->count_meanings == 0){ //feof오류로 인해 빈 줄을 받아 0을 받아올때 break
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
	fp = fopen(filename, "w"); //파일 덮어쓰기
	if(fp==NULL){ //파일열 떄 에러 발생시
		fprintf(stderr, "사전 파일을 불러올 수 없습니다!!\n"); //에러문구 출력
		return;
	}
	
	queue<Node*> q; //임시 큐 생성
	q.push(root); //큐에 root 푸쉬
	while(!q.empty()){ //레벨순회
		root = q.front(); //root에 queue의 front 저장
		q.pop(); //queue pop
		fprintf(fp, "%d %s %s\n", root->word->count_meanings, root->word->eng, root->word->kor); //root의 word element  내용 파일 저장
		for(int i=1; i < root->word->count_meanings; i++){ //root의 word에서 여러 뜻 존재시 파일 저장
			fprintf(fp, "%s\n", root->word->means[i]);
		}
		
		if(root->lnode) //lnode 존재시
			q.push(root->lnode); //큐에 lnode 푸쉬
		if(root->rnode) //rnode 존재시
			q.push(root->rnode); //큐에 rnode 푸쉬
	}
	fclose(fp); //파일 종료
}

Node* makeKorTree(Node* root){
	if(!root){
		printf("영한사전 트리가 비어있습니다!!\n");
		return NULL;
	}
	Node* root2 = NULL;

	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		root = q.front();
		q.pop();
		root2 = pushNode_kor(root2, root->word);
		if(root->lnode)
			q.push(root->lnode);
		if(root->rnode)
			q.push(root->rnode);
	}
	return root2;
}

//트리 및 element 동적할당 말소 함수
void eraseTree(Node* root){
	if(root){
		eraseTree(root->lnode);
		eraseTree(root->rnode);
		free(root->word);
		root->word = NULL;
		free(root);
		root = NULL;
	}
}

//element 제외한 트리만 말소하는 함수
void eraseOnlyTree(Node* root2){
	if(root2){
		eraseOnlyTree(root2->lnode);
		eraseOnlyTree(root2->rnode);
		free(root2);
		root2 = NULL;
	}
}

void print_menu(){ //메뉴 프린트 함수
	printf("**** 메뉴 ****\n");
	printf("1. 영->한 검색\n");
	printf("2. 한->영 검색\n"); //추가 점수 내용
	printf("3. 단어 추가\n");
	printf("4. 단어 삭제\n");
	printf("5. 성능 평가\n"); //점수없는 첼린지
	printf("6. 종료\n");
}

Node* select_menu(Node* root){ //메뉴 선택 함수
	int choice;
	Node* root2=makeKorTree(root);
	do{
		print_menu();
		printf("입력: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1: //영-한 검색 함수 호출
				searchEtoK(root); 
				break;
			case 2: //한-영 검색 함수(추가점수)
				searchKtoE(root2);
				break;
			case 3:  //단어 추가 함수
				root = insertWordToTree(root, &root2); 
				break;
			case 4: //단어 삭제 함수
				root = deleteWordToTree(root);
				eraseOnlyTree(root2);
				root2 = makeKorTree(root);
				break;
			case 5:  //성능 평가(첼린지)
				break;
			case 6: //프로그램 종료
				printf("단어장 프로그램을 종료합니다.\n"); 
				return root;
			
			default: printf("번호를 다시한번 확인해 주세요.\n");
		}
	}while(choice!=6);
	eraseOnlyTree(root2);
	root2 = NULL;

	return root;
}

int main(int argc, char* argv[]){
	char* filename = argv[1];
	printf("%s 파일 로드중...\n", filename);
	Node* root = FileToTree(filename);
	printf("총 %d개 데이터 로드 완료.\n\n", WordCount);
	root = select_menu(root);

	TreeToFile(root, filename); //프로그램 종료 시 트리 내용을 파일에 덮어씀
	eraseTree(root); //트리 동적할당 완전 삭제
	root = NULL;

	return 0;
}
