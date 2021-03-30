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
#include <vector>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

const int KINC = 10000;

void time_pbplot(vector<double> tCpp, vector<double> tX86, vector<double> s)
{
    RGBABitmapImageReference* img = CreateRGBABitmapImageReference();

    ScatterPlotSeries* series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = &s;
    series1->ys = &tCpp;
    series1->linearInterpolation = true;
    series1->lineType = toVector(L"solid");
    series1->lineThickness = 2;
    series1->color = CreateRGBColor(0.13, 0.13, 0.69);

    ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = &s;
    series2->ys = &tX86;
    series2->linearInterpolation = true;
    series2->lineType = toVector(L"dashed");
    series2->lineThickness = 2;
    series2->color = CreateRGBColor(0.35, 0.72, 0.64);

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(L"Recta de Regresion CPP/X86");
    settings->xLabel = toVector(L"Size");
    settings->yLabel = toVector(L"Time in ms");
    settings->scatterPlotSeries->push_back(series1);
    settings->scatterPlotSeries->push_back(series2);

    DrawScatterPlotFromSettings(img, settings);

    vector<double>* pngdata = ConvertToPNG(img->image);
    WriteToFile(pngdata, "example2.png");
    DeleteImage(img->image);
}
//___________________________________________________________________________


int main(){

    vector<double> timeCpp;
    vector<double> timeX86;
    vector<double> s;
    int cont = 0,tMedX86 = 0,tMedCpp = 0;

    srand(time(NULL));

    for (int i = 1; i <= 10; i++)
    {
        int arr_size = i * KINC;
        int* X = new int[arr_size];
        int* Y = new int[arr_size];

        s.push_back(arr_size);

        for (int j = 0; j < arr_size; j++) 
        {
            X[j] = rand() % 20 + 1;
            Y[j] = rand() % 20 + 1;
        }

        auto start = clock();
        do
        {
            Result resultCpp = regresionCpp(X, Y, arr_size);
            cont++;
        } while (cont < 100);
        auto end = clock();
        cont = 0;
        timeCpp.push_back(1000.0 * (static_cast<__int64>(end) - start) / CLOCKS_PER_SEC);

        start = clock();
        do
        {
            Result resultx86 = regresionx86(X, Y, arr_size);
            cont++;
        } while (cont < 100);
        cont = 0;
        end = clock();
        timeX86.push_back(1000.0 * (static_cast<__int64>(end) - start) / CLOCKS_PER_SEC);
    }

    unsigned i;

    for (i = 0; i < timeCpp.size(); i++)
    {
        tMedCpp += timeCpp[i];
    }

    for (i = 0; i < timeX86.size(); i++)
    {
        tMedX86 += timeX86[i];
    }

    cout << "Tiempo medio CPP: " << tMedCpp/i << " ms" << endl;
    cout << "Tiempo medio X86: " << tMedX86/i << " ms" << endl;

    time_pbplot(timeCpp, timeX86,s);
}
