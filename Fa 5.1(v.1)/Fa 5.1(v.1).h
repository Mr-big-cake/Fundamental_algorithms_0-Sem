#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>


//By default:
const int ConstSizeArr = 5;
const int MaxNumber = 5;

class SqMatrix {

	friend double DetSolut(SqMatrix&);
	friend double getDeterminant(const SqMatrix&);
	friend SqMatrix MatrixOfMinors(SqMatrix&);
	friend SqMatrix Reverse(const SqMatrix& matrix);
	friend SqMatrix Transpose(const SqMatrix& matrix);
	friend double getTrace(const SqMatrix& matrix);
	friend SqMatrix exp(const SqMatrix& matrix, int n);


private:
	
	double** matrix;
	char* name;
	int size;
	static unsigned Number;
public:

	~SqMatrix();

	SqMatrix(char*, int, double**);
	SqMatrix(int);
	SqMatrix();// SqMatrix obj, obj2();

	SqMatrix(const SqMatrix &); // SqMatrix  
	//SqMatrix(SqMatrix&&);

	SqMatrix& operator = (const SqMatrix&);
	SqMatrix& operator = (SqMatrix&&);


	SqMatrix& operator +=(const SqMatrix&);
	SqMatrix& operator -=(const SqMatrix&);
	SqMatrix& operator *=(const SqMatrix&);
	SqMatrix& operator *=(const double&);
	SqMatrix& operator /=(const double&);

	SqMatrix operator +(const SqMatrix&);
	SqMatrix operator -(const SqMatrix&);
	SqMatrix operator *(const SqMatrix&);
	SqMatrix operator *(const double&);
	SqMatrix operator /(const double&);

	friend std::ostream& operator<<(std::ostream& out, const SqMatrix& matrix);
	friend std::istream& operator>>(std::istream& in, SqMatrix& matrix);

	friend bool operator ==(const SqMatrix&, const SqMatrix&);
	friend bool operator !=(const SqMatrix&, const SqMatrix&);


	void SetMatrix();

};

