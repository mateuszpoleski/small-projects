
//Multidimensional Newtons method for solving equations and finding fixed points
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

typedef void (*FuncPointer)(const double *x, double *y, double *Df);

void printVector(const double *x, unsigned N)
{
    for (unsigned i = 0; i < N; ++i)
        printf("%17.17f ", x[i]);
    printf("\n");
}
double f_h(double a, double b)
{
    return a * a + 2 * a * b + b * b;
}
void gauss(double *arr, const int &n)
{
    //works for square matrix
    //a_row|col notation
    for (int k = 0; k < n - 1; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            double z = arr[i * n + k] / arr[k * n + k]; //a_ik/a_kk
            arr[i * n + k] = 0.0;
            for (int j = k + 1; j < n; j++)
            {
                arr[i * n + j] -= z * arr[k * n + j];
            }
        }
    }
}
void to_squared(double *arr, double *ret, const int &n, const int &m)
{
    int ctr = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ret[ctr] = arr[i * m + j];
            ctr++;
        }
    }
}
void solve(double *arr_df, double *vars, double *vals, const int &n, const int &m)
{
    //f'(x)*d = -f(x), looking for d->vars
    double arr_gauss[m * m];
    to_squared(arr_df, arr_gauss, m, n);
    vals[0] *= (-1.);
    vals[1] *= (-1.);
    double tmp = arr_gauss[0] / arr_gauss[2];
    arr_gauss[2] = 0.0;
    arr_gauss[3] *= tmp;
    arr_gauss[3] -= arr_gauss[1];
    vals[1] *= tmp;
    vals[1] -= vals[0];
    vars[1] = vals[1] / arr_gauss[3];
    vars[0] = (vals[0] - arr_gauss[1] * vars[1]) / arr_gauss[0];
}
void f_to_g(double *x, double *arr_y, double *arr_df)
{
    arr_y[0] -= x[0]; //g(x,y) = f(x,y) - (x,y)
    arr_y[1] -= x[1];
    arr_df[0] -= 1; //removing 1 from jacobian diagonal
    arr_df[5] -= 1;
}
int findCurve(FuncPointer f, double *x, unsigned k, double h)
{
    int n = 3;
    int m = 2;
    double tmp_x[n];
    tmp_x[0] = x[0];
    tmp_x[1] = x[1];
    tmp_x[2] = x[2];
    double arr_y[m];
    double arr_df[n * m];
    double arr_vars[m];
    f(x, arr_y, arr_df);
    for (int i = 1; i <= k; i++)
    {
        x[2] = x[2] + h;
        f(x, arr_y, arr_df);
        while (max(abs(arr_y[0]), abs(arr_y[1])) > 1e-14)
        {
            f(x, arr_y, arr_df);
            solve(arr_df, arr_vars, arr_y, n, m);
            x[0] = x[0] + arr_vars[0];
            x[1] = x[1] + arr_vars[1];
            if (abs(arr_y[0]) > 10 || abs(arr_y[1]) > 10)
            {
                return i;
            }
        }
        printVector(x, n);
    }
    return 0;
}
int findSurface(FuncPointer f, double *x, unsigned k1, unsigned k2, double h1, double h2)
{
    int n = 3;
    double arr_y[1];
    double arr_df[3];
    double tmp_a = x[0];
    bool first = false;
    for (int i = 0; i < k1; i++)
    {
        x[1] += h1;
        x[0] = tmp_a;
        first = true;
        for (int j = 0; j < k2; j++)
        {
            x[2] += h2;
            f(x, arr_y, arr_df);
            while (abs(arr_y[0]) > 1e-14)
            {
                f(x, arr_y, arr_df);

                x[0] -= arr_y[0] / arr_df[0];

                if (abs(arr_y[0]) > 10)
                {
                    return i * k1 + j;
                }
            }
            if (first)
            {
                first = false;
                tmp_a = x[0];
            }
            printVector(x, n);
        }
        x[2] -= h2 * k2;
        cout << endl;
    }
    return 0;
}
int findFixedPoints(FuncPointer f, double *x, unsigned k1, unsigned k2, double h1, double h2)
{
    int n = 4;
    int m = 2;
    double arr_y[m];
    double arr_df[n * m];
    double arr_vars[m];
    double tmp_a = x[0];
    double tmp_b = x[1];
    bool first = false;
    for (int i = 0; i < k1; i++)
    {
        x[2] += h1;
        x[0] = tmp_a;
        x[1] = tmp_b;
        first = true;
        for (int j = 0; j < k2; j++)
        {
            x[3] += h2;
            f(x, arr_y, arr_df);
            while (max(abs(arr_y[0] - x[0]), abs(arr_y[1] - x[1])) > 1e-15)
            {
                f(x, arr_y, arr_df);
                f_to_g(x, arr_y, arr_df); //f(x,y) -> f(x,y) - (x,y)
                solve(arr_df, arr_vars, arr_y, n, m);
                x[0] = x[0] + arr_vars[0];
                x[1] = x[1] + arr_vars[1];
                f(x, arr_y, arr_df);
                if (abs(arr_y[0]) > 10 || abs(arr_y[1]) > 10)
                {
                    return i * k1 + j;
                }
            }
            if (first)
            {
                first = false;
                tmp_a = x[0];
                tmp_b = x[1];
            }
            printVector(x, n);
        }
        x[3] -= h2 * k2;
        cout << endl;
    }
    return 0;
}