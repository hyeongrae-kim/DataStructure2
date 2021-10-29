#include <stdio.h>

int funcA(int n){
	if (n==0){
		int c=3;
		return 0;
	}
	if (n==1){
		int b=2;
		return 1;
	}
	if(n>1){
		int a=1;
		return n+funcA(n-1);
	}
}

int main(int argc, char* argv[]){
	funcA(10);
	return 0;
}
