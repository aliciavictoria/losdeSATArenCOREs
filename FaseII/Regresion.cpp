#include <stdio.h>
#include <stdlib.h>
#define N 1000

main()
{
    //Declaracion de variables 
    int n, i;
    float m, b, sumax, sumay, sumaxy, sumax2;
    float x[N], y[N];

    // Pedimos la cantidad de puntos
    printf("\n==>Este es un programa creado por maria paz sandoval<== ");
    printf("\n");
    printf("\n==>Programa en C que calcula la Regresion Lineal<== ");
    printf("\n");


    printf("\nIngrese la Cantidad  de puntos: ");
    scanf("%d", &n);

    // mostramos los puntos para pedir el peso y la estatura
    for (i = 0;i < n;i++)
    {
        printf("\nPunto==> %d:         \tPeso : ", i + 1);
        scanf("%f", &y[i]);
        printf("                       \tEstatura : ", i + 1);
        scanf("%f", &x[i]);

    }





    // Hacemos las sumatorias 
    sumax = sumay = sumaxy = sumax2 = 0;
    for (i = 0;i < n;i++)
    {



        // suma de los produtos/
             sumaxy += x[i]*y[i];
             //  suma de los valores de x^2/
                   sumax2 += x[i]*x[i];
                    //suma de los valores de x/
                   sumax += x[i];
                    //suma de los valores de y/
                   sumay += y[i];

        }
        /* Calculamos la pendiente (m) y la interseccion (b)*/

        m = (n*sumaxy - sumax*sumay) / (n*sumax2 - sumax*sumax);
        b = (sumay - m*sumax) / n;

        // Mostramos los valores de la pendiente y de la interseccion
        printf("\n\npendiente(m) = %f \nInterseccion(b) = %f\n\n",m,b);

        // la formula para calcular la variable dependiente(Y) es:
        printf("\n\nValor de la variable dependiente es Y = %f*X+ (%f)\n\n",m,b);

        system("pause");
     }