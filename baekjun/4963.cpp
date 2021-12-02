#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define MAX_SIZE 51

using namespace std;
int island[MAX_SIZE][MAX_SIZE];
int width;
int height;

typedef struct node{
	int x;
	int y;
} node;

//동적할당 배열로바꿔서 해보기
int find_island(){
	int result=0;
	queue <node*> q;
	node *tmp = NULL;
	node *tmp2 = NULL;
	for(int i=1; i<=height; i++){
		for(int k=1; k<=width; k++){
			if(island[i][k] == 1){
				//graph탐색시작-> 전부 2로바꿔줌
				tmp = (node*)malloc(sizeof(node));
				tmp->x = i;
				tmp->y = k;
				q.push(tmp);
				while(!q.empty()){
					tmp = q.front();
					q.pop();
					island[tmp->x][tmp->y] = 2;
					for(int n=(tmp->x)-1; n<=(tmp->x)+1; n++){
						for(int m=(tmp->y)-1; m<=(tmp->y)+1; m++){
							if(island[n][m] == 1){
								tmp2 = (node*)malloc(sizeof(node));
								tmp2->x = n;
								tmp2->y = m;
								q.push(tmp2);
							}
						}
					}
					free(tmp);
				}
				result++;
			}
		}
	}
	return result;
}

int main(int argc, char* argv[]){
	int count=1, result=0;
	while(1){
		//지도 너비 높이 받기
		scanf("%d %d", &width, &height);
		if(width==0 && height==0)
			break;
		
		//섬 정보받기
		char tmp[width*2];
		for(int i=1; i<=height; i++){
			getchar();
			scanf("%[^\n]s", tmp);
			for(int k=0; k<width*2-1; k=k+2)
				island[i][count++] = int(tmp[k]-48);
			count = 1;
			tmp[0] = '\0';
		}
			
		result = find_island();
		printf("%d\n", result);

		//island 2차원 배열 초기화
		for(int i=0; i<=width; i++)
			for(int k=0; k<=height; k++)
				island[i][k] = 0;
	}

}
