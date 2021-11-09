#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

int main(int argc, char* argv[]){
	char str[100] = "2a1(2ab9c)2(2abc)";
	char result[100] = {0};
	char pth[100];
	int count = 0, count_r = 0, count_tmp = 0, count_pth = 0;
	int q_size = 0;
	queue<char> q;

	for(int i=0; i<(int)strlen(str); i++){
		if(str[i] >= '1' && str[i] <= '9'){
			q_size = q.size();
			while(!q.empty()){
				result[count_r++] = q.front();
				q.pop();
			}
			if(count>1){
				for(int k=1; k<count; k++){
					for(int j=0; j<q_size; j++)
						result[count_r++] = result[count_r-q_size];
				}
			}
			if(q_size != 0) result[count_r++] = ' ';
			count = str[i]-48;
		}
		else if(str[i] >= 'a' && str[i] <= 'z')
			q.push(str[i]);
		//-------괄호처리--------
		else if(str[i] == '('){
			while(str[i] != ')'){
				i++;
				if(str[i] >= '1' && str[i] <= '9'){
					q_size = q.size();
					while(!q.empty()){
						pth[count_pth++] = q.front();
						q.pop();
					}
					if(count_tmp>1){
						for(int k=1; k<count_tmp; k++){
							for(int j=0; j<q_size; j++)
								pth[count_pth++] = pth[count_pth-q_size];
						}
					}
					if(q_size != 0) pth[count_pth++] = ' ';
					count_tmp = str[i]-48;
				}
				else if(str[i] >= 'a' && str[i] <= 'z'){
					q.push(str[i]);
				}
			}
			q_size = q.size();
			while(!q.empty()){
				pth[count_pth++] = q.front();
				q.pop();
			}
			if(count_tmp>1){
				for(int k=1; k<count_tmp; k++){
					for(int j=0; j<q_size; j++)
						pth[count_pth++] = pth[count_pth-q_size];
				}
			}
			pth[count_pth++] = ' ';
			for(int k=0; k<count; k++){
				for(int j=0; j<count_pth; j++){
					result[count_r++] = pth[j];
				}
			}
			pth[0] = '\0';
			count_pth = 0;
		}
		//-------괄호처리 끝------
	}
	q_size = q.size();
	while(!q.empty()){
		result[count_r++] = q.front();
		q.pop();
	}
	if(count>1){
		for(int k=1; k<count; k++){
			for(int j=0; j<q_size; j++)
				result[count_r++] = result[count_r-q_size];
		}
	}

	printf("%s\n", result);
	return 0;
}
