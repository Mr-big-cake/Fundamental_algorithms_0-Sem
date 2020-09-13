#include "Fa 5.1(v.1).h"

using namespace std;

SqMatrix::SqMatrix(char* name, int size, double** matrix) : name{ name }, size{ size }, matrix{ matrix }
{
	//cout << "*Конструктор: " << name << endl;
}

SqMatrix::~SqMatrix() {
	cout << "*Деструткор: ";
	name == nullptr ? cout << this << endl : cout << name << endl;
	if (name != nullptr)
		for (int i = 0; i < size; i++)
			delete[] matrix[i];
	delete[] matrix;

	delete[] name;
}

SqMatrix::SqMatrix(): SqMatrix(rand() % ConstSizeArr + 1)
{
	cout << "\t+ Конструктор по умолчанию: " << name << endl;
}

SqMatrix::SqMatrix(int Size)
{
	char* tmpName = new char[20];
	strcpy(tmpName, "RandName ");

	char temp[10];
	SqMatrix::Number++;
	_itoa(SqMatrix::Number, temp, 10);
	strcat(tmpName, temp);

	//int ArrSize = rand() % ConstSizeArr + 1;

	double** arr = new double* [Size];

	for (int i = 0; i < Size; i++) {
		arr[i] = new double[Size];
		for (int j = 0; j < Size; j++) arr[i][j] = rand() % 10;
	}


	name = { tmpName };
	size = { Size };
	matrix = { arr };
	//cout << "*Конструктор (int size): " << name << endl;
}

//Конструкторы перемещения и копирования
SqMatrix::SqMatrix(const SqMatrix& obj)
{
	
	double** arr = new double* [obj.size];
	for (int i = 0; i < obj.size; i++) {
		arr[i] = new double[obj.size];
		for (int j = 0; j < obj.size; j++)
			arr[i][j] = obj.matrix[i][j];
	}

	
	char* tmpName = new char[20];
	strcpy(tmpName, "RandName ");

	char temp[10];
	_itoa(++SqMatrix::Number, temp, 10);
	strcat(tmpName, temp);

	name = { tmpName };
	matrix = { arr };
	size = { obj.size };

	cout << "*Конструктор копирования: " << name << endl;

	//SetMatrix();
}

//SqMatrix::SqMatrix(SqMatrix&& obj) : name{obj.name}, matrix{obj.matrix}, size{obj.size}
//{
//	obj.name = nullptr;
//	obj.matrix = nullptr;
//	cout << "*Конструктор перемещения: " << name << endl;
//}

//	Действия с матрицами
double getDeterminant(const SqMatrix& obj)
{
	if (obj.size == 1) return obj.matrix[0][0];
	SqMatrix copyObj = obj;
	
	return DetSolut(copyObj);
}

SqMatrix Reverse(const SqMatrix& obj)
{
	double det = getDeterminant(obj);
	SqMatrix adj(obj);
	
	adj = Transpose(MatrixOfMinors(adj)) / det;
	return adj;
}

SqMatrix Transpose(const SqMatrix& matrix)
{
	SqMatrix result(matrix.size);
	for (int i = 0; i < matrix.size; ++i) {
		for (int j = 0; j < matrix.size; ++j) {
			result.matrix[i][j] = matrix.matrix[j][i];
		}
	}
	return result;
}

double getTrace(const SqMatrix& obj) {
	double result = 0;
	for (int i = 0; i < obj.size; ++i) {
		result += obj.matrix[i][i];
	}
	return result;
}

SqMatrix exp(const SqMatrix& obj, int n) {
	int d = 1;
	SqMatrix result = SqMatrix(obj.size);
	SqMatrix a = obj;
	for (int i = 0; i < obj.size; ++i) {
		result = result + a / d++;
		a *= obj;
	}

	return result;

}

// Операторы a = b
SqMatrix& SqMatrix::operator=(SqMatrix&& obj) 
{
	if (&obj == this) return *this;
	
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] name;

	matrix = { obj.matrix };
	name = { obj.name };
	size = { obj.size };

	obj.matrix = nullptr;
	obj.name = nullptr;
	
	cout << "*Опрератор присваивания пермещением: "<< name<< endl;
	return *this;
}

SqMatrix& SqMatrix::operator=(const SqMatrix& obj)
{
	if (&obj == this) return *this;
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;


	double** arr = new double* [obj.size];

	for (int i = 0; i < obj.size; i++) 
	{
		arr[i] = new double[obj.size];
		for (int j = 0; j < obj.size; j++) arr[i][j] = obj.matrix[i][j];
	}

	
	matrix = { arr };
	size = { obj.size };
	cout << "*Опрератор присваивания: " << name<< " = "<< obj.name << endl;
	return *this;
}

//Arithmetic
SqMatrix& SqMatrix::operator+=(const SqMatrix& right) {
	if (size != right.size) throw - 1;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] += right.matrix[i][j];
		}
	}

	return *this;
}

SqMatrix& SqMatrix::operator-=(const SqMatrix& right) {
	if (size != right.size) throw - 2;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] -= right.matrix[i][j];
		}
	}

	return *this;
}

SqMatrix& SqMatrix::operator*=(const SqMatrix& right) {
	if (size != right.size) throw - 3;

	double** arr = new double* [size];

	for (int i = 0; i < size; i++) {
		arr[i] = new double[size];
		for (int j = 0; j < size; j++)
			arr[i][j] = matrix[i][j];
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k) {
				arr[i][j] += this->matrix[i][k] * right.matrix[k][j];
			}
		}
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < size; i++)
		delete[] arr[i];
	delete[] arr;

	return *this;

}

SqMatrix& SqMatrix::operator*=(const double& right)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] *= right;
	return *this;
}

SqMatrix& SqMatrix::operator/=(const double& right)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] /= right;
	return *this;
}

SqMatrix SqMatrix::operator+(const SqMatrix& right) {

	SqMatrix tmp = *this;
	return (tmp += right);
}

SqMatrix SqMatrix::operator-(const SqMatrix& right) {
	SqMatrix tmp = *this;
	return tmp -= right;
}

SqMatrix SqMatrix::operator*(const SqMatrix& right) {
	SqMatrix tmp = *this;
	return tmp *= right;
}

SqMatrix SqMatrix::operator *(const double& right)
{
	SqMatrix tmp = *this;
	return tmp *= right;
}

SqMatrix SqMatrix::operator /(const double& right)
{
	SqMatrix tmp = *this;
	return tmp /= right;
}

//Операторы ввода, вывода
ostream& operator<<(ostream& out, const SqMatrix& obj)
{
	for (int i = 0; i < obj.size; i++) {
		for (int j = 0; j < obj.size; j++)
			out << obj.matrix[i][j] << " ";
		out << "\n";
	}
	return out;
}

istream& operator>>(std::istream& in, SqMatrix& obj)
{
	in >> obj.name;
	in >> obj.size;
	for (int i = 0; i < obj.size; i++)
		for (int j = 0; j < obj.size; j++)
			in >> obj.matrix[i][j];
	return in;
}

//Bool
bool operator==(const SqMatrix& left, const SqMatrix& right)
{
	if (right.size != left.size) return false;

	for (int i = 0; i < right.size; ++i) {
		for (int j = 0; j < right.size; ++j) {
			if (left.matrix[i][j] != right.matrix[i][j]) {
				return false;
			}
		}
	}

	return true;
}

bool operator!=(const SqMatrix& left, const SqMatrix& right)
{
	return !(left == right);
}

// Other
void SqMatrix::SetMatrix() {
	cout<<"___SetMatrix()___"<<endl <<"\tName :<"<< name<< ">"<< endl<< "\tSize = "<< size<< endl;
	cout << "\t";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cout << matrix[i][j] << " ";
		cout << "\n\t";
	}
	cout << endl;
}

double DetSolut(SqMatrix &arr)
{
	if (arr.size <= 1) return arr.matrix[0][0];

	double result{};


	for (int col = 0; col < arr.size; col++) 
	{
		SqMatrix temp(arr.size - 1);
		int label[2]{};
		for (int i = 0; i < arr.size; i++)
		{
			for (int j = 0; j < arr.size; j++)
			{
				if (i != 0 && j != col)
				{
					temp.matrix[label[0]][label[1]] = arr.matrix[i][j];
					label[1]++;
					if (label[1] == temp.size) {
						label[0]++;
						label[1] = {};
					}
				}
			}
		}
		result += pow(-1, col) * arr.matrix[0][col] * DetSolut(temp);
	}
	return result;
}

SqMatrix MatrixOfMinors(SqMatrix& arr)
{
	SqMatrix result(arr.size);
	SqMatrix temp(arr.size - 1);
	int sgn;
	int Rlabel[2]{};

	for (int row = 0; row < arr.size; row++)
	{
		for (int col = 0; col < arr.size; col++)
		{
			SqMatrix temp(arr.size - 1);
			int label[2]{};
			for (int i = 0; i < arr.size; i++)
			{
				for (int j = 0; j < arr.size; j++)
				{
					if (i != row && j != col)
					{
						temp.matrix[label[0]][label[1]] = arr.matrix[i][j];
						label[1]++;
						if (label[1] == temp.size) {
							label[0]++;
							label[1] = {};
						}
					}
				}
			}
			sgn = (((Rlabel[0] + Rlabel[1]) % 2 == 0) ? 1 : -1);
			result.matrix[Rlabel[0]][Rlabel[1]] = sgn * getDeterminant(temp);
			Rlabel[1]++;
			if (Rlabel[1] == result.size) 
			{
				Rlabel[0]++;
				Rlabel[1] = {};
			}
			
		}
	}
	return result;
}




unsigned SqMatrix::Number = {};
