#include "Fa 5.1(v.1).h";
const int GCOUNT  = 50000;

SqMatrix foo()
{
	SqMatrix foo;
	return foo;
}
int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	//Lvalue и Rvalue


	

	SqMatrix obj1;
	//std::cout << obj1 << "\n___________\n";
	//SqMatrix obj2 = obj1;//инициализация при объявлении
	//obj2 = obj1;
	obj1 = foo();
	//std::cout << obj2 << "\n___________\n";
	//Конст
	//const int ArrSize = 3;
	//const char* text1 = "Matrix1";

	//char* name1 = new char[strlen(text1) + 1];

	//strcpy(name1, text1);

	//double** arr = new double* [ArrSize];
	//for (int i = 0; i < ArrSize; i++) {
	//	arr[i] = new double[ArrSize];
	//	for (int j = 0; j < ArrSize; j++) arr[i][j] = i * (j + 1) + j + 1;
	//}

	//SqMatrix matrix1(name1, ArrSize, arr);

	//SqMatrix matrix2;



	//matrix1.SetMatrix();
	//
	//matrix2 = matrix1;
	//matrix2.SetMatrix();

	//std::cout << "\n~~~~Bool\n";
	//std::cout << "matrix2 == matrix1 ? --- " << (matrix2 == matrix1)<< std::endl;
	//std::cout << "matrix2 != matrix1 ? --- " << (matrix2 != matrix1) << std::endl;

	//std::cout << std::endl;
	//clock_t start_time;// начальное время
	//clock_t end_time; // конечное время
	//auto someFunc1
	//{
	//	[](SqMatrix) 
	//{ 		
	//	//std::cout << "~~~Вовзрат по значению\n\n";
	//	SqMatrix temp;
	//	return temp; 
	//}
	//};

	//std::cout << "~~~Передача аргумента по значению. Вызов конструктора копирования\n\n";
	//start_time = clock();
	//for(int i = 0; i < GCOUNT; i++)
	//{
	//	someFunc1(matrix2);
	//}
	//end_time = clock();
	//std::cout << "\tВремя = " << double(start_time - end_time)/CLOCKS_PER_SEC <<" (с) \n";
	//auto someFunc2
	//{
	//	[](SqMatrix&)
	//{
	//	//std::cout << "~~~Вовзрат по значению\n\n";
	//	SqMatrix temp;
	//	return temp;
	//}
	//};


	//std::cout << "\n~~~Передача аргумента по ссылке\n\n";
	//start_time = clock();
	//for (int i = 0; i < GCOUNT; i++)
	//{
	//	someFunc2(matrix2);
	//}
	//end_time = clock();

	//std::cout << "\tВремя = " << double(start_time - end_time)/ CLOCKS_PER_SEC << " (с) \n";
	//std::cout << "~~~Сравнение времени ";
	/////////////////////////////////////

	//std::cout << "\n\n~~~Арифметика \n";

	//SqMatrix inc1(3), inc2(3), inc(3);
	//try
	//{
	//	inc1.SetMatrix();
	//	inc2.SetMatrix();

	//	std::cout << "inc = inc1 + inc2 \n";
	//	inc = inc1 + inc2;
	//	inc.SetMatrix();

	//	std::cout << "inc = inc1 - inc2  \n";
	//	inc = inc1 - inc2;
	//	inc.SetMatrix();

	//	std::cout << "inc1 * inc2 = \n";
	//	//inc = inc1 * inc2;
	//	(inc1 + inc2).SetMatrix();
	//}
	//catch(int num)
	//{
	//	switch (num)
	//	{
	//	case -1:
	//		std::cout << "Ошибка! Складывать матрицы можно только одного размера!";
	//		break;
	//	case -2:
	//		std::cout << "Ошибка! Вычитать матрицы можно только одного размера!";
	//		break;
	//	case -3:
	//		std::cout << "Ошибка! Умножать матрицы можно только одного размера!";
	//		break;
	//	default:
	//		break;
	//	}

	//}

	//SqMatrix temp(4);

	//std::cout << "Действия над матрицами\n\n";
	//std::cout << temp;
	//
	//std::cout << "Определитель = " << getDeterminant(temp) << std::endl;
	//std::cout << "Транспонированная матрица:\n" << Transpose(temp);
	//std::cout << "Обратная матрица:\n" << Reverse(temp);
	//std::cout << "След матрицы = " << getTrace(temp) << std::endl;
	//std::cout << "Вычисление матричной экспоненты:\n" << exp(temp, 10) << std::endl;



	//double** arr2 = new double* [ArrSize];
	//for (int i = 0; i < ArrSize; i++) {
	//	arr2[i] = new double[ArrSize];
	//	for (int j = 0; j < ArrSize; j++) j == 0 ? arr2[i][j] = i + 1 : arr2[i][j] = 0;
	//}
	//char* objname = new char[10]{ "123" };
	//SqMatrix obj1(3), obj2(objname, ArrSize, arr2);
	//std::cout << "Решение СЛАУ\n\tA * X = C\n\tX = A^-1 * C\nA = \n"<< obj1 
	//	<< "C = \n" << obj2 << "X = \n" << Reverse(obj1) * obj2;
	std::cout << "\n______________________________________________\n";
}