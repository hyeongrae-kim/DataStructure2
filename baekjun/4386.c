#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1001
#define INF 1000000

int parent[MAX_VERTICES]; //부모노드

void set_init(int n){
	for(int i=0; i<n; i++)
		parent[i] = -1;
}

int set_find(int curr){
	if(parent[curr] == -1)
		return curr;
	while(parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b){
	int root1 = set_find(a);
	int root2 = set_find(b);
	if(root1 != root2)
		parent[root1] = root2;
}

struct Edge{ //간선 구조체
	double x1, y1;
	double x2, y2;
	double weight;
	int start, end;
};

struct Point{ //점 구조체
	double x;
	double y;
};

typedef struct GraphType{
	int edge; //간선의 개수
	int node; //노드의 개수
	struct Edge edges[2*MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g){
	g->edge=0;
	g->node=0;
	for(int i=0; i<2*MAX_VERTICES; i++){		
		g->edges[i].x1 = 0;
		g->edges[i].y1 = 0;
		g->edges[i].x2 = 0;
		g->edges[i].y2 = 0;
		g->edges[i].weight = 0;
	}
}

double cal_weight(double x1, double y1, double x2, double y2){
	double result = 0;
	double v1 = (x1-x2)*(x1-x2);
	double v2 = (y1-y2)*(y1-y2);
	result = sqrt(v1+v2);

	return result;
}

void insert_edge(GraphType* g, double x1, double y1, double x2, double y2){
	g->edges[g->edge].x1 = x1;
	g->edges[g->edge].y1 = y1;
	g->edges[g->edge].x2 = x2;
	g->edges[g->edge].y2 = y2;
	g->edges[g->edge].weight = cal_weight(x1, y1, x2, y2);
	g->edge++;
}

int compare(const void* a, const void* b){
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

double kruskal(GraphType* g){
	int edge_accepted = 0; //현재까지 선택된 간선의 수
	int uset, vset; //정점 u와 정점 v의 집합번호
	struct Edge e;
	double result = 0;

	set_init(g->edge);
	qsort(g->edges, g->edge, sizeof(struct Edge), compare); //가중치 순으로 정렬

	int i=0;

	while(edge_accepted < (g->node)-1){
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if(uset != vset){
			edge_accepted++;
			set_union(uset, vset);
			result += e.weight;
		}
		i++;
	}

	return result;
}

int main(int argc, char* argv[]){
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	int n=0;
	double result = 0;

	//--------별 개수 및 좌표 받기--------
	scanf("%d", &n);
	g->node = n;
	struct Point points[g->node];
	for(int i=0; i<n; i++){
		scanf("%lf %lf", &points[i].x, &points[i].y);
	}
	
	//-------간선 추가하기-----------
	for(int i=0; i<n; i++){
		for(int k=i+1; k<n; k++){
			insert_edge(g, points[i].x, points[i].y, points[k].x, points[k].y);
			g->edges[(g->edge)-1].start = i;
			g->edges[(g->edge)-1].end = k;
		}
	}
	result = kruskal(g);
	free(g);
	printf("%.2lf", result);

	return 0;
}
