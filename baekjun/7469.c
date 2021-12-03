#include <stdio.h>
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

int main(void){
	int arrcount=0, count=0, arrlen=0;
	int start, end, pick;
	scanf("%d %d", &arrlen, &count);

	int arr[arrlen];
	char tmp[arrlen*2];
	getchar();
	scanf("%[^\n]s", tmp);

	for(int i=0; i<arrlen*2-1; i=i+2)
		arr[arrcount++] = tmp[i]-48;

	arrcount = 0;
	for(int i=0; i<count; i++){
		getchar();
		scanf("%d %d %d", &start, &end, &pick);	
		merge_sort(arr, start-1, end-1);
		printf("%d\n", arr[start+pick-2]);
		for(int k=0; k<arrlen*2-1; k=k+2)
			arr[arrcount++] = tmp[k]-48;
		for(int k=0; k<arrlen; k++)
			sorted[k] = 0;
		arrcount = 0;
	}
	
	return 0;	
}
