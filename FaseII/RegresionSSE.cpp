#include "Regresion.h"

Result regresionSSE(float X[], float Y[], int arr_size) {
    float suma_x, suma_y, suma_xy, suma_xx, media, var_x, cov_xy;
    suma_x = suma_y = suma_xy = suma_xx = media = var_x = cov_xy = 0.0;

    Result result;

    __asm {
        xor esi, esi            ;se usara como cont del arr de puntos
        mov edi, arr_size       ;se usara como max iteraciones en los arr de puntos

        ;Se usara los registros xmm como paquetes de 4 elementos (4 flotantes de simple precision)

        ;recorrer arr de puntos de 4 en 4
        for_point:
            cmp esi, edi
            je calc             ;saltar si esi==edi

            mov ebx, X          ;item i de X
            movups xmm0, [ebx+esi*4]    
            mov ecx, Y          ;item i de Y
            movups xmm1, [ecx+esi*4]

                                ;operacion sobre 4 elementos -> xmm2 += X[i]
            addps xmm2, xmm0

                                ;operacion sobre 4 elementos -> xmm3 += Y[i]
            addps xmm3, xmm1

                                ;operacion sobre 4 elementos -> xmm5 += X[i] * Y[i];
            mulps xmm1, xmm0
            addps xmm5, xmm1

                                ;operacion sobre 4 elementos-> xmm4 += X[i] * X[i];
            mulps xmm0, xmm0
            addps xmm4, xmm0

            add esi, 4
            jmp for_point


        calc:
            ;Extraer elemento de xmm -> pextrd variable, xmm<num>, <posicion>h
            ;con hadpps (SSE3) se suma en horizontal de una manera especial
            ;con dos haddps estaran en las 4 posiciones de xmm la suma de los 4 elementos
            ;y bastaria con acceder a una posicion cualquiera
            ;tambien se podria hacer sin haddps, accediendo en posiciones de 1 en 1 y luego sumar

            haddps xmm2, xmm2
            haddps xmm2, xmm2
            pextrd suma_x, xmm2, 0h

            haddps xmm3, xmm3
            haddps xmm3, xmm3
            pextrd suma_y, xmm3, 0h

            haddps xmm4, xmm4
            haddps xmm4, xmm4
            pextrd suma_xx, xmm4, 0h

            haddps xmm5, xmm5
            haddps xmm5, xmm5
            pextrd suma_xy, xmm5, 0h


                                ;media_x
            fld suma_x
            fidiv arr_size
            fst media

                                ;media_x*media_x
            fmul media
            fstp var_x
                                ;var_x = (suma_xx/arr_size) - (media_x*media_x)
            fld suma_xx
            fidiv arr_size
            fsub var_x
            fstp var_x

                                ;media_y*media_x
            fld suma_y
            fidiv arr_size
            fmul media
            fstp cov_xy
                                ;cov_x = (suma_xy/arr_size) - (media_x*media_y)
            fld suma_xy
            fidiv arr_size
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
            fidiv arr_size
            fstp media
                                ;n = ((cov_xy/var_x)*(-media_x)) + media_y
            fadd media
            fstp result.n
    }

    return result;
}