//learning classes
#include <iostream>
using namespace std;
static unsigned int ludnosc = 0;
enum Grupa
{
    dziecko,
    kobieta_w_ciazy,
    robotnik,
    bez_grupy
};
extern double limit_dziecko[];
extern double limit_robotnik[];
extern double limit_kobieta_w_ciazy[];
struct Kartka
{
    double mieso;
    double czekolada;
};
struct Obywatel
{
    int NIP;
    Grupa grupa;
    Kartka kartka;
    Obywatel()
    {
        NIP = 0;
        grupa = bez_grupy;
        kartka.czekolada = 0.0;
        kartka.mieso = 0.0;
    }
    Obywatel(int g)
    {
        NIP = ++ludnosc;
        grupa = Grupa(g);
        if (g == 0)
        {
            kartka.mieso = limit_dziecko[0];
            kartka.czekolada = limit_dziecko[1];
        }
        else if (g == 1)
        {
            kartka.mieso = limit_kobieta_w_ciazy[0];
            kartka.czekolada = limit_kobieta_w_ciazy[1];
        }
        else if (g == 2)
        {
            kartka.mieso = limit_robotnik[0];
            kartka.czekolada = limit_robotnik[1];
        }
    }
};
struct Klient
{
    Obywatel osoba;
    Klient *nastepny;
    Klient *poprzedni;
};
struct Lista
{
    Klient *pierwszy;
    Klient *ostatni;
    int licznik;
    Lista()
    {
        pierwszy = nullptr;
        ostatni = nullptr;
        licznik = 0;
    }
    ~Lista()
    {
        //TODO
    }
    void naKoniec(int gr)
    {
        licznik++;
        Klient *nowy = new Klient;
        nowy->osoba = Obywatel(gr);
        nowy->nastepny = nullptr;
        nowy->poprzedni = ostatni;
        ostatni = nowy;
        if (nowy->poprzedni)
        {
            nowy->poprzedni->nastepny = nowy;
        }
        else
        {
            pierwszy = nowy;
        }
    }
    void naPoczatek(int gr)
    {
        licznik++;
        Klient *nowy = new Klient;
        nowy->osoba = Obywatel(gr);
        nowy->poprzedni = nullptr;
        nowy->nastepny = pierwszy;
        pierwszy = nowy;
        if (nowy->nastepny)
        {
            nowy->nastepny->poprzedni = nowy;
        }
        else
        {
            ostatni = nowy;
        }
    }
    void doSrodka(int gdzie, int gr)
    {
        licznik++;
        Klient *pomocniczy = pierwszy;
        for (int i = 0; i < gdzie - 1; i++)
        {
            pomocniczy = pomocniczy->nastepny;
        }
        Klient *nowy = new Klient;
        nowy->osoba = Obywatel(gr);
        nowy->poprzedni = pomocniczy;
        nowy->nastepny = pomocniczy->nastepny;
        pomocniczy->nastepny->poprzedni = nowy;
        pomocniczy->nastepny = nowy;
    }
    void wypisz()
    {
        Klient *pomocniczy = pierwszy;
        while (pomocniczy)
        {
            cout << pomocniczy->osoba.NIP << " " << pomocniczy->osoba.grupa << " " << pomocniczy->osoba.kartka.mieso << " " << pomocniczy->osoba.kartka.czekolada << " " << endl;
            pomocniczy = pomocniczy->nastepny;
        }
    }
    void usun(int nip)
    {
        Klient *pomocniczy = pierwszy;
        while (pomocniczy)
        {
            if (pomocniczy->osoba.NIP == nip)
            {
                if (pomocniczy == pierwszy)
                {
                    pierwszy = pomocniczy->nastepny;
                    pierwszy->poprzedni = nullptr;
                }
                else if (pomocniczy == ostatni)
                {
                    ostatni = pomocniczy->poprzedni;
                    ostatni->nastepny = nullptr;
                }
                else
                {
                    pomocniczy->poprzedni->nastepny = pomocniczy->nastepny;
                    pomocniczy->nastepny->poprzedni = pomocniczy->poprzedni;
                }
                licznik--;
                ludnosc--;
                delete pomocniczy;
                break;
            }
            pomocniczy = pomocniczy->nastepny;
        }
    }
    bool wydawanie(double ile, Obywatel *obw, double *tow, char co)
    {
        double &towar = *tow;
        if (towar == 0)
        {
            return false;
        }
        else
        {
            if (co == 'C')
            {
                if (ile >= obw->kartka.czekolada)
                {
                    if (towar >= obw->kartka.czekolada)
                    {
                        towar -= obw->kartka.czekolada;
                        obw->kartka.czekolada = 0;
                    }
                    else
                    {
                        obw->kartka.czekolada -= towar;
                        towar = 0;
                    }
                }
                else
                {
                    if (towar >= ile)
                    {
                        obw->kartka.czekolada -= ile;
                        towar -= ile;
                    }
                    else
                    {
                        obw->kartka.czekolada -= towar;
                        towar = 0;
                    }
                }
            }
            else
            {
                if (ile >= obw->kartka.mieso)
                {
                    if (towar >= obw->kartka.mieso)
                    {
                        towar -= obw->kartka.mieso;
                        obw->kartka.mieso = 0;
                    }
                    else
                    {
                        obw->kartka.mieso -= towar;
                        towar = 0;
                    }
                }
                else
                {
                    if (towar >= ile)
                    {
                        obw->kartka.mieso -= ile;
                        towar -= ile;
                    }
                    else
                    {
                        obw->kartka.mieso -= towar;
                        towar = 0;
                    }
                }
            }
            return true;
        }
    }
    void sprz(double x, double *towar, char co)
    {
        while (pierwszy)
        {
            if (wydawanie(x, &(pierwszy->osoba), towar, co))
            {
                licznik--;
                ludnosc--;
                pierwszy = pierwszy->nastepny;
                if (pierwszy)
                {
                    pierwszy->poprzedni = nullptr;
                }
                if (pierwszy)
                {
                    delete pierwszy->poprzedni;
                }
            }
            else
            {
                break;
            }
        }
    }
    void zamiana(Klient *a, Klient *b)
    {
        Obywatel temp;
        temp = a->osoba;
        a->osoba = b->osoba;
        b->osoba = temp;
    }
    void odwrKol()
    {
        Klient *pierwszyTemp = pierwszy;
        Klient *ostatniTemp = ostatni;
        for (int i = 0; i < licznik / 2; i++)
        {
            zamiana(pierwszyTemp, ostatniTemp);
            pierwszyTemp = pierwszyTemp->nastepny;
            ostatniTemp = ostatniTemp->poprzedni;
        }
    }
    void naKoniec2(Obywatel pom)
    {
        cout << "a" << endl;
        licznik++;
        Klient *nowy;
        cout << "b" << endl;
        nowy->osoba = pom;
        cout << "c" << endl;
        nowy->nastepny = nullptr;
        cout << "d" << endl;
        nowy->poprzedni = ostatni;
        cout << "e" << endl;
        ostatni = nowy;
        cout << "f" << endl;
        if (nowy->poprzedni)
        {
            nowy->poprzedni->nastepny = nowy;
        }
        else
        {
            pierwszy = nowy;
        }
        cout << "g" << endl;
    }
    void sort()
    {
        Lista a;
        Lista b;
        Lista c;
        Klient *temp = pierwszy;
        Obywatel tempOs = temp->osoba;
        while (temp)
        {
            if (temp->osoba.grupa == 0)
            {
                a.naKoniec2(tempOs);
                cout << "a" << endl;
            }
            else if (temp->osoba.grupa == 1)
            {
                b.naKoniec2(tempOs);
                cout << "b" << endl;
            }
            else
            {
                c.naKoniec2(tempOs);
                cout << "c" << endl;
            }
            temp = temp->nastepny;
            tempOs = temp->osoba;
            cout << "cos" << endl;
        }
        a.wypisz();
        b.wypisz();
        c.wypisz();
    }
};
struct Sklep
{
    char symbol;
    double towar;
    Lista kolejka;
    Sklep() {}
    Sklep(char s, double x)
    {
        symbol = s;
        towar = x;
    }
    void dostawa(double y)
    {
        towar += y;
    }
    void ustawKlientaNaKoniec(int g)
    {
        kolejka.naKoniec(g);
    }
    void ustawKlientaNaPoczatek(int g)
    {
        kolejka.naPoczatek(g);
    }
    void ustawZaKlientem(int k, int g)
    {
        kolejka.doSrodka(k, g);
    }
    void usunKlienta(int n)
    {
        kolejka.usun(n);
    }
    bool towarWydano(double x, Obywatel *o)
    {
        kolejka.wydawanie(x, o, &towar, symbol);
    }
    void sprzedaz(double x)
    {
        kolejka.sprz(x, &towar, symbol);
    }
    void odwrocKolejnosc()
    {
        kolejka.odwrKol();
    }
    void sortuj()
    {
        kolejka.sortowanko();
    }
    int sprwadzObecnosc()
    {
        kolejka.wypisz();
        return kolejka.licznik;
    }
    void dolaczKolejke(Sklep &sklep2)
    {
        if (symbol == sklep2.symbol)
        {
            Klient *pom = sklep2.kolejka.ostatni;
            while (pom)
            {
                Klient *nowy = new Klient;
                nowy = pom;
                pom = pom->poprzedni;
                cout << pom->osoba.NIP << endl;
                kolejka.licznik++;
                nowy->nastepny = nullptr;
                nowy->poprzedni = kolejka.ostatni;
                kolejka.ostatni = nowy;
                if (nowy->poprzedni)
                {
                    nowy->poprzedni->nastepny = nowy;
                }
                else
                {
                    kolejka.pierwszy = nowy;
                }
                if (kolejka.licznik == 10)
                {
                    cout << "licznik" << endl;
                    break;
                }
            }
        }
    }
};
