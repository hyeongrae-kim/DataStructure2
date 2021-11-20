#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType *g){
	int r, c;
	g->n=0;
	for(r=0; r<MAX_VERTICES; r++)
		for(c=0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g){
	if(((g->n)+1) > MAX_VERTICES){
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end){
	if(start>=g->n || end >= g->n){
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end]=1;
	g->adj_mat[end][start]=1;
}

void insert_edge_plus(GraphType* g){
	int start=0, end=0, count=0;
	while(1){
		scanf("%d %d", &start, &end);
		if(start == -1 && end == -1)
			break;
		if(start >= g->n || end>=g->n){
			fprintf(stderr, "그래프: 정점 번호 오류");
			return;
		}
		g->adj_mat[start][end] = 1;
		g->adj_mat[end][start] = 1;
		count++;
	}
	printf("에지 %d개 추가 완료\n\n", count);
}

void delete_edge(GraphType* g){
	int start=0, end=0, count=0;
	while(1){
		scanf("%d %d", &start, &end);
		if(start == -1 && end == -1)
			break;
		if(start >= g->n || end>=g->n){
			fprintf(stderr, "그래프: 정점 번호 오류");
			return;
		}
		g->adj_mat[start][end] = 0;
		g->adj_mat[end][start] = 0;
		count++;
	}
	printf("에지 %d개 삭제 완료\n\n", count);
}

void find_path(GraphType* g, int start, int end){
	int tmp=0, result=0, count_path=0;
	int path[100];
	stack <int> s;
	stack <int> s_tmp;
	s.push(start);
	while(!s.empty()){
		tmp = s.top();
		s.pop();
		path[count_path++] = tmp;
		s_tmp.push(tmp);
		if(visited[tmp] != TRUE){
			visited[tmp] = TRUE;
			for(int i=MAX_VERTICES-1; i>=0; i--){
				if(visited[i] != TRUE && g->adj_mat[tmp][i] == 1){
					if(i==end){
						printf("PATH 발견: ");
						path[count_path] = i;
						printf("%d", path[0]);
						for(int k=1; k<=count_path; k++)
							printf("-%d", path[k]);
						printf("\n\n");
						return;
					}
					s.push(i);
				}
			}
		}
		printf("%d\n", s.top());
		if(g->adj_mat[tmp][s.top()] != 1){
			while(g->adj_mat[s.top()][s_tmp.top()] != 1){
				path[count_path++] = s_tmp.top();
				s_tmp.pop();
			}
			path[count_path++] = s_tmp.top();
			s_tmp.pop();
		}
	}
	printf("PATH 없음\n\n");
	return;	
}

void print_menu(){
	printf("1. 에지 추가\n");
	printf("2. 에지 삭제\n");
	printf("3. PATH 찾기\n");
	printf("4. 종료\n");
	printf("입력: ");
}

void choice_menu(GraphType* g){
	int choice = 0, start=0, end=0;
	while(choice!=4){
		print_menu();
		scanf("%d", &choice);

		switch(choice){
			case 1:
				insert_edge_plus(g);
				break;
			case 2:
				delete_edge(g);
				break;
			case 3:
				scanf("%d %d", &start, &end);
				find_path(g, start, end);
				for(int i=0; i<MAX_VERTICES; i++)
					visited[i] = 0;
				break;
			case 4:
				break;
		}
	}

	return;
}

int main(void){
	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	int choice=0;

	for(int i=0; i<10; i++)
		insert_vertex(g);
	
	insert_edge(g, 0, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 1, 2);
	//insert_edge(g, 1, 3);
	//insert_edge(g, 2, 3);
	insert_edge(g, 3, 6);
	insert_edge(g, 3, 8);
	insert_edge(g, 4, 5);
	insert_edge(g, 6, 7);
	insert_edge(g, 8, 9);

	choice_menu(g);
	free(g);
	printf("BYE\n");	
}
