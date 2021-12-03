#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 5

typedef struct{
	char str[100];
} element;

struct list{
	element item;
	struct list *link;
};

struct list *hash_table[TABLE_SIZE];

int hash_function(char* str){
	int result=0;
	for(int i=0; i<(int)strlen(str); i++){
		result += str[i]-96;
	}
	return result%TABLE_SIZE;
}

void hash_chain_add(element item){
	int hash_value = hash_function(item.str);
	struct list *ptr;
	struct list *node_before = NULL, *node = hash_table[hash_value];
	for(; node; node_before = node, node = node->link){
		if(strcmp(node->item.str, item.str)==0){
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if(node_before){
		printf("(Collision!)\n");
		node_before->link = ptr;
	}
	else
		hash_table[hash_value] = ptr;
}

void hash_chain_print(){
	struct list *node;
	
	for(int i=0; i<TABLE_SIZE; i++){
		printf("%d: ", i);
		for(node = hash_table[i]; node; node=node->link){
			if(node->link)
				printf("%s - ", node->item.str);
			else
				printf("%s", node->item.str);
		}
		printf("\n");
	}
	printf("-------------------------\n");
}

void FunHashingQuiz(){
	char str[100];
	char exit[5] = "exit";
	element tmp;
	while(1){
		printf("입력: ");
		scanf("%s", str);
		if(strcmp(str, exit)==0){
			printf("shutdown\n");
			break;
		}
		strcpy(tmp.str, str);
		hash_chain_add(tmp);
		hash_chain_print();
	}
}

int main(void){
	FunHashingQuiz();
	return 0;
}
