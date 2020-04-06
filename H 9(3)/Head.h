struct Operation;
void CreateOperation(const char, const int, Operation**, unsigned int*);
int comparison(const char, const char, Operation, const unsigned int);

struct Stack_c;
void push(Stack_c**, char);
char popd(Stack_c**);
int Re_recording(FILE*, Stack_c*, char*);

struct Stack_i;
void pushi(Stack_i**, int);
int popi(Stack_i**);
int peek(const Stack_i*);

void error(int errorId, FILE*);
void ErrorWithExit(int, int, ...);