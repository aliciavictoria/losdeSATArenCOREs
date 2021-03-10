#include <iostream>
#include "RegresionCpp.h"

using std::cout;
using std::endl;

int main(){
	int size = 5;
	float X[] = { 1,2,3,4,5 };
	float Y[] = { 1,2,3,4,5 };

	Result resultCpp = regresionCpp(X, Y, size);

	cout << "Recta Regresion -> m=" << resultCpp.m << ", n=" << resultCpp.n << endl;

	return 0;
}