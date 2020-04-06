#include "Stack_and_errors.h"
#define COUNT_OPERATION 6
#define IS_OPERATOR(c) (c == '-' || c == '+' || c == '/' || c == '*' || c == '%' || c == '^')
Operation **Arrops = (Operation **)malloc(sizeof(Operation*) * COUNT_OPERATION);
unsigned int countops = 0;



int main(int argc, char* argv[]) {
	FILE* fin, *fout;
	unsigned valuebuf = 2, positiondigit = 2;
	char* buf = (char*)malloc(1 << valuebuf), *pb = buf;
	Stack* headop = NULL;
	char c, *ph;
	CreateOperation('-', 1, Arrops, &countops);
	CreateOperation('+', 1, Arrops, &countops);
	CreateOperation('/', 2, Arrops, &countops);
	CreateOperation('*', 2, Arrops, &countops);
	CreateOperation('%', 2, Arrops, &countops);
	CreateOperation('^', 3, Arrops, &countops);
	if (argc < 2) error(FEW_ARGUMENTS);
	if (!(fin = fopen(argv[1], "r"))) error(FIN_NO_OPEN);
	if (!(fout = fopen(argv[2], "w"))) {
		fclose(fin);
		error(FOUT_NO_OPEN);
	}
	while (((c = fgetc(fin)) != EOF)) {
		if (!IS_OPERATOR(c) && c != ')' && c != '(' && !isdigit(c) && !isspace(c)) error(UNAVAILABLE_CHARACTER);
		if (isspace(c)) continue;
		else if (isdigit(c)) {
			printf("%c", c);
			positiondigit = 0;
			continue;
		}
		else if (positiondigit == 1 ) positiondigit = 2;
		else if (positiondigit == 0) {
			printf(" ");
			positiondigit = 1;
		}

		if (c == '(') push(&headop, c);
		else if (c == ')') {
			if (positiondigit == 1) error(ERROR_BRACKETS);
			if (headop == NULL) error(ERROR_BRACKETS);
			positiondigit = 0;
			while (headop->data != '(') {
				//*pb++ = popd(&headop);
				printf("%c ", popd(&headop));
				if (headop == NULL) error(ERROR_BRACKETS);
			}
			popd(&headop);
		}
		else if (headop == NULL || headop->data == '(') {
			if (positiondigit == 2) error(ERROR_BRACKETS);
			push(&headop, c);
		}
		else if (comparison(c, headop->data, Arrops, countops) == 1) push(&headop, c);
		else {
			while (headop->data != '(') {
					printf("%c ", popd(&headop));
					if (headop == NULL) break;
					if (comparison(c, headop->data, Arrops, countops) == 1) break;
			}
			push(&headop, c);
		}

	}
	printStack(headop);
}