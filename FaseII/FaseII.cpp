#include <iostream>
#include "Regresion.h"

using std::cout;
using std::endl;

int main(){
	constexpr int arr_size = 5;
	int* X = new int[arr_size] {1,2,3,4,5};
	int* Y = new int[arr_size] {1,2,3,4,5};

	Result resultCpp = regresionCpp(X, Y, arr_size);
	cout <<"Recta Regresion en cpp-> m="<<resultCpp.m<<", n="<<resultCpp.n<< endl;

	Result resultx86 = regresionx86(X, Y, arr_size);
	cout <<"Recta Regresion en x86-> m="<<resultx86.m<<", n="<<resultx86.n<< endl;

	return 0;
}