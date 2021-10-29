#include <stdio.h>
#include <stdlib.h>

//스택의 노드 정의
typedef struct ListNode{
	int data;
	struct ListNode *prev;
}ListNode;


//리스트 스택이 비었는지 검사
int isEmptyList(ListNode** top){
	if((*top) == NULL){
		printf("STACK IS EMPTY!!\n");
		return 1;
	}
	else return 0;
}

//리스트 스택의 top부분에 원소를 삽입하는 함수
void push(ListNode** top){
	int data;
	printf("INPUT: "); //추가할 데이터를 받음
	scanf("%d", &data);

	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); //새로운 노드 생성

	newNode->data = data; //data추가
	newNode->prev = *top; //이전 리스트스택 지정
	*top = newNode; //top을 새로운 노드로 설정
	
	printf("%d PUHSED!\n", newNode->data);
}

//스택의 top위치에서 원소를 삭제하는 함수
int pop(ListNode** top){
	int popped = (*top)->data; //pop할 데이터 저장

	ListNode* temp = *top; //top을 free해주기 위해서 임시 노드에 저장
	*top = (*top) -> prev; //top위치를 이전 노드로 설정
	free(temp); //top 삭제

	return popped; //pop하는 데이터 리턴
}

//메뉴 UI
void printMenu(){
		printf("1.PUSH\n");
		printf("2.POP\n");
		printf("3.QUIT\n");
		printf("->");
}

//동적할당 free 함수
void deleteAll(ListNode** top){
	ListNode* temp;

	while(*top){
		temp = *top;
		*top = (*top)->prev;
		free(temp);
	}
	
	if(!*top)
		printf("DELETE ALL STACK!!\n");
	else
		printf("MEMORY IS NOT CLEAN!!\n");
}

int main(int argc, char* argv[]){
	int choice, popped;
	
	ListNode *top = NULL; //top 노드 초기화

	while(1){
		printMenu();
		scanf("%d", &choice);

		switch(choice){
			case 1 : //push
				push(&top);
				break;

			case 2 : //pop
				if(isEmptyList(&top)) //비었는지 검사
					break;
				else{
					popped = pop(&top);
					printf("%d POPPED!\n", popped);
					break;
				}

			case 3 : //종료 할 때엔 동적할당 모두 지워주고 종료
				deleteAll(&top);
				return 0;

			default : 
				printf("메뉴를 잘 못 선택하였습니다.");
		}
	}
}

