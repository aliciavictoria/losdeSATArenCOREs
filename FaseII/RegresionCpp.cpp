#include "RegresionCpp.h"

Result regresionCpp(const float X[], const float Y[], int size){
    float suma_x, suma_y, suma_xy, suma_xx;
    suma_x = suma_y = suma_xy = suma_xx = 0;

    for (int i=0; i < size; i++){
        suma_xy += X[i] * Y[i];
        suma_xx += X[i] * Y[i];
        suma_x += X[i];
        suma_y += Y[i];
    }

    float media_x = suma_x / size;
    float media_y = suma_y / size;

    float var_x = (suma_xx/size) - (media_x*media_x);
    float cov_xy = (suma_xy/size) - (media_x*media_y);

    Result result;
    result.m = cov_xy / var_x;
    result.n = ((cov_xy/var_x)*(-media_x)) + media_y;

    return result;
}