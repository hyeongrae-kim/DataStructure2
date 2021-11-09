#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
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
	if(start>g->n || end>g->n){
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//인접 행렬로 표현된 그래프에 대한 큐를 활용한 너비 우선 탐색
void bfs_mat(GraphType* g, int v){ //v부터 탐색시작
	queue <int> q;
	q.push(v);
	visited[v] = TRUE;
	printf("%d", v);
	while(!q.empty()){
		v=q.front();
		q.pop();
		for(int i=1; i<=(g->n); i++){
			if((g->adj_mat[v][i] == 1) && visited[i] != TRUE){
				q.push(i);
				visited[i] = TRUE;
				printf(" %d", i);
			}
		}
	}
}

//인접 행렬로 표현된 그래프에 대한 스택을 활용한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v){ //v부터 탐색시작
	int tmp = v;
	stack<int> s;
	s.push(v);
	while(!s.empty()){
		v = s.top();
		s.pop();
		if(visited[v] != TRUE){
			visited[v] = TRUE;
			if(tmp==v)
				printf("%d", v);
			else
				printf(" %d", v);
			for(int k=g->n; k>=1; k--){
				if(visited[k] != TRUE && (g->adj_mat[v][k] == 1))
					s.push(k);
			}
		}
	}
}

int main(void){
	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	int edge=0, vertex=0, count=0, start=0, end=0;
	printf("정점, 간선, 시작번호: ");
	scanf("%d %d %d", &vertex, &edge, &count);

	for(int i=0; i<vertex; i++)
		insert_vertex(g, i);
	
	for(int i=0; i<edge; i++){
		printf("선 입력: ");
		scanf("%d %d", &start, &end);
		insert_edge(g, start, end);
	}

	dfs_mat(g, count);
	printf("\n");
	for(int i=0; i<MAX_VERTICES; i++)
		visited[i] = 0;

	bfs_mat(g, count);
	printf("\n");
	free(g);

	return 0;
}
