#include <stdio.h>

int main(){
	char str[10] = "abcde";
	for (int i=0; i<5; i++){
		str[5+i] = str[4-i];
	}
	printf("%s\n", str);
}
