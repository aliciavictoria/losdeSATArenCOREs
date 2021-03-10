#include "Regresion.h"

Result regresionx86(int X[], int Y[], int arr_size){
    int suma_x, suma_y, suma_xy, suma_xx;
    float media, var_x, cov_xy;
    suma_x = suma_y = suma_xy = suma_xx = media = var_x = cov_xy = 0;

    Result result;

    __asm{
        xor edx, edx            ;imul purposes
        xor esi, esi            ;se usara como cont del arr de puntos
        mov edi, arr_size       ;se usara como max iteraciones en los arr de puntos


        ;recorrer arr de puntos
        for_point:
            cmp esi, edi
            je calc             ;saltar si esi==edi

            mov ebx, X          ;item i de X
            mov ebx, [ebx+esi*4]    
            mov ecx, Y          ;item i de Y
            mov ecx, [ecx+esi*4]

                                ;suma_x += X[i];
            mov eax, suma_x
            add eax, ebx
            mov suma_x, eax

                                ;suma_y += Y[i];
            mov eax, suma_y
            add eax, ecx
            mov suma_y, eax

                                ;suma_xx += X[i] * X[i];
            mov eax, ebx
            imul eax
            add suma_xx, eax

                                ;suma_xy += X[i] * Y[i];
            mov eax, ebx
            imul ecx
            add suma_xy, eax

            add esi, 1
            jmp for_point


        calc:
                                ;media_x
            fld suma_x
            fdiv arr_size
            fst media

                                ;media_x*media_x
            fmul media
            fstp var_x
                                ;var_x = (suma_xx/arr_size) - (media_x*media_x)
            fld suma_xx
            fdiv arr_size
            fsub var_x
            fstp var_x

                                ;media_y*media_x
            fld suma_y
            fdiv arr_size
            fmul media
            fstp cov_xy
                                ;cov_x = (suma_xy/arr_size) - (media_x*media_y)
            fld suma_xy
            fdiv arr_size
            fsub cov_xy
            fst cov_xy

                                ;m = cov_xy / var_x
            fdiv var_x
            fstp result.m

                                ;(-media_x)
            fldz
            fsub media
                                ;((cov_xy/var_x)*(-media_x))
            fmul result.m
                                ;media_y
            fld suma_y
            fdiv arr_size
            fstp media
                                ;n = ((cov_xy/var_x)*(-media_x)) + media_y
            fadd media
            fstp result.n
    }

    return result;
}