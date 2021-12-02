#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1234567891
#define WEIGHT 31

typedef struct{
	char *str;
} element;

struct list{
	element item;
	struct list *link;
};

struct list *hash_table[TABLE_SIZE];

int pow_num(int num, int repeat){
	int result=1;
	for(int i=0; i<repeat; i++){
		result = result*num;
	}
	return result;
}

int hash_function(char* tmp){
	int result=0;
	for(int i=0; i<(int)strlen(tmp); i++){
		result += (tmp[i]-96)*pow_num(WEIGHT, i);
	}
	return result%TABLE_SIZE;
}

/*void hash_chain_add(element item){
	int hash_value = hash_function(item.str);
	struct list *ptr;
	struct list *node_before = NULL, *node = ht[hash_value];
	for(; node; node_before = node, node = node->link){
		if(node->item.str == item.str){
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if(node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}*/

int main(void){
	int len=0;
	char *str;
	int result = 0;

	scanf("%d", &len);
	scanf("%s", str);
	
	result = hash_function(str);
	printf("%d", result);
}
