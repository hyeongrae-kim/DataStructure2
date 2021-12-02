#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int compare(int a, int b){
	return a>b;
}

int main(int argc, char* argv[]){
	int a[10] = {9, 3, 5, 4, 1, 10, 8, 6, 7, 2};
	sort(a, a+10, compare);

	for(int i=0; i<10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
