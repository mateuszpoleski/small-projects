//automatic differentiation for two dimensional two variable functions
#include <iostream>
#include <cmath>
#include "funkcja.h"

using namespace std;

class Node
{
    long double f, fx, fy, fxx, fxy, fyy;

public:
    Node()
    {
        f = fx = fy = fxx = fxy = fyy = 0.;
    }
    Node(long double x)
    {
        f = x;
        fx = fy = fxx = fxy = fyy = 0.;
    }
    Node(long double x, bool)
    {
        f = x;
        fx = 1.;
        fy = fxx = fxy = fyy = 0.;
    }
    Node(bool, long double y)
    {
        f = y;
        fy = 1.;
        fx = fxx = fxy = fyy = 0.;
    }
    Node(const Node &n) : f(n.f), fx(n.fx), fy(n.fy), fxx(n.fxx), fxy(n.fxy), fyy(n.fyy) {}
    Node &operator=(const Node &n)
    {
        if (this != &n)
        {
            f = n.f;
            fx = n.fx;
            fy = n.fy;
            fxx = n.fxx;
            fxy = n.fxy;
            fyy = n.fyy;
        }
        return *this;
    }
    Node operator-() const
    {
        Node tmp;
        tmp.f = -this->f;
        tmp.fx = -this->fx;
        tmp.fy = -this->fy;
        tmp.fxx = -this->fxx;
        tmp.fxy = -this->fxy;
        tmp.fyy = -this->fyy;
        return tmp;
    }
    void print()
    {
        cout.precision(15);
        cout << f << " " << fx << " " << fy << " " << fxx << " " << fxy << " " << fyy << endl;
    }

    friend Node operator-(const Node &n1, const Node &n2);
    friend Node operator+(const Node &n1, const Node &n2);
    friend Node operator*(const Node &n1, const Node &n2);
    friend Node operator/(const Node &n1, const Node &n2);
    friend Node operator+(const Node &n1, const long double &a);
    friend Node operator-(const Node &n1, const long double &a);
    friend Node operator*(const Node &n1, const long double &a);
    friend Node operator/(const Node &n1, const long double &a);
    friend Node operator+(const long double &a, const Node &n1);
    friend Node operator-(const long double &a, const Node &n1);
    friend Node operator*(const long double &a, const Node &n1);
    friend Node operator/(const long double &a, const Node &n1);
    friend Node sin(const Node &n);
    friend Node cos(const Node &n);
    friend Node exp(const Node &n);
};

Node operator-(const Node &n1, const Node &n2)
{
    Node tmp;
    tmp.f = n1.f - n2.f;
    tmp.fx = n1.fx - n2.fx;
    tmp.fy = n1.fy - n2.fy;
    tmp.fxx = n1.fxx - n2.fxx;
    tmp.fxy = n1.fxy - n2.fxy;
    tmp.fyy = n1.fyy - n2.fyy;
    return tmp;
}
Node operator+(const Node &n1, const Node &n2)
{
    Node tmp;
    tmp.f = n1.f + n2.f;
    tmp.fx = n1.fx + n2.fx;
    tmp.fy = n1.fy + n2.fy;
    tmp.fxx = n1.fxx + n2.fxx;
    tmp.fxy = n1.fxy + n2.fxy;
    tmp.fyy = n1.fyy + n2.fyy;
    return tmp;
}
Node operator*(const Node &n1, const Node &n2)
{
    Node tmp;
    tmp.f = n1.f * n2.f;
    tmp.fx = n1.f * n2.fx + n2.f * n1.fx;
    tmp.fy = n1.f * n2.fy + n2.f * n1.fy;
    tmp.fxx = 2 * n1.fx * n2.fx + n1.f * n2.fxx + n2.f * n1.fxx;
    tmp.fxy = n1.fy * n2.fx + n1.fx * n2.fy + n1.f * n2.fxy + n2.f * n1.fxy;
    tmp.fyy = 2 * n1.fy * n2.fy + n1.f * n2.fyy + n2.f * n1.fyy;
    return tmp;
}
Node operator/(const Node &n1, const Node &n2)
{
    Node tmp;
    tmp.f = n1.f / n2.f;
    tmp.fx = (n1.fx * n2.f - n1.f * n2.fx) / (n2.f * n2.f);
    tmp.fy = (n1.fy * n2.f - n1.f * n2.fy) / (n2.f * n2.f);
    tmp.fxx = (-2 * n1.fx * n2.fx) / (n2.f * n2.f) + (2 * n1.f * n2.fx * n2.fx) / (n2.f * n2.f * n2.f) + n1.fxx / n2.f - (n1.f * n2.fxx) / (n2.f * n2.f);
    tmp.fxy = (-n1.fx * n2.fy) / (n2.f * n2.f) + (-n1.fy * n2.fx) / (n2.f * n2.f) + (2 * n1.f * n2.fx * n2.fy) / (n2.f * n2.f * n2.f) + n1.fxy / n2.f - (n1.f * n2.fxy) / (n2.f * n2.f);
    tmp.fyy = (-2 * n1.fy * n2.fy) / (n2.f * n2.f) + (2 * n1.f * n2.fy * n2.fy) / (n2.f * n2.f * n2.f) + n1.fyy / n2.f - (n1.f * n2.fyy) / (n2.f * n2.f);
    return tmp;
}
Node operator+(const Node &n1, const long double &a)
{
    Node n2(a);
    return n1 + n2;
}
Node operator-(const Node &n1, const long double &a)
{
    Node n2(a);
    return n1 - n2;
}
Node operator*(const Node &n1, const long double &a)
{
    Node n2(a);
    return n1 * n2;
}
Node operator/(const Node &n1, const long double &a)
{
    Node n2(a);
    return n1 / n2;
}
Node operator+(const long double &a, const Node &n1)
{
    Node n2(a);
    return n2 + n1;
}
Node operator-(const long double &a, const Node &n1)
{
    Node n2(a);
    return n2 - n1;
}
Node operator*(const long double &a, const Node &n1)
{
    Node n2(a);
    return n2 * n1;
}
Node operator/(const long double &a, const Node &n1)
{
    Node n2(a);
    return n2 / n1;
}
Node sin(const Node &n)
{
    Node tmp;
    tmp.f = sin(n.f);
    tmp.fx = cos(n.f) * n.fx;
    tmp.fy = cos(n.f) * n.fy;
    tmp.fxx = cos(n.f) * n.fxx - sin(n.f) * n.fx * n.fx;
    tmp.fxy = cos(n.f) * n.fxy - sin(n.f) * n.fx * n.fy;
    tmp.fyy = cos(n.f) * n.fyy - sin(n.f) * n.fy * n.fy;
    return tmp;
}
Node cos(const Node &n)
{
    Node tmp;
    tmp.f = cos(n.f);
    tmp.fx = -sin(n.f) * n.fx;
    tmp.fy = -sin(n.f) * n.fy;
    tmp.fxx = -cos(n.f) * n.fx * n.fx - sin(n.f) * n.fxx;
    tmp.fxy = -cos(n.f) * n.fx * n.fy - sin(n.f) * n.fxy;
    tmp.fyy = -cos(n.f) * n.fy * n.fy - sin(n.f) * n.fyy;
    return tmp;
}
Node exp(const Node &n)
{
    Node tmp;
    tmp.f = exp(n.f);
    tmp.fx = exp(n.f) * n.fx;
    tmp.fy = exp(n.f) * n.fy;
    tmp.fxx = exp(n.f) * n.fx * n.fx + exp(n.f) * n.fxx;
    tmp.fxy = exp(n.f) * n.fx * n.fy + exp(n.f) * n.fxy;
    tmp.fyy = exp(n.f) * n.fy * n.fy + exp(n.f) * n.fyy;
    return tmp;
}

int main()
{
    int M;
    long double x, y;
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> x >> y;
        Node node1(x, false);
        Node node2(false, y);
        funkcja(node1, node2).print();
    }

    return 0;
}