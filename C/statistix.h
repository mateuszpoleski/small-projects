//some common math functions

bool expval(const unsigned int n, const double *x, const double *p, double (*f)(double a), double &r)
{
    bool flag = true;
    double sumaP = 0;
    double sumaCalk = 0;
    for (int i = 0; i < n; i++)
    {
        sumaP += p[i];
        sumaCalk += f(x[i]) * p[i];
        if (p[i] < 0 || sumaP >= 1)
        {
            flag = false;
            break;
        }
    }
    sumaCalk += f(x[n]) * (1 - sumaP);
    if (flag)
    {
        r = sumaCalk;
    }
    return flag;
}
//2
int podzial(int tablica[], int p, int r)
{
    int x = tablica[p];
    int i = p, j = r, w;
    while (true)
    {
        while (tablica[j] > x)
            j--;
        while (tablica[i] < x)
            i++;
        if (i < j)
        {
            w = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = w;
            i++;
            j--;
        }
        else
            return j;
    }
}

void qsort(int tablica[], int p, int r)
{
    int q;
    if (p < r)
    {
        q = podzial(tablica, p, r);
        qsort(tablica, p, q);
        qsort(tablica, q + 1, r);
    }
}
bool median(const unsigned int n, const int *t, int (*f)(int a), bool (*p)(int a), double &r)
{
    int *tabPom = new int[n];
    int licznikArg = 0;
    for (int i = 0; i < n; i++)
    {
        if (p(t[i]) == true)
        {
            tabPom[licznikArg] = f(t[i]);
            licznikArg++;
        }
    }
    if (licznikArg == 0)
    {
        return false;
    }
    qsort(tabPom, 0, licznikArg - 1);
    int licznikUnk = 0;
    for (int i = 0; i < licznikArg; i++)
    {
        if (tabPom[i] != tabPom[licznikUnk])
        {
            licznikUnk++;
            tabPom[licznikUnk] = tabPom[i];
        }
    }
    licznikUnk++;
    if (licznikArg)
    {
        if (licznikUnk % 2 == 0)
        {
            r = (tabPom[licznikUnk / 2] + tabPom[(licznikUnk / 2) - 1]) / 2.;
        }
        else
        {
            r = tabPom[licznikUnk / 2];
        }
        return true;
    }
    else
    {
        return false;
    }
}
//-2
//3
int nwd(int a, int b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    if (b != 0)
        return nwd(b, a % b);
    else
        return a;
}
unsigned int gcd(unsigned int n, const int *t, int *r = nullptr) //r nullptr
{
    int nd;
    int k = 0;
    if (n == 0)
        return 0;
    if (n == 1 && t[0] == 0)
        return 0;
    nd = t[0];
    for (int i = 0; i < n; i++)
    {
        if (t[i] != 0)
        {
            nd = nwd(nd, t[i]);
            k++;
        }
        if (nd == 1)
            break;
    }
    if (k == 0)
        return 0;
    if (r != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            r[i] = t[i] / nd;
        }
    }
    return nd;
}
//4
unsigned int count(const unsigned int n, const int *t, bool (*p)(int a, int b) = nullptr)
{
    if (n == 0)
    {
        return 0;
    }
    int *tab = new int[n];
    for (int i = 0; i < n; i++)
    {
        tab[i] = t[i];
    }
    unsigned int wynik = 0;
    int bezDuplikatow = 0;
    qsort(tab, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        if (tab[i] != tab[bezDuplikatow])
        {
            bezDuplikatow++;
            tab[bezDuplikatow] = tab[i];
        }
    }
    bezDuplikatow++;
    if (p)
    {
        for (int i = 0; i < bezDuplikatow; i++)
            for (int j = 0; j < bezDuplikatow; j++)
            {
                if (p(tab[i], tab[j]) == true)
                    wynik++;
            }
    }
    else
    {
        wynik = bezDuplikatow * bezDuplikatow;
    }
    return wynik;
}
