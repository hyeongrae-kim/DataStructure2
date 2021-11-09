#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	//1q. 입력값 : 2a4b3cd2k // ouput : aabbbbcdcdcd kk
	//2q. input : aabbbbcdcdcdkk // ouput : 2a4b3cd2k
	char* str = argv[1];
	char result[100] = {0};
	int count = 0;
	int result_i = 0;

	//aa bbbb c d c d c d kk
	for(int i=0; i<(int)strlen(str); i++){
		if(str[i] == str[i+1]){
			while(str[i]==str[i+1]){
				count++;
				i++;
			}
			count++;
			result[result_i++] = count+48;
			result[result_i++] = str[i];
			count = 0;
		}
		else if(str[i] != str[i+1]){
			if(str[i]+str[i+1] == str[i+2]+str[i+3]){
				while(str[i]+str[i+1] == str[i+2]+str[i+3]){
					count+=1;
					i+=2;
				}
				count+=1;
				i+=1;
				result[result_i++] = count+48;
				result[result_i++] = str[i-1];
				result[result_i++] = str[i];
				count = 0;
			}
			else{
				result[result_i++] = '1';
				result[result_i++] = str[i];
				i++;
			}
		}
	}

	printf("%s\n", result);

	return 0;
}
