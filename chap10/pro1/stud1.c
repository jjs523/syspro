#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	char name[20];
};

int main(){	
	struct student *ptr;
	int n, i;

	printf("how many?\n");
	scanf("%d", &n);
	if(n <= 0){
		fprintf(stderr,"error!\n");
		fprintf(stderr,"end!\n");
		exit(1);
	}

	ptr = (struct student *)malloc(n * sizeof(struct student));
	if(ptr == NULL){
		perror("malloc");
		exit(2);
	}

	printf("%d 명의 학번과 이름을 입력하세요.\n", n);
	for(i = 0; i < n; i++)
		scanf("%d %s", &ptr[i].id, ptr[i].name);

	printf("\n* 학생정보 (역순) *\n");
	for(i = n; i >= 0; i--)
		printf("%d %s\n", ptr[i].id, ptr[i].name);

	printf("\n");
	exit(0);
}
