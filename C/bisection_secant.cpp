//combined bisection and secant numerical method to solve equations
//#include <iostream>
bool in_range(double x, double a, double b)
{
    return x >= a && x <= b;
}
double my_abs(double a)
{
    return a < 0 ? -a : a;
}

double secant(double (*f)(double), double a, double b, int M, double eps, double delta) //secant
{
    double x1 = a;
    double x2 = b;
    double fx1 = f(a);
    double fx2 = f(b);
    double x3 = 0.0;
    double fx3 = 0.0;
    if (my_abs(fx1) < eps)
        return a;
    if (my_abs(fx2) < eps)
        return b;
    for (int i = 0; i < M - 2; i++)
    {
        x3 = x2 - (fx2 * (x2 - x1) / (fx2 - fx1));
        fx3 = f(x3);
        if (my_abs(fx3) < eps || my_abs(x3 - x2) < delta)
            break;
        x1 = x2;
        fx1 = fx2;
        x2 = x3;
        fx2 = fx3;
    }
    return x3;
};

double bisection(double (*f)(double), double a, double b, int M, double eps, double delta)
{
    double fa = f(a);
    double fb = f(b);
    double e = b - a;
    double c = 0.0;
    if (my_abs(fa) < eps)
        return a;
    if (my_abs(fb) < eps)
        return b;
    if (fa * fb > 0)
    {
        return secant(f, a, b, M - 2, eps, delta);
    }
    bool flag = false;
    for (int i = 0; i < M - 2; i++) //max amound of iterations
    {
        e /= 2;
        c = a + e;
        double fc = f(c);
        if (my_abs(e) < 0.1 || my_abs(fc) < 0.05)
        {
            if (flag)
            {
                return secant(f, a, c, M - i - 3, eps, delta);
            }
            else
            {
                return secant(f, c, b, M - i - 3, eps, delta);
            }
        }
        if (fc * fa < 0)
        {
            b = c;
            fb = fc;
            flag = false;
        }
        else
        {
            a = c;
            fa = fc;
            flag = true;
        }
    }
    return c;
};

double wyznaczMiejsceZerowe(double (*f)(double), double a, double b, int M, double eps, double delta)
{
    return bisection(f, a, b, M, eps, delta);
};
