#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 5001 //맥스노드개수
#define INF 1000000

int gunwoo = 0;

typedef struct GraphType{
	int n; //정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

struct DistNode{
	int dist;
	int road[MAX_VERTICES];
	int road_max;
};

struct DistNode distance[MAX_VERTICES]; // 시작 정점으로부터 최단거리 저장
int found[MAX_VERTICES]; // 방문한 정점 표시

int choose(int n){
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=1; i<=n; i++){
		if(distance[i].dist < min && !found[i]){
			min = distance[i].dist;
			minpos = i;
		}
	}
	return minpos;
}

int has_gunwoo(int i){
	for(int k=0; k<distance[i].road_max; k++){
		if(distance[i].road[k] == gunwoo){
			return 1;
		}
	}
	return 0;
}

void find_gunwoo(GraphType* g){
	int i, u, w;
	int gw;

	for(i=1; i<=g->n; i++){ //초기화
		distance[i].dist = g->weight[1][i];
		if(i==1)
			distance[i].road[distance[i].road_max++] = 1;
		if(g->weight[1][i] != INF && i!=1){
			distance[i].road[distance[i].road_max++] = 1;
			distance[i].road[distance[i].road_max++] = i;
		}
		found[i] = FALSE;
	}
	found[1] = TRUE; //시작정점 방문
	distance[1].dist = 0;
	for(i=0; i<g->n-1; i++){
		u = choose(g->n);
		found[u] = TRUE;
		for(w=1; w<=g->n; w++){
			if(!found[w]){
				if(distance[u].dist + g->weight[u][w] < distance[w].dist){
					distance[w].dist = distance[u].dist + g->weight[u][w];
					distance[w].road_max = 0; //road array init?
					for(int k=0; k<distance[u].road_max; k++){
						distance[w].road[distance[w].road_max++] = distance[u].road[k];
					}
					distance[w].road[distance[w].road_max++] = w;
				}
				else if(distance[u].dist + g->weight[u][w] == distance[w].dist){ //거리가 같을때
					gw = has_gunwoo(u);
					if(gw){
						distance[w].road_max = 0;
						for(int k=0; k<distance[u].road_max; k++){
							distance[w].road[distance[w].road_max++] = distance[u].road[k];
						}
						distance[w].road[distance[w].road_max++] = w;
					}
				}
			}
		}
	}

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

	scanf("%d %d %d", &v, &e, &gunwoo);
	graph_init(g);
	g->n = v;

	for(int i=1; i<= g->n; i++){
		distance[i].road_max = 0;
		distance[i].dist = INF;
	}

	for(int i=0; i<e; i++){
		scanf("%d %d %d", &start, &end, &weight);
		g->weight[start][end] = weight;
		g->weight[end][start] = weight;
	}
	for(int i=1; i<=g->n; i++){
		g->weight[i][i] = 0;
	}
	
	find_gunwoo(g);

	for(int i=0; i<distance[g->n].road_max; i++){
		if(distance[g->n].road[i] == gunwoo){
			printf("SAVE HIM");
			free(g);
			return 0;
		}
	}
	printf("GOOD BYE");
	free(g);
	return 0;
}
