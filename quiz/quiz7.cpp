#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <memory.h>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

using namespace std;


void selection_sort(int list[], int n){
	int i, j, least, temp;
	for(i=0; i<n-1; i++){
		least = i;
		for(j=i+1; j<n; j++)
			if(list[j] <list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

void insertion_sort(int list[], int n){
	int i, j, key;
	for(i=1; i<n; i++){
		key = list[i];
		for(j=i-1; j>=0 && list[j]>key; j--)
			list[j+1] = list[j];
		list[j+1] = key;
	}
}

void bubble_sort(int list[], int n){
	int i, j, temp;
	for(i=n-1; i>0; i--){
		for(j=0; j<i; j++)
			if(list[j] > list[j+1])
				SWAP(list[j], list[j+1], temp);
	}
}


int main(int argc, char* argv[]){
	struct timeval start, end;
	double diff;
	int size;
	srand(time(NULL));
	scanf("%d", &size);
	int *list1 = (int*)malloc(sizeof(int)*size);
	int *list2 = (int*)malloc(sizeof(int)*size);
	int *list3 = (int*)malloc(sizeof(int)*size);
	int *list4 = (int*)malloc(sizeof(int)*size);


	for(int i=0; i<size; i++)
		list1[i] = rand()%size;
	
	memmove(list2, list1, sizeof(int)*size);
	memmove(list3, list1, sizeof(int)*size);
	memmove(list4, list1, sizeof(int)*size);
	
	printf("START!!\n");
	gettimeofday(&start, NULL);
	selection_sort(list1, size);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec-start.tv_sec) + ((end.tv_usec-start.tv_usec)/1000000);
	printf("[선택정렬]: %.1f\n", diff);
	if(size<=100){
		for(int i=0; i<size; i++)
			printf("%d ", list1[i]);
		printf("\n");
	}

	gettimeofday(&start, NULL);
	insertion_sort(list2, size);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec-start.tv_sec) + ((end.tv_usec-start.tv_usec)/1000000);
	printf("[삽입정렬]: %.1f\n", diff);
	if(size<=100){
		for(int i=0; i<size; i++)
			printf("%d ", list2[i]);
		printf("\n");
	}

	gettimeofday(&start, NULL);
	bubble_sort(list3, size);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec-start.tv_sec) + ((end.tv_usec-start.tv_usec)/1000000);
	printf("[버블정렬]: %.1f\n", diff);
	if(size<=100){
		for(int i=0; i<size; i++)
			printf("%d ", list3[i]);
		printf("\n");
	}

	gettimeofday(&start, NULL);
	sort(list4, list4+size);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec-start.tv_sec) + ((end.tv_usec-start.tv_usec)/1000000);
	printf("[STL_SORT정렬]: %.1f\n", diff);
	if(size<=100){
		for(int i=0; i<size; i++)
			printf("%d ", list4[i]);
		printf("\n");
	}
	free(list1);
	free(list2);
	free(list3);
	free(list4);
	printf("END\n");
	return 0;
}
