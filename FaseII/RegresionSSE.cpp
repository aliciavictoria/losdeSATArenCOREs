#include "Regresion.h"

Result regresionSSE(float X[], float Y[], int arr_size) {
    float aux, suma_x, suma_y, suma_xy, suma_xx, media, var_x, cov_xy;
    aux = suma_x = suma_y = suma_xy = suma_xx = media = var_x = cov_xy = 0.0;

    Result result;

    __asm {
        mov eax, arr_size
        mov ebx, 4
        xor edx, edx    ;mul purposes
        div ebx         ;remainder in edx

        xor esi, esi            ;se usara como cont del arr de puntos
        mov edi, arr_size       ;se usara como max iteraciones en los arr de puntos
        sub edi, edx            ;edi como multiplo de 4

        mov ebx, X      ;posicion de memoria de X
        mov ecx, Y      ;posicion de memoria de Y


        ;Se usara los registros xmm como paquetes de 4 elementos (4 flotantes de simple precision)

        ;recorrer arr de puntos de 4 en 4
        for_point:
            cmp esi, edi
            je init_for_point_remainder ;saltar si esi==edi

            movups xmm0, [ebx+esi*4]    ;item i de X
            movups xmm1, [ecx+esi*4]    ;item i de Y

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


        ;queda operar los puntos restante
        ;se empieza desde desde la posicion donde se quedo el loop anterior

        init_for_point_remainder:
            mov esi, edi        ;se usara como cont del arr de puntos
            mov edi, arr_size   ;se usara como max iteraciones en los arr de puntos


        for_point_remainder:
            cmp esi, edi
            je calc             ;saltar si esi==edi

            fld [ebx+esi*4]     ;item i de X
            fld [ecx+esi*4]     ;item i de Y
                                ;suma_y += Y[i];
            fadd suma_y
            fstp suma_y

                                ;suma_x += X[i];
            fadd suma_x
            fstp suma_x

            fld [ebx+esi*4]     ;item i de X
                                ;suma_xx += X[i] * X[i];
            fst aux
            fmul aux
            fadd suma_xx
            fstp suma_xx

            fld [ebx+esi*4]     ;item i de X
            fld [ecx+esi*4]     ;item i de Y
                                ;suma_xy += X[i] * Y[i];
            fstp aux
            fmul aux
            fadd suma_xy
            fstp suma_xy

            add esi, 1
            jmp for_point_remainder


        calc:
            ;extraer elemento de xmm -> pextrd variable, xmm<num>, <posicion>h
            ;con hadpps (SSE3) se suma en horizontal de una manera especial
            ;con dos haddps estaran en las 4 posiciones de xmm la suma de los 4 elementos
            ;y bastaria con acceder a una posicion cualquiera
            ;tambien se podria hacer sin haddps, accediendo en posiciones de 1 en 1 y luego sumar

            haddps xmm2, xmm2
            haddps xmm2, xmm2
            pextrd aux, xmm2, 0h
            fld suma_x
            fadd aux
            fstp suma_x
            
            haddps xmm3, xmm3
            haddps xmm3, xmm3
            pextrd aux, xmm3, 0h
            fld suma_y
            fadd aux
            fstp suma_y

            haddps xmm4, xmm4
            haddps xmm4, xmm4
            pextrd aux, xmm4, 0h
            fld suma_xx
            fadd aux
            fstp suma_xx

            haddps xmm5, xmm5
            haddps xmm5, xmm5
            pextrd aux, xmm5, 0h
            fld suma_xy
            fadd aux
            fstp suma_xy


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