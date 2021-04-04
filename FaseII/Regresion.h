#pragma once

struct Result {
    float m;
    float n;
};

Result regresionCpp(int X[], int Y[], int arr_size);
Result regresionx86(int X[], int Y[], int arr_size);
Result regresionSSE(float X[], float Y[], int arr_size);