#include <stdio.h>

int main(int argc, char* argv[]){
	char a[20] = "가나다라마";
	char b[20] = "바사아자차";
	char c[20] = "가가가가가";
	for(int i=0; i<10; i++){
		printf("%d", a[i]);
	}
	printf("\n");
	for(int i=0; i<10; i=i+2){
		printf("%d", c[i]);
	}
	printf("\n");
	for(int i=0; i<20; i++){
		printf("%c", b[i]);
	}
	printf("\n");

	printf("가나다라마\n");
	return 0;
}
