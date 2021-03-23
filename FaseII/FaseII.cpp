#include <iostream>
#include "Regresion.h"

using std::cout;
using std::endl;

//___________________________________________________________________________
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include "plplot\plstream.h"
using namespace std;
const int NSIZE = 101;
void test_plplot() {
    PLFLT x[NSIZE], y[NSIZE];
    PLFLT xmin = 0., xmax = 1., ymin = 0., ymax = 100.;
    int   i;
    for (i = 0; i < NSIZE; i++) {
        x[i] = (PLFLT)(i) / (PLFLT)(NSIZE - 1);
        y[i] = ymax * x[i] * x[i];
    }
    auto pls = new plstream();
    plsdev("wingcc");
    pls->init();
    pls->env(xmin, xmax, ymin, ymax, 0, 0);
    pls->lab("x", "y=100 x#u2#d", "Simple PLplot demo of a 2D line plot");
    pls->line(NSIZE, x, y);
    delete pls;
}
//___________________________________________________________________________


int main(){
	constexpr int arr_size = 5;
	int* X = new int[arr_size] {1,2,6,4,5};
	int* Y = new int[arr_size] {5,2,3,4,5};

	Result resultCpp = regresionCpp(X, Y, arr_size);
	cout <<"Recta Regresion en cpp-> m="<<resultCpp.m<<", n="<<resultCpp.n<< endl;

	Result resultx86 = regresionx86(X, Y, arr_size);
	cout <<"Recta Regresion en x86-> m="<<resultx86.m<<", n="<<resultx86.n<< endl;

    test_plplot();
	return 0;
}
