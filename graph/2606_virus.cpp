#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 101
typedef struct GraphType{
	int n; //정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int attacked[MAX_VERTICES]; //virus 감염됨 표시

//그래프 초기화
void init(GraphType *g){
	int r, c;
	g->n = 0;
	for(r = 0; r<MAX_VERTICES; r++)
		for(c = 0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

//정점 삽입 연산
void insert_vertex(GraphType* g, int v){
	if(((g->n)+1) > MAX_VERTICES){
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge(GraphType* g, int start, int end){
	if(start>g->n || end>g->n){
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//인접 행렬로 표현된 그래프에 대한 큐를 활용한 너비 우선 탐색
//바이러스 감염된 컴퓨터 표시
void bfs_mat(GraphType* g, int v){ //v부터 탐색시작
	queue <int> q;
	q.push(v);
	attacked[v] = TRUE;
	while(!q.empty()){
		v=q.front();
		q.pop();
		for(int i=1; i<=(g->n); i++){
			if((g->adj_mat[v][i] == 1) && attacked[i] != TRUE){
				q.push(i);
				attacked[i] = TRUE;
			}
		}
	}
}

int main(void){
	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	int edge=0, vertex=0, start=0, end=0, count=0;
	scanf("%d", &vertex);
	scanf("%d", &edge);

	for(int i=1; i<=vertex; i++)
		insert_vertex(g, i);
	
	for(int i=0; i<edge; i++){
		scanf("%d %d", &start, &end);
		insert_edge(g, start, end);
	}

	bfs_mat(g, 1);
	for(int i=1; i<=MAX_VERTICES; i++){
		if(attacked[i] == TRUE)
			count++;
	}
	printf("%d", count-1);
	free(g);

	return 0;
}
