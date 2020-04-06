#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<locale.h>
#include<stdarg.h>
#include"Head.h"

#pragma warning (disable: 4996)


#define SUBTRACTION 0
#define ADDITION 1
#define DIVISION 2
#define MULTIPLICATION 3
#define TAKING_THE_REMAINDER_FROM_DIVIDING 4
#define POW 5


#define STACK_OVERFLOW  -257
#define STACK_UNDERFLOW -258
#define LACK_MEMORY -259

#define FEW_ARGUMENTS 1
#define FIN_NO_OPEN 2
#define FOUT_NO_OPEN 3
#define OUT_OF_MEMORY 4
#define UNAVAILABLE_CHARACTER 5
#define ERROR_BRACKETS 6
#define ERROR_INT_OVERFLOW 7
#define ERROR_DIVISION_BY_ZERO 8

const char* errors[] =
{
	//1
	"Few arguments\n",

	//2
	"The input file did not open\n",

	//3
	"The output file did not open\n",

	//4
	"Out of memmory\n",

	//5
	"Unavailable character\n",

	//6
	"The balance of brackets is broken\n",

	//7
	"Integer overflow occurred\n",
	
	//8
	"There has been a division by zero\n"
};



typedef struct Operation {
	int priority;
	char operation;
	char *name;
}Operation;


void CreateOperation(const char operation, const int priority,
	 Operation** Arrops, unsigned int *countops){
	Operation* temp = (Operation*)malloc(sizeof(Operation));
	temp->priority = priority;
	temp->operation = operation;
	Arrops[*countops] = temp;
	(*countops)++;
}

int comparison(const char leftoperation, const char rightoperation,
	 Operation **Arrops, const unsigned int countops){
	int leftpriority = -1, rightpriority = -1;
	unsigned int i;
	for (i = 0; i < countops; i++) {
		if (leftoperation == Arrops[i]->operation) leftpriority = Arrops[i]->priority;
		if (rightoperation == Arrops[i]->operation) rightpriority = Arrops[i]->priority;
	}
	if (leftpriority < rightpriority) return -1;
	else if (leftpriority > rightpriority) return 1;
	else return 0;
}



typedef struct Stack_c{
	char data;
	struct Stack_c* next;
} Stack_c;

void push(Stack_c** head, char data) {
	Stack_c* tmp = (Stack_c*)malloc(sizeof(Stack_c));
	if (tmp == NULL) exit(STACK_OVERFLOW);
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
}


char popd(Stack_c** head) {
	Stack_c* out;
	char data;
	if (*head == NULL) exit(STACK_UNDERFLOW);
	out = *head;
	*head = (*head)->next;
	data = out->data;
	free(out);
	return data;
}

int Re_recording(FILE* postfix_expression, Stack_c* head,
	char *buf) {
	char *b = buf + strlen(buf);
	while (head) {
		if (head->data == '(') {
			error(ERROR_BRACKETS, postfix_expression);
			return 1;
		}
		*b++ = ' ';
		*b++ = head->data;
		*b = 0;
		//*b = 0;
		head = head->next;
	}

	return 0;
}

//______________________________________________________
typedef struct Stack_i {
	int data;
	struct Stack_i* next;
} Stack_i;

void pushi(Stack_i** head, int data) {
	Stack_i* tmp = (Stack_i*)malloc(sizeof(Stack_i));
	if (tmp == NULL) exit(STACK_OVERFLOW);
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
}


int popi(Stack_i** head) {
	Stack_i* out;
	int data;
	if (*head == NULL) exit(STACK_UNDERFLOW);
	out = *head;
	*head = (*head)->next;
	data = out->data;
	free(out);
	return data;
}

int peek(const Stack_i* head) {
	if (head == NULL) {
		exit(STACK_UNDERFLOW);
	}
	return head->data;
}


void error(int errorId, FILE* filetemp) {
	fprintf(filetemp, "Error #%d: %s ", errorId, errors[errorId - 1]);
	//system("pause");
	//exit(errorId);
}

void ErrorWithExit(int errorId, int num, ...) {
	va_list args;
	va_start(args, num);
	printf("\nError #%d: %s \n", errorId, errors[errorId - 1]);
	while (num--) fclose(va_arg(args, FILE*));
	va_end(args);
	system("pause");
	exit(errorId);

}