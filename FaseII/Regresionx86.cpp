#include "Regresion.h"

Result regresionx86(int X[], int Y[], int arr_size){
    int suma_x, suma_y, suma_xy, suma_xx;
    suma_x = suma_y = suma_xy = suma_xx = 0;

    __asm{
        xor esi, esi            ;se usara como cont del arr de puntos
        mov edi, arr_size       ;se usara como max iteraciones en los arr de puntos


        ;recorrer arr de puntos
        for_point:
            cmp esi, edi
            je calc         ;saltar si esi==edi

            mov ebx, X
            mov ebx, [ebx+esi*4]    ;item i de X
            mov ecx, Y
            mov ecx, [ecx+esi*4]    ;item i de Y

            ;---suma_x += X[i];
            mov eax, suma_x
            add eax, ebx
            mov suma_x, eax

            ;---suma_y += Y[i];
            mov eax, suma_y
            add eax, ecx
            mov suma_y, eax

            ;---suma_xx += X[i] * X[i];
            mov eax, ebx
            imul eax
            add suma_xx, eax

            ;---suma_xy += X[i] * Y[i];
            mov eax, ebx
            imul ecx
            add suma_xy, eax

            add esi, 1
            jmp for_point


        calc:

    }
    return {1,2};
}