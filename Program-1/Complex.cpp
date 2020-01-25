/*
 * Complex.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Quan Nghiem
 */
#include <iostream>
#include "Complex.h"
using namespace std;
//default constructor

Complex::Complex(double r, double i) {
	real = r;
	imaginary = i;
}

//get the real value of a complex number. Return a double value.
double Complex::getReal() {
	return real;
}
//get the imaginary value of a complex number. Return a double value.
double Complex::getImaginary() {
	return imaginary;
}
//return the conjugate of the complex number called by this method.
Complex Complex::conjugate() {
	Complex result;
	result.real = this->real;
	result.imaginary = -(this->imaginary);

	return result;
}
//add the complex number prior to the operator with the complex number after it.
Complex Complex::operator+(const Complex& complex2) {
	Complex result;
	result.real = this->real + complex2.real;
	result.imaginary = this->imaginary + complex2.imaginary;

	return result;
}
//change the value of the first complex number by adding it with the complex number after the operator.
Complex& Complex::operator+=(const Complex& complex2) {
	*this = *this + complex2;
	return *this;
}
//subtract the complex number prior to the operator with the complex number after it.
Complex Complex::operator-(const Complex& complex2) {
	Complex result;
	result.real = this->real - complex2.real;
	result.imaginary = this->imaginary - complex2.imaginary;

	return result;
}
//change the value of the first complex number by subtracting it with the complex number after the operator.
Complex& Complex::operator-=(const Complex& complex2) {
	*this = *this - complex2;
	return *this;
}
//multiply the complex number prior to the operator with the complex number after it.
Complex Complex::operator*(const Complex& complex2) {
	Complex result;
	result.real = (this->real * complex2.real)
			- (this->imaginary * complex2.imaginary);
	result.imaginary = (this->real * complex2.imaginary)
			+ (this->imaginary * complex2.real);

	return result;
}
//multiply the complex number prior to the operator with the integer after it.
Complex Complex::operator*(const int& a) {
	Complex result;
	result.real = (this->real * a);
	result.imaginary = (this->imaginary * a);

	return result;
}
//change the value of the first complex number by multiplying it with the complex number after the operator.
Complex& Complex::operator*=(const Complex& complex2) {
	*this = *this * complex2;
	return *this;
}
//divide the complex number prior to the operator with the complex number after it.
Complex Complex::operator/(const Complex& complex2) {
	if (complex2.real == 0 && complex2.imaginary == 0) {
		cout << "Divided by zero" << endl;
		return *this;
	}
	Complex result;
	result.real = (this->real * complex2.real
			+ this->imaginary * complex2.imaginary)
			/ (complex2.real * complex2.real
					+ complex2.imaginary * complex2.imaginary);
	result.imaginary = (this->real * complex2.imaginary
			- this->imaginary * complex2.real)
			/ (complex2.real * complex2.real
					+ complex2.imaginary * complex2.imaginary);

	return result;
}
//divide the complex number prior to the operator with the integer after it.
Complex Complex::operator/(const int& a) {
	if (a == 0) {
		cout << "Divided by zero" << endl;
		return *this;
	}
	Complex result;
	result.real = (this->real / a);
	result.imaginary = (this->imaginary / a);

	return result;
}
//change the value of the first complex number by dividing it with the complex number after the operator.
Complex& Complex::operator/=(const Complex& complex2) {
	*this = *this / complex2;
	return *this;
}
//return true if the first complex number is equal to the second complex number
bool Complex::operator==(Complex & complex2) const {
	return (this->real == complex2.real && this->imaginary == complex2.imaginary);
}
//return true if the first complex number is not equal to the second complex number
bool Complex::operator!=(Complex & complex2) const {
	return !(this->real == complex2.real
			&& this->imaginary == complex2.imaginary);
}
//prompt the user to enter real and imaginary value for the complex number
istream& operator>>(istream &in, Complex& input) {
	cout << "Enter value for real." << endl;
	in >> input.real;
	cout << "Enter value for imaginary." << endl;
	in >> input.imaginary;
	return in;
}
//print out the value of the complex number
ostream& operator<<(ostream& out, const Complex & output) {
	if (!(output.imaginary != 0 && output.real == 0)) {
		out << output.real;
	}
	if (output.imaginary != 0.0) {
		if (output.imaginary < 0) {
			out << " - ";
			if (output.imaginary != -1) {
				out << -output.imaginary;
			}
		} else {
			if (output.real != 0) {
				out << " + ";
			}
			if (output.imaginary != 1) {
				out << output.imaginary;
			}
		}
		out << 'i';
	}
	return out;
}
