#include <stdio.h>

int main(int argc, char* argv[]){
	char a[5] = "김";
	char b[5] = "가";

	if(a>b)
		printf("김은 가보다 크다\n");
	else if(b>a)
		printf("가는 김보다 크다\n");
	else
		printf("?\n");

	return 0;

}
