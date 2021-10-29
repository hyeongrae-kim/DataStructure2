#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//트리에 data push하는 함수
void push_data(int *tree, int size){
	int pos, data;

	printf("트리 데이터 입력을 시작합니다.\n");

	while(1){
		printf("pos, data = ? (enter 0 0 to finish)  ");
		scanf("%d %d", &pos, &data); //pos위치에 data입력받음
		
		if(pos == 0 && data == 0)
			break;
		else if(pos <= 0 || pos >= size)
			printf("pos값이 범위를 벗어났습니다.(range: 1-%d)\n", size-1);
		else{
			tree[pos] = data;
		}
	}
	
	printf("트리 데이터 입력이 완료되었습니다.\n");
}

//거듭제곱 함수
int pow_two(int num){ 
	int result = 1;
	for(int i=0; i<num; i++)
		result *= 2;

	return result; //2의 num승을 반환
}

//int node를 char 배열로 바꾸는 함수
char* translate_node(int node){
	char *node_c = (char*)malloc(sizeof(char)*3); //배열 동적할당

	for(int i=0; i<3; i++)
		node_c[i] = ' '; //빈칸으로 초기화

	if(node == 0) //노드가 빈칸일떄
		node_c[1] = '-';
	else if(node>0 && node<10) //노드가 한자리수 일때
		node_c[1] = node+'0';
	else if(node>=10 && node<100){ //노드가 두자리수 일때
		node_c[0] = node/10 + '0';
		node_c[2] = node%10 + '0';
	}
	else if(node>=100 && node<1000){ //노드가 세자리수 일때
		node_c[0] = node/100 + '0';
		node_c[1] = (node%100)/10 + '0';
		node_c[2] = (node%100)%10 + '0';
	}

	return node_c;//node_c 배열 반환
}

//2차원 배열에 트리구조 모양 저장
void make_tree(int height, int size, char (*graph)[size*3], int* tree){
	int tree_i = 1; //tree배열에서 index를 움직이기 위한 변수
	int graph_i=0; //tree를 그리기위한 graph배열에 저장할 때 정렬을 위해 특정한 공식으로 index를 움직이는 변수
	int tmp = 0;

	char *node_c = NULL; //int node값을 char형 3칸 배열로 저장할 포인터변수

	for(int i=0; i<height; i++){ //세로 축 반복
		if(i==0){ //반복구문 첫번째 사이클, tree의 마지막level의 node들을 graph배열에 저장
			for(int j=0; j<size*3; j=j+3){ //node, 빈칸을 하나당 세칸씩 배분을 하여 반복구문을 최대 size의 3배로 잡는다.
				if(j%3 == 0){
					node_c = translate_node(tree[size/2+tree_i++]); //node를 char[3]크기의 배열로 변환. 마지막 level을 가져오므로 tree에서 size/2 index부터 1씩 더해 가져온다.
					for(int w = 0; w<3; w++){
						graph[height-1][j] = node_c[w]; //tree를 그리기위한 이차원 배열의 마지막 행에 node를 저장
						j++;
					}
					free(node_c); //char[3]크기의 node를 임시저장하는 동적 배열 해제
					node_c = NULL; 
				}
			}
		}
		else{ //반복구문 두번째 부터의 사이클, tree의 마지막-1 level부터 첫번째 level까지 node들을 graph배열에 저장
			//graph에 저장 할 때 정렬을 위해 첫번째는 2의i승-1칸을 띄우고, 그 다음부터는 2의i+1승-1칸을 띄우는데, 제각기 다른 자릿수의 정렬을 위해 한 노드, 가지당 3칸의 배열을
			//부여 하였으므로 곱하기 3을 해준다.
			tree_i = 0;
			for(graph_i = 3*(pow_two(i)-1); graph_i<size*3; graph_i = graph_i+((pow_two(i+1)-1)*3)){
				node_c = translate_node(tree[pow_two(height-1-i)+tree_i++]); //node를 char[3]크기의 배열로 변환, tree는 2의height-1-i승 부터 접근하면 원하는 level의 node를 가져올 수 있다.
				for(int w=0; w<3; w++)
					graph[height-1-i][graph_i++] = node_c[w]; //tree를 그리기 위한 2차원 배열에 node를 저장, 하단의 level부터 접근하므로 height-1-i행에 넣어준다
				free(node_c); //char[3]크기의 node를 임시저장하는 동적 배열 해제
				node_c = NULL;
			}
		}
	}
}

//2차원 배열에 branch 저장
void make_branch(int height, int size, char(*branch)[size*3], char(*graph)[size*3] ){
	int direction=0; // '/', '\' 방향 구분하기 위한 변수

	//branch 배열 ' '공백으로 초기화
	for(int i=0; i<height; i++){
		for(int k=0; k<size*3; k++){
			branch[i][k] = ' ';
		}
	}

	//노드 위치에 맞게 branch저장. 비어있는칸도 branch는 그려준다.
	for(int i=0; i<height; i++){
		for(int k=0; k<size*3; k++){
			if(graph[i][k]!=' ' && i>0){ //그래프에 빈칸이 아닌 변수가 존재할 때
				if(graph[i][k+1]!=' ' && graph[i][k+2] != ' '){ //3자리수 일때
					if(direction%2==0){ //왼쪽노드일때
						branch[i][++k] = '/'; //branch /방향 저장
						k+=2;
					}
					else{ //오른쪽노드일때
						branch[i][++k] = '\\'; //branch \방향 저장
						k+=2;
					}
					++direction;
				}
				else if(graph[i][k+2]>= 0+'0' && graph[i][k+2] <= 9+'0'){ //2자리수 일떄
					if(direction%2==0){ //왼쪽노드 일때
						branch[i][++k] = '/';  //branch /방향 저장
						k+=2;
					}
					else{
						branch[i][++k] = '\\'; //branch \방향 저장
						k+=2;
					}
					++direction;
				}
				else if(graph[i][k-1] == ' ' && graph[i][k+1] == ' '){ //한자릿수 혹은 빈칸 '-'
					if(direction%2==0){ //왼쪽 노드일때
						branch[i][k] = '/'; //branch /방향 저장
						k=k+2;
					}
					else{ //오른쪽 노드일때
						branch[i][k] = '\\'; //branch \방향 저장
						k=k+2;
					}
					++direction;
				}
			}
		}
		direction = 0;
	}
}

//tree모양 출력 함수
void print_tree(int *tree, int size, int height){
	size = size-1;

	char graph[height][size*3]; //출력할 tree모양 저장할 이차원 배열 
	char branch[height][size*3]; //출력할 가지 저장할 이차원 배열

	//graph정보 넣을 함수 초기화
	for(int i=0; i<height; i++){
		for(int k=0; k<size*3; k++){
			graph[i][k] = ' ';
		}
	}

	make_tree(height, size, graph, tree); //graph배열에 tree저장하는 함수 호출 
	make_branch(height, size, branch, graph); //branch배열에 branch저장하는 함수 호출

	//최종본 출력
	for(int i=0; i<height; i++){
		for(int j=0; j<size*3; j++){
			if(i==0){
				if(j==0)
					printf("Lev%d: ", i+1); //Lev정보 표시
				printf("%c", graph[i][j]); //tree node출력
			}
			else{
				if(j==0)
					printf("      "); //칸 맞추기 위한 빈칸
				printf("%c", branch[i][j]); //branch 출력
			}
		}
		printf("\n");
		if(i!=0){
			printf("Lev%d: ", i+1);
			for(int k=0; k<size*3; k++)
				printf("%c", graph[i][k]);	//tree node 출력
			printf("\n");
		}
	}
	printf("\n");
}

//info변수가 tree에 존재하는 node인지 확인하는 함수
int check_node(int *tree, int size, int info){
	int check=0;
	for(int i=0; i<size; i++){
		if(tree[i] == info)
			check=i;
	}
	return check;
}

//입력받은 node정보 프린트 하는 함수
void print_info(int *tree, int size,  int index){
	int max=0;
	int brother[size];
	int count = 0;

	printf("%d: ", tree[index]);

	//부모 노드 출력
	if(index == 1 || tree[index/2] == 0)
		printf("부모 = 없음, ");
	else
		printf("부모 = %d ", tree[index/2]);

	//자식 노드 출력
	if(index*2 >= size) //마지막 level에 존재하는 node일때 자식 없음
		printf("왼쪽 자식 = 없음, 오른쪽 자식 = 없음, ");
	else{ //마지막level에 있는 node가 아닌 경우
		if(tree[index*2]) //왼쪽 자식이 존재 할때
			printf("왼쪽 자식 = %d, ", tree[index*2]);
		else //왼쪽 자식이 존재하지 않을때
			printf("왼쪽 자식 = 없음, ");

		if(tree[index*2+1]) //오른쪽 자식이 존재 할때
			printf("오른쪽 자식 = %d, ", tree[index*2+1]);
		else //오른쪽 자식이 존재하지 않을때
			printf("오른쪽 자식 = 없음, ");
	}

	//형제 노드 출력
	printf("형제노드 = ");
	if(index == 1) //level 1일 경우 형제노드가 없음
		printf("없음");
	else{
		if(index%2==0){ //오른쪽에 형제가 존재해야할때
			if(tree[index+1] == 0)
				printf("없음");
			else
				printf("%d", tree[index+1]);
		}
		else{ //왼쪽에 형제가 존재해야할때
			if(tree[index-1] == 0)
				printf("없음");
			else
				printf("%d", tree[index-1]);			
		}
	}
	printf("\n");
}

//node정보 출력위해 임의 노드를 사용자로부터 입력받는 함수
void ask_info(int *tree, int size){
	int info, check;

	while(1){
		printf("정보를 알고 싶은 데이터를 입력하세요 (종료 = 999) : ");
		scanf("%d", &info);
		if(info == 999)
			break;

		check=check_node(tree, size, info); //입력받은 node가 존재하는지 확인
		if(!check)
			printf("%d: 노드가 존재하지 않습니다.\n", info);
		else{
			for(int i=0; i<size; i++){
				if(tree[i] == info)
					print_info(tree, size, i);
			}
		}
	}

	printf("종료합니다.\n");
}

//tree의 node를 0으로 초기화 하는 함수
void init_tree(int *tree, int size){
	for(int i=0; i<size; i++)
		tree[i] = 0;
}

int main(int argc, char* argv[]){
	int height, size = 1;

	printf("tree height? ");
	scanf("%d", &height); //트리 height값 입력받음

	for(int i=0; i<height; i++) //tree의 size저장
		size *= 2;
	
	int *tree = (int*)malloc(sizeof(int)*size); //tree size크기만큼 동작할당
	init_tree(tree, size); //tree초기화

	push_data(tree, size);
	print_tree(tree, size, height);

	ask_info(tree, size); 

	return 0;
}
