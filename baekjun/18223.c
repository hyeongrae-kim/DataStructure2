#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 5001 //맥스노드개수
#define INF 1000000

int gunwoo = 0; //건우의 위치

typedef struct GraphType{
	int n; //정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터 최단거리 저장
int found[MAX_VERTICES]; // 방문한 정점 표시

int choose(int n){
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=1; i<=n; i++){
		if(distance[i] < min && !found[i]){
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

int find_gunwoo(GraphType* g){
	int i, u, w;
	int take=0;
	for(i=0; i<g->n; i++){ //초기화
		distance[i] = g->weight[1][i];
		found[i] = FALSE;
	}
	found[1] = TRUE; //시작정점 방문
	distance[1] = 0;
	for(i=0; i<g->n-1; i++){
		u = choose(g->n);
		found[u] = TRUE;
		for(w=1; w<=g->n; w++){
			if(g->weight[u][g->n] != INF){
				return take;
			}
			if(!found[w]){
				if(distance[u]+g->weight[u][w] < distance[w]){
					distance[w] = distance[u] + g->weight[u][w];
					if(w == gunwoo)
						take=1;
				}
			}
		}
	}

	return take;
}

void graph_init(GraphType* g){
	g->n=0;
	for(int i=0; i<MAX_VERTICES; i++){
		for(int k=0; k<MAX_VERTICES; k++){
			g->weight[i][k] = INF;
		}
	}
}

int main(int argc, char* argv[]){
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));

	int v, e;
	int start, end, weight;
	int result;

	scanf("%d %d %d", &v, &e, &gunwoo);
	graph_init(g);
	g->n = v;

	for(int i=0; i<e; i++){
		scanf("%d %d %d", &start, &end, &weight);
		g->weight[start][end] = weight;
		g->weight[end][start] = weight;
	}
	
	result = find_gunwoo(g);
	printf("\n");
	if(result==1)
		printf("SAVE HIM");
	else
		printf("GOOD BYE");

	free(g);
	return 0;
}
