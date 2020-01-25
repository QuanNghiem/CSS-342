#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>
using namespace std;

//-----------Complex-----------//

class Complex {
	friend istream & operator>>(istream &, Complex &); //overloading input stream operator
	friend ostream & operator<<(ostream &, const Complex &); //overloading output stream operator

public:
	Complex(double = 0, double = 0); //constructor

	//Math operators
	Complex operator+(const Complex &);
	Complex operator-(const Complex &);
	Complex operator*(const Complex &);
	Complex operator*(const int&);
	Complex operator/(const Complex &);
	Complex operator/(const int&);

	//Comparison
	bool operator==(Complex &) const;
	bool operator!=(Complex &) const;

	//Assignment
	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator/=(const Complex&);

	//Conjugate
	Complex conjugate ();

	//Getter
	double getReal();
	double getImaginary();

private:
	double real;
	double imaginary;
};

#endif
