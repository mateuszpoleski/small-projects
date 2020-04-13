//learning operators overloading
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

class Z2
{
    short int reszta;

public:
    Z2() : reszta(0) {}
    Z2(short int x) : reszta(x % 2) {}
    operator short int()
    {
        return reszta;
    }
    Z2 &operator+=(const Z2 &b)
    {
        reszta = (reszta + b.reszta) % 2;
        return *this;
    }
    Z2 &operator*=(const Z2 &b)
    {
        if (reszta == 1 && b.reszta == 1)
        {
            reszta = 1;
        }
        else
        {
            reszta = 0;
        }
        return *this;
    }
    Z2 operator/=(const Z2 &b)
    {
        if (b.reszta == 0)
        {
            cout << "Dzielenie przez zero\n";
        }
        return *this;
    }
    friend Z2 operator+(const Z2 &a, const Z2 &b);
    friend Z2 operator*(const Z2 &a, const Z2 &b);
    friend Z2 operator/(const Z2 &a, const Z2 &b);
    friend ostream &operator<<(ostream &out, const Z2 &a);
};
Z2 operator+(const Z2 &a, const Z2 &b)
{
    Z2 c(a.reszta + b.reszta);
    return c;
}
Z2 operator*(const Z2 &a, const Z2 &b)
{
    if (a.reszta == 1 && b.reszta == 1)
    {
        Z2 c(1);
        return c;
    }
    else
    {
        Z2 c;
        return c;
    }
}
Z2 operator/(const Z2 &a, const Z2 &b)
{
    if (b.reszta == 0)
    {
        cout << "Dzielenie przez zero\n";
    }
    return a;
}
ostream &operator<<(ostream &out, const Z2 &a)
{
    out << a.reszta;
    return out;
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
class Polynomial
{
    unsigned int stopien;
    Z2 *tabWsp;

public:
    friend ostream &operator<<(ostream &out, const Polynomial &a);
    friend istream &operator>>(istream &in, Polynomial &p);
    friend Polynomial operator+(const Polynomial &a, const Polynomial &b);
    friend Polynomial operator*(const Polynomial &a, const Polynomial &b);
    friend Polynomial increseIndex(const Polynomial &w, const unsigned int &x);
    friend void mod(const Polynomial &u, const Polynomial &v, Polynomial &q, Polynomial &r);
    friend Polynomial operator/(const Polynomial &u, const Polynomial &v);
    friend Polynomial operator%(const Polynomial &u, const Polynomial &v);

    Polynomial() : stopien(0)
    {
        tabWsp = new Z2[1];
        tabWsp[0] = 0;
    }
    Polynomial(unsigned int _st, Z2 *_tabWsp) : stopien(_st)
    {
        tabWsp = new Z2[stopien + 1];
        for (int i = 0; i <= stopien; i++)
        {
            tabWsp[i] = _tabWsp[i];
        }
    }
    Polynomial(const Polynomial &toCopy) : stopien(toCopy.stopien)
    {
        tabWsp = new Z2[stopien + 1];
        for (int i = 0; i <= stopien; i++)
        {
            tabWsp[i] = toCopy.tabWsp[i];
        }
    }
    ~Polynomial()
    {
        delete[] tabWsp;
    }
    Polynomial &operator=(const Polynomial &b)
    {
        if (this != &b)
        {
            if (tabWsp != NULL)
            {
                delete[] tabWsp;
            }
            stopien = b.stopien;
            tabWsp = new Z2[stopien + 1];
            for (int i = 0; i <= stopien; i++)
            {
                tabWsp[i] = b.tabWsp[i];
            }
        }
        return *this;
    }
    short int operator[](const unsigned int &k)
    {
        if (k > stopien)
        {
            cout << "Niepoprawny indeks Polynomialu\n";
            return tabWsp[0];
        }
        else
        {
            return tabWsp[k];
        }
    }
    Polynomial &operator+=(const Polynomial &b)
    {
        return *this = *this + b;
    }
    Polynomial &operator*=(const Polynomial &b)
    {
        return *this = *this * b;
    }
    unsigned int degree()
    {
        return stopien;
    }
    string toString(const string &xVar)
    {
        string s;
        if (stopien == 0)
        {
            s += "0";
            return s;
        }
        else
        {
            if (tabWsp[0] == 1)
            {
                s += "1+";
            }
            for (int i = 1; i <= stopien; i++)
            {
                if (tabWsp[i] != 0)
                {
                    ostringstream ss;
                    ss << i;
                    s += xVar + "^" + ss.str();
                    if (stopien != i)
                    {
                        s += "+";
                    }
                }
            }
            return s;
        }
    }
    Polynomial increseIndex(const Polynomial &w, const unsigned int &x)
    {
        Z2 *_tabWsp = new Z2[w.stopien + x + 1];
        for (int i = 0; i <= w.stopien + x; i++)
        {
            _tabWsp[i] = 0;
        }
        for (int i = 0; i <= w.stopien; i++)
        {
            if (w.tabWsp[i] == 1)
            {
                _tabWsp[i + x] = 1;
            }
        }
        Polynomial c(w.stopien + x, _tabWsp);
        delete[] _tabWsp;
        return c;
    }
};
unsigned int max(unsigned int &a, unsigned int &b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
Polynomial operator+(const Polynomial &a, const Polynomial &b)
{
    unsigned int st = max(a.stopien, b.stopien);
    Z2 *_tabWsp = new Z2[st + 1];
    unsigned int tmp = 0;
    for (int i = 0; i <= st; i++)
    {
        _tabWsp[i] = 0;
        if (i <= a.stopien)
        {
            _tabWsp[i] += a.tabWsp[i];
        }
        if (i <= b.stopien)
        {
            _tabWsp[i] += b.tabWsp[i];
        }
        if (_tabWsp[i] == 1)
        {
            tmp = i;
        }
    }
    Polynomial c(tmp, _tabWsp);
    delete[] _tabWsp;
    return c;
}
Polynomial operator*(const Polynomial &a, const Polynomial &b)
{
    unsigned int st = (a.stopien + b.stopien + 1);
    unsigned int tmp = 0;
    Z2 *_tabWsp = new Z2[st];
    for (unsigned int i = 0; i <= a.stopien; i++)
    {
        for (unsigned int j = 0; j <= b.stopien; j++)
        {
            _tabWsp[i + j] += a.tabWsp[i] * b.tabWsp[j];
            if (_tabWsp[i + j] == 1)
            {
                tmp = max(tmp, i + j);
            }
        }
    }
    Polynomial c(tmp, _tabWsp);
    delete[] _tabWsp;
    return c;
}

void mod(const Polynomial &u, const Polynomial &v, Polynomial &q, Polynomial &r)
{
    if (v.stopien == 0 && v.tabWsp[0] == 1)
    {
        q = u;
        r = Polynomial();
        return;
    }
    else if (v.stopien == 0)
    {
        cout << "Dzielenie przez zero\n";
        return;
    }
    Polynomial tmp = u;
    Polynomial tmp2 = v;
    Z2 *_tab = new Z2[u.stopien + 1];
    for (int i = 0; i <= u.stopien; i++)
    {
        _tab[i] = 0;
    }
    unsigned int wsp = v.stopien;
    while (tmp.stopien >= v.stopien)
    {
        wsp = tmp.stopien - v.stopien;
        _tab[wsp] = 1;
        tmp2 = tmp2.increseIndex(v, wsp);
        tmp += tmp2;
    }
    Polynomial c(u.stopien - v.stopien, _tab);
    delete[] _tab;
    q = c;
    r = tmp;
}
Polynomial operator/(const Polynomial &u, const Polynomial &v)
{
    if (v.stopien == 0)
    {
        cout << "Dzielenie przez zero\n";
        return u;
    }
    Polynomial tmp = u;
    Polynomial tmp2 = v;
    Z2 *_tab = new Z2[u.stopien + 1];
    for (int i = 0; i <= u.stopien; i++)
    {
        _tab[i] = 0;
    }
    unsigned int wsp = v.stopien;
    while (tmp.stopien >= v.stopien)
    {
        wsp = tmp.stopien - v.stopien;
        _tab[wsp] = 1;
        tmp2 = tmp2.increseIndex(v, wsp);
        tmp += tmp2;
    }
    Polynomial c(u.stopien - v.stopien, _tab);
    delete[] _tab;
    return c;
}
Polynomial operator%(const Polynomial &u, const Polynomial &v)
{
    if (v.stopien == 0)
    {
        cout << "Dzielenie przez zero\n";
        return Polynomial();
    }
    Polynomial tmp = u;
    Polynomial tmp2 = v;
    Z2 *_tab = new Z2[u.stopien + 1];
    for (int i = 0; i <= u.stopien; i++)
    {
        _tab[i] = 0;
    }
    unsigned int wsp = v.stopien;
    while (tmp.stopien >= v.stopien)
    {
        wsp = tmp.stopien - v.stopien;
        _tab[wsp] = 1;
        tmp2 = tmp2.increseIndex(v, wsp);
        tmp += tmp2;
    }
    delete[] _tab;
    return tmp;
}
ostream &operator<<(ostream &out, const Polynomial &a)
{
    out << "{";
    for (int i = 0; i <= a.stopien; i++)
    {
        out << a.tabWsp[i];
        if (i != a.stopien)
        {
            out << ",";
        }
    }
    out << "}";
    return out;
}
istream &operator>>(istream &in, Polynomial &p)
{
    Z2 *tmp = new Z2[100000];
    unsigned int licznik = 0;
    unsigned int i = 0;
    string s;
    in >> s;
    while (s[i] != '{')
    {
        i++;
    }
    while (s[i] != '}')
    {
        if (s[i] == '1')
        {
            tmp[licznik] = 1;
            licznik++;
            i++;
        }
        else if (s[i] == '0')
        {
            tmp[licznik] = 0;
            licznik++;
            i++;
        }
        else
        {
            i++;
        }
    }
    Polynomial c(licznik - 1, tmp);
    delete[] tmp;
    p = c;
}

int main()
{
    Z2 tab1[5] = {1, 0, 1, 0, 1};
    Z2 tab2[2] = {1, 1};
    Polynomial d;
    Polynomial a(4, tab1);
    Polynomial b(1, tab2);
    Polynomial q;
    Polynomial r;
    cout << b;
    string s = b.toString("x");
    cout << s;
    cout << a;
    Polynomial c;
    c = a + b;
    cout << c;
    unsigned int x = c.degree();
    cout << endl
         << x;
    cout << endl;
    mod(a, d, q, r);
    cout << q << endl;
    cout << r << endl;
    cout << a / d << endl;
    cout << a % d << endl;
    s = c.toString("y");
    cout << c << endl
         << s << endl;
    Polynomial w;
    cin >> w;
    cout << "w: " << w;

    return 0;
}
