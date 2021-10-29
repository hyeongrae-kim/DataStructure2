#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push_data(int *tree, int size){
	int pos, data;

	printf("트리 데이터 입력을 시작합니다.\n");

	while(1){
		printf("pos, data = ? (enter 0 0 to finish)  ");
		scanf("%d %d", &pos, &data);
		
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

int pow_two(int num){
	int result = 1;
	for(int i=0; i<num; i++)
		result *= 2;

	return result;
}


void print_tree(int *tree, int size, int height){
	size = size-1;

	char graph[height][size];
	char branch[height][size*3];
	int count = 1;
	int tmp = 0;
	
	//2차원 배열에 트리구조 모양 저장
	for(int i=0; i<height; i++){
		if(i==0){
			for(int j=0; j<size; j++){
				if(j%2 == 0){
					graph[height-1][j] = tree[size/2+count]+'0';
					++count;
				}
				else
					graph[height-1][j] = ' ';
			}
		}
		else{
			for(int k=0; k<size; k++)
				graph[height-1-i][k] = ' ';

			for(count = pow_two(i)-1; count<size; count = count+pow_two(i+1)){
				graph[height-1-i][count] = tree[pow_two(height-1-i)+tmp]+'0';
				tmp++;
			}
			tmp=0;
		}
	}

	//branch 출력배열 init
	for(int i=0; i<height; i++){
		for(int k=0; k<size*3; k++){
			if(graph[i][k]!=' ' && i>0){
				if(tmp%2==0){
					k++;
					branch[i][k++] = '/';
				}
				else{
					k++;
					branch[i][k++] = '\\';
				}
				++tmp;
			}
			else{
				for(int w=0; w<3; w++){
					branch[i][k] = ' ';
					k++;
				}
				k--;
			}
		}
		tmp=0;
	}

	//최종본 출력
	for(int i=0; i<height; i++){
		for(int j=0; j<size; j++){
			if(i==0){
				for(int w=0; w<3; w++)
					printf("%c", graph[i][j]);
			}
			else
				printf("%c", branch[i][j]);
		}
		printf("\n");
		if(i!=0){
			for(int k=0; k<size; k++){
				for(int x=0; x<3; x++)
					printf("%c", graph[i][k]);
			}	
			printf("\n");
		}
	}
	printf("\n");

}

int check_node(int *tree, int size, int info){
	int check=0;
	for(int i=0; i<size; i++){
		if(tree[i] == info)
			check=i;
	}
	return check;
}

void print_info(int *tree, int size,  int index){
	int max=0;

	printf("%d: ", tree[index]);

	//부모 노드 출력
	if(index == 1 || tree[index/2] == 0)
		printf("부모 = 없음, ");
	else
		printf("부모 = %d ", tree[index/2]);

	//자식 노드 출력
	if(index*2 >= size)
		printf("왼쪽 자식 = 없음, 오른쪽 자식 = 없음, ");
	else{
		if(tree[index*2])
			printf("왼쪽 자식 = %d, ", tree[index*2]);
		else
			printf("왼쪽 자식 = 없음, ");

		if(tree[index*2+1])
			printf("오른쪽 자식 = %d, ", tree[index*2+1]);
		else
			printf("오른쪽 자식 = 없음, ");
	}

	//형제 노드 출력
	printf("형제노드 = ");
	if(index == 1)
		printf("없음\n");
	else{
		for(int i=1; i<=size; i=i*2){
			if(index<i){
				max = i; 
				break;
			}
		}
		for(int i=max/2; i<max; i++){
			if(i==index)
				continue;
			else
				printf("%d, ", tree[i]);
		}
		printf("\n");
	}
}

void ask_info(int *tree, int size){
	int info, check;

	while(1){
		printf("정보를 알고 싶은 데이터를 입력하세요 (종료 = 999) : ");
		scanf("%d", &info);
		if(info == 999)
			break;

		check=check_node(tree, size, info);
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

void init_tree(int *tree, int size){
	for(int i=0; i<size; i++)
		tree[i] = 0;
}

int main(int argc, char* argv[]){
	int height, size = 1;

	printf("tree height? ");
	scanf("%d", &height);

	for(int i=0; i<height; i++)
		size *= 2;
	
	int *tree = (int*)malloc(sizeof(int)*size);
	init_tree(tree, size);

	push_data(tree, size);
	print_tree(tree, size, height);

	//ask_info(tree, size);

	return 0;
}
