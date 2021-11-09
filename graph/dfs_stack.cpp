#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphType{
	int n; //정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

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
	if(start>=g->n || end>=g->n){
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[start][end] = 1;
}

//인접 행렬로 표현된 그래프에 대한 스택을 활용한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v){ //v부터 탐색시작
	stack<int> s;
	s.push(v);
	while(!s.empty()){
		v = s.top();
		s.pop();
		if(visited[v] != TRUE){
			visited[v] = TRUE;
			printf("정점 %d-> ", v);
			for(int k=MAX_VERTICES-1; k>=0; k--){
				if(visited[k] != TRUE && (g->adj_mat[v][k] == 1))
					s.push(k);
			}
		}
	}
}

int main(void){
	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	
	for(int i=0; i<4; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0);
	printf("\n");
	free(g);

	return 0;
}
