#include "Implementation.cpp"
#pragma warning (disable: 4703)
#define INT_ZEROS 9
#define COUNT_OPERATION 6
#define COUNT_FILES 3
#define SIZE_NAME 5
#define IS_OPERATOR(c) (c == '-' || c == '+' || c == '/' || c == '*' || c == '%' || c == '^')


Operation **Arrops = (Operation **)malloc(sizeof(Operation*) * COUNT_OPERATION);
unsigned int countops = 0;

int commitcom(int A, int B, int opcount, unsigned* flagoverflow, unsigned* flagdivision0)
{
	switch (opcount) {
	case SUBTRACTION:
		if (A < INT_MIN + B) {
			*flagoverflow = 1;
			return 0;
		}
		return (A - B);
	case ADDITION:
		if (A > INT_MAX - B) {
			*flagoverflow = 1;
			return 0;
		}
		return (A + B);
	case DIVISION:
		if (B == 0) {
			*flagdivision0 = 1;
			return 0;
		}
		return (A / B);
	case MULTIPLICATION:
		if (A > INT_MAX / B) {
			*flagoverflow = 1;
			return 0;
		}
		return (A * B);
	case TAKING_THE_REMAINDER_FROM_DIVIDING:
		return (A % B);
	case POW:
		if (!B) return 1;
		else if (B < 0 || !A) return 0;
		while (--B) {
			if (A > INT_MAX / A) {
				*flagoverflow = 1;
				return 0;
			}
			A *= A;
		}
		
		return A;
	}
}

int main(int argc, char* argv[]) {
	FILE* fin, * tempfile, *errorfile;

	unsigned positiondigit, flagspace, emptiness;
	unsigned countdigit = 0;
	unsigned flag_error = 0;
	unsigned flagoverflow, flagdivision0;
	unsigned flagcreatefile;
	//unsigned flagfirstchar;

	Stack_c* headop = NULL;
	Stack_i* headargs = NULL;

	char c = 0, cf = 0;
	char buf[BUFSIZ] , *b = buf;
	*b = 0;
	char* tempname = (char*)malloc(SIZE_NAME + 1);

	unsigned labelfile = 2; 
	unsigned labelstr = 1;

	char tempop; // производит операцию 
	int tempvalue; // помещает в стек аргументов полученое значение после произведение операции
	int tempargs = -1; //используется для занесения в стек аргументов числа из tempfile

	CreateOperation('-', 1, Arrops, &countops);
	CreateOperation('+', 1, Arrops, &countops);
	CreateOperation('/', 2, Arrops, &countops);
	CreateOperation('*', 2, Arrops, &countops);
	CreateOperation('%', 2, Arrops, &countops);
	CreateOperation('^', 3, Arrops, &countops);

	if (argc < COUNT_FILES + 1) ErrorWithExit(FEW_ARGUMENTS, 0);
	
	while (labelfile < argc) {
		flagcreatefile = 0;
		c = 0, cf = 0;
		labelstr = 1;
		if (!(tempfile = fopen(argv[1], "w"))) ErrorWithExit(FOUT_NO_OPEN, 0);
		if (!(fin = fopen(argv[labelfile], "r"))) ErrorWithExit(FIN_NO_OPEN, 1, tempfile);
		printf("___________________________\n	FILE #%d <%s>: \n\n", labelfile - 1, argv[labelfile]);
		while (c != EOF) {
			positiondigit = 2;// расстояние до ближайшей цифры. positiondigit = 2 это значит растояние 2+
			emptiness = 1; // пробелы перед выражением. 1 - когда выражение еще не началось в строчке 
			flagspace = 0;// 1 - если предыдущий символ является любым пробелом
			countdigit = 0;// число десяток отдельного числа. Первая проверка на переполнение 
			flag_error = 0;
			headop = NULL;
			b = buf;
			*b = 0;
			while (((c = fgetc(fin)) != EOF) && c != '\n') {
				if (!IS_OPERATOR(c) && c != ')' && c != '(' && !isdigit(c) && !isspace(c)) {
					error(UNAVAILABLE_CHARACTER, tempfile);
					while (c != EOF && c != '\n')
						c = fgetc(fin);
					flag_error = 1;
					break;
				}
				if (isspace(c)) {
					flagspace = 1;
					countdigit = 0;
					continue;
				}
				else if (isdigit(c)) {
					if (positiondigit == 0 && flagspace == 1) {
						error(UNAVAILABLE_CHARACTER, tempfile);
						while (c != EOF && c != '\n')
							c = fgetc(fin);
						flag_error = 1;
						break;
					}
					*b++ = c;
					*b = 0;
					//fprintf(tempfile, "%c", c);
					if (++countdigit > INT_ZEROS) {
						error(ERROR_INT_OVERFLOW, tempfile);
						while (c != EOF && c != '\n')
							c = fgetc(fin);
						flag_error = 1;
						break;
					}
					positiondigit = 0;
					flagspace = 0;
					emptiness = 0;
					continue;
				}
				else if (positiondigit == 1 && c != ')') {
					positiondigit = 2;
					flagspace = 0;
				}
				else if (positiondigit == 0) {
					*b++ = ' ';
					*b = 0;
					//fprintf(tempfile, " ");
					if (c != ')')positiondigit = 1;
					flagspace = 0;
				}
				emptiness = 0;
				countdigit = 0;

				if (c == '(') {
					if (positiondigit != 2) {
						error(UNAVAILABLE_CHARACTER, tempfile);
						while (c != EOF && c != '\n')
							c = fgetc(fin);
						flag_error = 1;
						break;
					}
					push(&headop, c);
				}
				else if (c == ')') {
					if (positiondigit == 1) {
						error(UNAVAILABLE_CHARACTER, tempfile);
						while (c != EOF && c != '\n')
							c = fgetc(fin);
						flag_error = 1;
						break;
					}
					if (headop == NULL) {
						error(ERROR_BRACKETS, tempfile);
						while (c != EOF && c != '\n')
							c = fgetc(fin);
						flag_error = 1;
						break;
					}
					flagspace = 1;
					
					while (headop->data != '(') {
						//*pb++ = popd(&headop);
						*b++ = popd(&headop);
						*b = 0;
						//fprintf(tempfile, "%c ", popd(&headop));
						if (headop == NULL) {
							error(ERROR_BRACKETS, tempfile);
							while (c != EOF && c != '\n')
								c = fgetc(fin);
							flag_error = 1;
							break;
						}
					}
					if (flag_error)
						break;
					popd(&headop);
				} //c == ')' ?
				else if (positiondigit == 2) {
					error(UNAVAILABLE_CHARACTER, tempfile);
					while (c != EOF && c != '\n')
						c = fgetc(fin);
					flag_error = 1;
					break;
				}
				else if (headop == NULL || headop->data == '(')
					push(&headop, c);
				else if (comparison(c, headop->data, Arrops, countops) == 1)
					push(&headop, c);
				else {
					while (headop->data != '(') {
						*b++ = popd(&headop);
						*b = 0;
						//fprintf(tempfile, "%c ", popd(&headop));
						if (headop == NULL) break;
						if (comparison(c, headop->data, Arrops, countops) == 1) break;
					}
					push(&headop, c);
				}

			}//--- LVL 3 ---//
			if (flag_error) 
				continue;
			else if (positiondigit != 0 && emptiness == 0) {
				if (headop != NULL) {
					if (IS_OPERATOR(headop->data))
						error(UNAVAILABLE_CHARACTER, tempfile);
					else if (headop->data == '(') {
						error(ERROR_BRACKETS, tempfile);
						//printf("HEEEEELP");
					}
					//fprintf(tempfile, "<>");
					continue;
				}
			}
			//else if (headop != NULL) {
			//	if (headop->data == '(') 
			//		error(1, tempfile);
			//	continue;
			//}
			else {
				*b = 0;
				if (Re_recording(tempfile, headop, buf)) continue;
				fprintf(tempfile, "%s", buf);
				fprintf(tempfile, " \n");
			}
		}//--- LVL 2 ---//
		fclose(tempfile);
		fclose(fin);
		if (!(tempfile = fopen(argv[1], "r"))) ErrorWithExit(FIN_NO_OPEN, 0);
		if (!(fin = fopen(argv[labelfile], "r"))) ErrorWithExit(FIN_NO_OPEN, 1, tempfile);
		printf("#%d: ", labelstr);
		emptiness = 0;
		while (1) {
			if (isspace(c)) {
				c = fgetc(fin);
				emptiness = 1;
			}
			else break;
		}
		if (emptiness) {
			printf("%c", c);
			emptiness = 0;
		}
		while (1) {
			cf = fgetc(tempfile);
			if (isdigit(cf)) {
				if (tempargs == -1) tempargs = 0;
				tempargs = tempargs * 10 + cf - '0';
				//printf("tempargs = %d \n", tempargs);
			}
			else if (cf == ' ' && tempargs != -1) {

				pushi(&headargs, tempargs);
				//printf("headargs->data = %d\n", headargs->data);
				tempargs = -1;
			}
			else if (IS_OPERATOR(cf)) {
				if (cf == '-') tempop = SUBTRACTION;
				else if (cf == '+') tempop = ADDITION;
				else if (cf == '/') tempop = DIVISION;
				else if (cf == '*') tempop = MULTIPLICATION;
				else if (cf == '%') tempop = TAKING_THE_REMAINDER_FROM_DIVIDING;
				else if (cf == '^') tempop = POW;
				flagoverflow = 0;
				flagdivision0 = 0;
				tempvalue = commitcom(popi(&headargs), popi(&headargs), tempop,
					&flagoverflow, &flagdivision0);
				if (flagoverflow || flagdivision0) {
					while (((c = fgetc(fin)) != EOF) && c != '\n') printf("%c", c);
					printf(" - ");
					if(flagoverflow)
						printf("Error #%d: %s", ERROR_INT_OVERFLOW, errors[ERROR_INT_OVERFLOW - 1]);
					if(flagdivision0)
						printf("Error #%d: %s", ERROR_DIVISION_BY_ZERO, errors[ERROR_DIVISION_BY_ZERO - 1]);
					printf("#%d: ", ++labelstr);
					while ((cf = fgetc(tempfile)) != EOF && cf != '\n');
				}
				pushi(&headargs, tempvalue);

			}
			else if (cf == '#') {
				cf = fgetc(tempfile);

				if (cf == ERROR_BRACKETS + '0') {
					if (!flagcreatefile) {
						flagcreatefile = 1;
						tempname = (char*)realloc(tempname, SIZE_NAME + sizeof(argv[labelfile]) + 1);
						*tempname = 0;
						strcat(tempname, "error");
						strcat(tempname, argv[labelfile]);
						//printf("AAAAAAAAAAAAAAAAAAAAAAAAAA <%s>", tempname);
						errorfile = fopen(tempname, "w");
					}
					//tempname = (char*)"error";
					
					fprintf(errorfile, "%d: %c", labelstr, c);
					while (((c = fgetc(fin)) != EOF) && c != '\n') {
						printf("%c", c);
						fprintf(errorfile, "%c", c);
					}
					fprintf(errorfile,"\n");
					printf(" - Error #");
					do {
						printf("%c", cf);
					} while ((cf = fgetc(tempfile)) != EOF && cf != '\n');
					printf("\n");
					printf("#%d: ", ++labelstr);
				}
				else {
					while (((c = fgetc(fin)) != EOF) && c != '\n') printf("%c", c);
					printf(" - Error #");
					do {
						printf("%c", cf);
					} while ((cf = fgetc(tempfile)) != EOF && cf != '\n');
					printf("\n");
					printf("#%d: ", ++labelstr);
				}
			}
			else if (cf == '\n' || cf == EOF) {
				if (headargs != NULL) {
					while (((c = fgetc(fin)) != EOF) && c != '\n') printf("%c", c);
					printf(" = %d\n", popi(&headargs));
					printf("#%d: ", ++labelstr);
					headargs = NULL;
				}
				while (1) {
					if (isspace(c)) {
						c = fgetc(fin);
						emptiness = 1;
					}
					else break;
				}
				if (emptiness) {
					printf("%c", c);
					emptiness = 0;
				}
				if (cf == EOF) break;

			}
		}//--- LVL 2 ---//
		labelfile++;
		fclose(errorfile);
		printf("Expressions in the file were successfully checked and calculated\n");
	}//--- LVL 1 ---//
	
}