#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 200

//힙 내의 데이터 구조체
typedef struct{
	char key; //알파벳 저장 변수
	int count; //알파벳이 문자열에 몇개있는지 count한 변수
}element;

//heap type 구조체 선언
typedef struct{
	element heap[MAX_ELEMENT]; //element변수 배열 생성
	int heap_size; //heapsize
}HeapType;

//heap element-key 삽입 함수
void insert_max_heap(HeapType *h, element item){
	int i;
	i = ++(h->heap_size); //i변수에 heapsize+1

	while((i!=1) && (item.key > h->heap[i/2].key)){ //삽입하려는 item.key가 말단노드의 부모노드보다 작아질때까지 반복
		h->heap[i] = h->heap[i/2]; //부모노드와 말단노드 내용 swap
		i/=2; //부모노드로 거슬러 올라감
	}

	h->heap[i] = item; //i번째 노드에 item 삽입
}

//heap element-key 삭제 함수
element delete_max_heap(HeapType *h){
	int parent, child;
	element item, temp;

	item = h->heap[1]; //첫번째 노드로 초기화
	temp = h->heap[(h->heap_size)--]; //마지막 노드로 초기화
	parent = 1; 
	child = 2;

	while(child <= h->heap_size){
		if((child < h->heap_size) && (h->heap[child].key) < h->heap[child+1].key) //child위치의 key가 형제보다 작을때
			child++; //child+1

		if(temp.key >= h->heap[child].key) break; //이동하는 temp노드가 child노드보다 커지면 break

		h->heap[parent] = h->heap[child]; //parent child swap
		parent = child; //자식노드로 거슬러 내려감
		child *= 2;
	}
	h->heap[parent] = temp; //parent위치에 temp삽입
	return item; //삭제하려는 첫번째 노드 반환
}

//heap element-key 정렬 함수
void heap_sort(element a[], int end, int start){
	int i;
	HeapType *h = (HeapType*)malloc(sizeof(HeapType)); //임시 힙 h 동적할당
	h->heap_size = 0; //heapsize 0 초기화

	for(i=start; i<end; i++){ //max heap으로 h에 a배열 insert
		insert_max_heap(h, a[i]);
	}
	for(i = (end-1); i>=start; i--){ //힙을 삭제하면서 배열에 반환되는 내용을 배열의 뒤에서부터 넣어줌
		a[i] = delete_max_heap(h);
	}
	free(h); //힙 해제
}

//heap element-count 삽입 함수
void insert_max_heap_count(HeapType *h, element item){
	int i;
	i = ++(h->heap_size); //i변수에 heapsize +1추가

	while((i!=1) && (item.count >= h->heap[i/2].count)){ //삽입하려는 item.count가 말단노드의 부모노드보다 작아질때까지 반복
			h->heap[i] = h->heap[i/2]; //부모노드와 말단노드 swap
			i/=2; //부모노드로 거슬러 올라감
	}
	h->heap[i] = item; //i번째 노드에 item 삽입
}

//heap element-count 삭제 함수
element delete_max_heap_count(HeapType *h){
	int parent, child;
	element item, temp;

	item = h->heap[1]; //첫번째 노드로 초기화
	temp = h->heap[(h->heap_size)--]; //마지막 노드로 초기화
	parent = 1;
	child = 2;

	while(child <= h->heap_size){
		if((child < h->heap_size) && (h->heap[child].count) < h->heap[child+1].count) //child위치의 count가 그의 형제보다 작을때
			child++; //child + 1

		if(temp.count >= h->heap[child].count) break; //이동하는 temp노드가 child노드보다 커질때 break

		h->heap[parent] = h->heap[child]; //parent child swap
		parent = child; //부모노드에서 자식노드로 거슬러 내려감
		child *= 2;
	}
	h->heap[parent] = temp; //parent위치에 temp 삽입
	return item;
}

//heap element-count 정렬 함수
void heap_sort_count(element a[], int n){
	int i;
	int k=0;
	HeapType *h = (HeapType*)malloc(sizeof(HeapType)); //임시 힙 h 동적할당
	h->heap_size = 0; //heapsize 0 초기화

	for(i=0; i<n; i++){
		insert_max_heap_count(h, a[i]); //max heap으로 h에 배열 a 삽입
	}
	for(i = (n-1); i>=0; i--){
		a[i] = delete_max_heap_count(h); //힙을 삭제하면서 반환되는 내용을 a배열에 넣는데 뒤에서부터 삽입
	}
	free(h); //동적할당 힙 해제

	//count는 data가 같은 노드가 생길 수 있으므로, 아래의 반복구문으로 같을경우 알파벳순으로 재정렬 한다.
	for(i=0; i<n; i++){
		if(a[i].count==a[i+1].count){ //i부터 k번째까지 count가 같을때
			k=i;
			while(a[k].count==a[k+1].count && k+1<n)
				++k;
			heap_sort(a, k+1, i); //alphabet순으로 i부터 k번째까지 배열을 재정렬 한다
			i=k;
		}
		else //count가 같지 않으면 pass
			continue;
	}
}

//element배열 내에 a 변수가 있는지 검사. 
int check_elem(element tmp[], char a, int count){
	for(int i=0; i<count; i++){
		if(tmp[i].key == a)
			return i; //변수 있을 시 인덱스 반환
	}
	return -1; //변수 없을 시 -1 반환
}

//str내용을 문자와 갯수로 정리하여 element 배열에 넣는다.
void make_element(element single_char[], char str[], int count){
	int k=0; //check_elem함수 반환값 저장 할 변수
	int elem_count=0; //반복 구문에서 element array count 변수

	//str크기만큼 반복함
	for(int i=0; i<strlen(str); i++){
		k = check_elem(single_char, str[i], elem_count); //문자열 i번째 문자가 single_char배열에 있는지 검사
		if(k!=-1) //이미 배열에 문자가 있을시
			single_char[k].count++; //해당 인덱스에 카운트만 +1
		else{ //배열에 문자가 없을 시
			single_char[elem_count].key = str[i]; //single_char배열의 elem_count번째에 문자 저장
			single_char[elem_count].count = 1; //카운트는 1로 초기화
			elem_count++; //element array count + 1
		}
	}
}

//입력자로 부터 받은 str안에 문자종류 수를 count하기 위해 중복된 문자를 검사해주는 함수
int check_same_char(char str[], int i){
	for(int k=0; k<i; k++){
		if(str[k] == str[i]) //이미 문자가 i-1번째 str안에 있을경우
			return 0; //거짓 반환
	}
	return 1; //문자가 i-1번째 str 까지 없을 경우 참 반환
}

void print_sort_by_alphabet(element single_char[], int count){
	int space = 0, period = 0;

	heap_sort(single_char, count, 0); //알파벳 순으로 element 정렬
		
	for(int i=0; i<count; i++){ 
		if(single_char[i].key == ' '){ //element 배열 안에 공백이 있을경우 space변수에 인덱스 저장
			space = i;
			continue;
		}
		else if(single_char[i].key == '.'){ //element 배열 안에 점이 있을 경우 period변수에 인덱스 저장
			period = i;
			continue;
		}
		printf("%c(%d) / ", single_char[i].key, single_char[i].count); //알파벳 순으로 정렬된 element print
	}
	printf("PERIOD(%d) / ", single_char[period].count); //period 갯수 print
	printf("SPACE(%d)\n", single_char[space].count); //공백 갯수 print
}

void print_sort_by_count(element single_char[], int count){
	heap_sort_count(single_char, count); //count순대로 element 정렬

	printf("SORTED : ");
	for(int i=0; i<count; i++){
		if(single_char[i].key == ' ') //공백일 경우 print
			printf("S(%d)", single_char[i].count);
		else if(single_char[i].key == '.') //점일 경우 print
			printf("P(%d)", single_char[i].count);
		else //문자일 경우 print
			printf("%c(%d)", single_char[i].key, single_char[i].count);

		if(i==count-1) //마지막 node프린트후 개행
			printf("\n");
		else //마지막 노드가 아닐 시엔 ", " print
			printf(", ");
	}
}

int main(int argc, char* argv[]){
	int count = 0;
	char str[MAX_ELEMENT];

	printf("Input String: ");
	scanf(" %[^\n]s", str); //str변수에 사용자로부터 문자열 받음
	
	//count 변수 안에 str내에 문자가 몇개의 종류가 있는지 세서 넣는다.
	for(int i=0; i<strlen(str); i++){
		if(check_same_char(str, i)) //아직 안 나온 문자 일때
			count++; //count 변수 + 1
	}

	element single_char[count]; //count 크기만큼의 element형 single_char 배열 선언
	make_element(single_char, str, count); //single_char 배열에 str내용을 정리하여 삽입하는 함수

	print_sort_by_alphabet(single_char, count); //alphabet 순 정렬 프린트
	print_sort_by_count(single_char, count); //count 순 정렬 프린트

	return 0;
}
