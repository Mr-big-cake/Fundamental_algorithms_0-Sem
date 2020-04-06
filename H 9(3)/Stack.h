#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<locale.h>

#pragma warning (disable: 4996)


#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

#define FEW_ARGUMENTS 1
#define FIÒ_NO_OPEN 2


typedef struct Node_tag {
	char data;
	struct Node_tag* next;
} Stack;

void push(Stack** head, char data) {
	Stack* tmp = (Stack*)malloc(sizeof(Stack));
	if (tmp == NULL) exit(STACK_OVERFLOW);
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
}

Stack* pops(Stack** head) {
	if ((*head) == NULL) exit(STACK_UNDERFLOW);
	Stack* out;
	out = *head;
	*head = (*head)->next;
	return out;
}

char popd(Stack** head) {
	Stack* out;
	char data;
	if (*head == NULL) exit(STACK_UNDERFLOW);
	out = *head;
	*head = (*head)->next;
	data = out->data;
	free(out);
	return data;
}

char peek(const Stack* head) {
	if (head == NULL) {
		exit(STACK_UNDERFLOW);
	}
	return head->data;
}

void printStack(const Stack* head) {
	printf("stack >");
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
}

size_t getSize(const Stack* head) {
	size_t size = 0;
	while (head) {
		size++;
		head = head->next;
	}
	return size;
}


const char* errors[] =
{
	//1
	"Few arguments" 

	//2
	"The input file did not open"

	//3

};

void error(int errorId) {
	printf("Error #%d: %s \n", errorId, errors[errorId - 1]);
	system("pause");
	exit(errorId);
}
