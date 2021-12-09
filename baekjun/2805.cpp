#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

int cal_meter(int tree[], int count, int cut){
	int result = 0;
	for(int i=0; i<count; i++){
		if(tree[i] > cut){
			result += tree[i]-cut;
		}
	}
	return result;
}

int search(int tree[], int count, int meter, int low, int high){
	int  middle;

	while(low <= high){
		middle = (low+high)/2;
		if(meter == cal_meter(tree, count, middle))
			return middle;
		else if(meter > cal_meter(tree, count, middle))
			high = middle - 1;
		else
			low = middle + 1;
	}
	return -1;

}

int main(int argc, char* argv[]){
	int count = 0, meter = 0; // 나무갯수, 잘라야할 나무 미터
	scanf("%d %d", &count, &meter);
	int tree[count];
	for(int i=0; i<count; i++)
		scanf("%d", &tree[i]);
	sort(tree, tree+count);

	printf("%d", search(tree, count, meter, 0, tree[count-1]));

	return 0;
}
