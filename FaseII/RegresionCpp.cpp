#include "Regresion.h"

Result regresionCpp(int X[], int Y[], int arr_size){
    int suma_x, suma_y, suma_xy, suma_xx;
    suma_x = suma_y = suma_xy = suma_xx = 0;

    for (int i=0; i < arr_size; i++){
        suma_x += X[i];
        suma_y += Y[i];
        suma_xx += X[i] * X[i];
        suma_xy += X[i] * Y[i];        
    }

    float media_x = suma_x / (float)arr_size;
    float media_y = suma_y / (float)arr_size;

    float var_x = (suma_xx/arr_size) - (media_x*media_x);
    float cov_xy = (suma_xy/arr_size) - (media_x*media_y);

    Result result;
    result.m = cov_xy / var_x;
    result.n = ((cov_xy/var_x)*(-media_x)) + media_y;

    return result;
}