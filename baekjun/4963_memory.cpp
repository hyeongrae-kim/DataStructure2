#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define MAX_SIZE 51

using namespace std;
int island[MAX_SIZE][MAX_SIZE];
int width;
int height;


//동적할당 배열로바꿔서 해보기
int find_island(){
	int result=0;
	queue <int> q;
	int x=0, y=0;
	int x_tmp = 0, y_tmp = 0;
	for(int i=1; i<=height; i++){
		for(int k=1; k<=width; k++){
			if(island[i][k] == 1){
				//graph탐색시작-> 전부 2로바꿔줌
				x = i;
				y = k;
				q.push(x);
				q.push(y);
				while(!q.empty()){
					x = q.front();
					q.pop();
					y = q.front();
					q.pop();
					island[x][y] = 2;
					for(int n=x-1; n<=x+1; n++){
						for(int m=y-1; m<=y+1; m++){
							if(island[n][m] == 1){
								x_tmp = n;
								y_tmp = m;
								q.push(x_tmp);
								q.push(y_tmp);
							}
						}
					}
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
