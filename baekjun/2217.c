#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100000

int sorted[MAX_SIZE];

void merge(int list[], int left, int mid, int right){
	int i=0;
	int count_r = mid+1;
	int count_l = left;
	for(i=left; count_r<=right && count_l<=mid; ){
		if(list[count_l] > list[count_r])
			sorted[i++] = list[count_r++];
		else
			sorted[i++] = list[count_l++];
	}
	if(count_l<=mid)
		for(int k=count_l; count_l<=mid; count_l++)
			sorted[i++] = list[count_l];
	if(count_r<=right)
		for(int k=count_r; count_r<=right; count_r++)
			sorted[i++] = list[count_r];

	for(int k=left; k<=right; k++)
		list[k] = sorted[k];
}


void merge_sort(int list[], int left, int right){
	int mid=0;
	if(left<right){
		mid = (left+right)/2;
		merge_sort(list, left, mid);
		merge_sort(list, mid+1, right);
		merge(list, left, mid, right);
	}
}

int main(int argc, char* argv[]){
	int count=0;
	int weight = 0;
	int tmp=0;
	int result = 0;

	scanf("%d", &count);
	getchar();
	int arr[count];
	for(int i=0; i<count; i++){
		scanf("%d", &arr[i]);
		getchar();
	}
	merge_sort(arr, 0, count-1);

	for(int k=0; k<count; k++){
		weight = count-k-1;
		for(int i=count-k-1; i<count; i++){
			tmp += arr[weight];
		}
		if(tmp>result) result = tmp;
		tmp = 0;
	}
	printf("%d", result);
	
	return 0;
}
