//learning inheritance
#include <iostream>
#include <stdlib.h>
#include "Morfologia.h"

class BitmapaExt : public Bitmapa
{
private:
    bool *bitMap;
    unsigned zakresX;
    unsigned zakresY;
    unsigned zakresZ;

public:
    BitmapaExt(const unsigned X, const unsigned Y, const unsigned Z) : zakresX(X), zakresY(Y), zakresZ(Z)
    {
        bitMap = (bool *)calloc(X * Y * Z, sizeof(bool));
    }
    //konstr. kopiujacy
    BitmapaExt(const BitmapaExt &toCopy) : zakresX(toCopy.zakresX), zakresY(toCopy.zakresY), zakresZ(toCopy.zakresZ)
    {
        unsigned arrSize = toCopy.zakresX * toCopy.zakresY * toCopy.zakresZ;
        bitMap = (bool *)calloc(arrSize, sizeof(bool));
        for (int i = 0; i < arrSize; i++)
        {
            bitMap[i] = toCopy.bitMap[i];
        }
    }
    //operator przypisania
    BitmapaExt &operator=(const BitmapaExt &b)
    {
        if (this != &b)
        {
            free(bitMap);
            zakresX = b.zakresX;
            zakresY = b.zakresY;
            zakresZ = b.zakresZ;
            unsigned arrSize = zakresX * zakresY * zakresZ;
            bitMap = (bool *)calloc(arrSize, sizeof(bool));
            for (int i = 0; i < zakresX; i++)
            {
                bitMap[i] = b.bitMap[i];
            }
        }
        return *this;
    }
    virtual unsigned sx() const
    {
        return zakresX;
    }
    virtual unsigned sy() const
    {
        return zakresY;
    }
    virtual unsigned sz() const
    {
        return zakresZ;
    }
    virtual bool &operator()(unsigned x, unsigned y, unsigned z)
    {
        return bitMap[x * zakresY * zakresZ + y * zakresZ + z];
    }
    virtual bool operator()(unsigned x, unsigned y, unsigned z) const
    {
        return bitMap[x * zakresY * zakresZ + y * zakresZ + z];
    }
    virtual ~BitmapaExt()
    {
        free(bitMap);
    }
};
//
std::ostream &operator<<(std::ostream &out, const Bitmapa &bitMap)
{

    out << "{\n";
    for (unsigned i = 0; i < bitMap.sx(); i++)
    {
        out << " {\n";
        for (unsigned j = 0; j < bitMap.sy(); j++)
        {
            out << "  {";
            for (unsigned k = 0; k < bitMap.sz(); k++)
            {
                out << bitMap(i, j, k);
                if (k != bitMap.sz() - 1)
                    out << ",";
            }
            if (j != bitMap.sy() - 1)
                out << "},\n";
            else
                out << "}\n";
        }
        if (i != bitMap.sx() - 1)
            out << " },\n";
        else
            out << " }\n";
    }
    out << "}";
    return out;
}

//
class Inwersja : public Przeksztalcenie
{
public:
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        for (int i = 0; i < bitMap.sx(); i++)
            for (int j = 0; j < bitMap.sy(); j++)
                for (int k = 0; k < bitMap.sz(); k++)
                    bitMap(i, j, k) = !bitMap(i, j, k);
    }
    virtual ~Inwersja() {}
};
class Erozja : public Przeksztalcenie
{
public:
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        int arrSize = bitMap.sx() * bitMap.sy() * bitMap.sz();
        int *tmp = (int *)calloc(arrSize, sizeof(int));
        //int* tmp = new int[arrSize];
        int tmpSize = 0;
        for (int i = 0; i < bitMap.sx(); i++)
        {
            for (int j = 0; j < bitMap.sy(); j++)
            {
                for (int k = 0; k < bitMap.sz(); k++)
                {
                    if (bitMap(i, j, k) && (                                           // je�li jest bialy
                                               (i - 1 >= 0 && !bitMap(i - 1, j, k)) || //spr. czy jest brzegowy,je�li tak to zmiana na bia�y
                                               (i + 1 < bitMap.sx() && !bitMap(i + 1, j, k)) ||
                                               (j - 1 >= 0 && !bitMap(i, j - 1, k)) ||
                                               (j + 1 < bitMap.sy() && !bitMap(i, j + 1, k)) ||
                                               (k - 1 >= 0 && !bitMap(i, j, k - 1)) ||
                                               (k + 1 < bitMap.sz() && !bitMap(i, j, k + 1))))
                    {
                        tmp[tmpSize++] = i * bitMap.sy() * bitMap.sz() + j * bitMap.sz() + k;
                    }
                }
            }
        }
        for (int i = 0; i < tmpSize; i++)
        {
            bitMap(tmp[i] / (bitMap.sy() * bitMap.sz()), (tmp[i] / bitMap.sz()) % bitMap.sy(), tmp[i] % bitMap.sz()) = false;
        }
        free(tmp);
    }
    virtual ~Erozja() {}
};

class Dylatacja : public Przeksztalcenie
{
public:
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        //
        int arrSize = bitMap.sx() * bitMap.sy() * bitMap.sz();
        int *tmp = (int *)calloc(arrSize, sizeof(int));
        int tmpSize = 0;
        for (int i = 0; i < bitMap.sx(); i++)
        {
            for (int j = 0; j < bitMap.sy(); j++)
            {
                for (int k = 0; k < bitMap.sz(); k++)
                {
                    if (!bitMap(i, j, k) && (                                          // je�li jest bialy
                                                (i - 1 >= 0 && bitMap(i - 1, j, k)) || //spr. czy jest brzegowy,je�li tak to zmiana na bia�y
                                                (i + 1 < bitMap.sx() && bitMap(i + 1, j, k)) ||
                                                (j - 1 >= 0 && bitMap(i, j - 1, k)) ||
                                                (j + 1 < bitMap.sy() && bitMap(i, j + 1, k)) ||
                                                (k - 1 >= 0 && bitMap(i, j, k - 1)) ||
                                                (k + 1 < bitMap.sz() && bitMap(i, j, k + 1))))
                    {
                        tmp[tmpSize++] = i * bitMap.sy() * bitMap.sz() + j * bitMap.sz() + k;
                    }
                }
            }
        }
        for (int i = 0; i < tmpSize; i++)
        {
            bitMap(tmp[i] / (bitMap.sy() * bitMap.sz()), (tmp[i] / bitMap.sz()) % bitMap.sy(), tmp[i] % bitMap.sz()) = true;
        }
        free(tmp);
    }
    virtual ~Dylatacja() {}
};

class Zerowanie : public Przeksztalcenie
{
public:
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        for (int i = 0; i < bitMap.sx(); i++)
            for (int j = 0; j < bitMap.sy(); j++)
                for (int k = 0; k < bitMap.sz(); k++)
                    bitMap(i, j, k) = false;
    }
    virtual ~Zerowanie() {}
};

class Usrednianie : public Przeksztalcenie
{
public:
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        int arrSize = bitMap.sx() * bitMap.sy() * bitMap.sz();
        int *tmp = (int *)calloc(arrSize, sizeof(int));
        int tmpSize = 0;
        for (int i = 0; i < bitMap.sx(); i++)
        {
            for (int j = 0; j < bitMap.sy(); j++)
            {
                for (int k = 0; k < bitMap.sz(); k++)
                {
                    int colorCount = 0;
                    if (bitMap(i, j, k))
                    { //czarne
                        if (i - 1 >= 0 && !bitMap(i - 1, j, k))
                            colorCount++;
                        if (i + 1 < bitMap.sx() && !bitMap(i + 1, j, k))
                            colorCount++;
                        if (j - 1 >= 0 && !bitMap(i, j - 1, k))
                            colorCount++;
                        if (j + 1 < bitMap.sy() && !bitMap(i, j + 1, k))
                            colorCount++;
                        if (k - 1 >= 0 && !bitMap(i, j, k - 1))
                            colorCount++;
                        if (k + 1 < bitMap.sz() && !bitMap(i, j, k + 1))
                            colorCount++;
                    }
                    else
                    { //biale
                        if (i - 1 >= 0 && bitMap(i - 1, j, k))
                            colorCount++;
                        if (i + 1 < bitMap.sx() && bitMap(i + 1, j, k))
                            colorCount++;
                        if (j - 1 >= 0 && bitMap(i, j - 1, k))
                            colorCount++;
                        if (j + 1 < bitMap.sy() && bitMap(i, j + 1, k))
                            colorCount++;
                        if (k - 1 >= 0 && bitMap(i, j, k - 1))
                            colorCount++;
                        if (k + 1 < bitMap.sz() && bitMap(i, j, k + 1))
                            colorCount++;
                    }
                    if (colorCount > 3)
                        tmp[tmpSize++] = i * bitMap.sy() * bitMap.sz() + j * bitMap.sz() + k;
                }
            }
        }
        for (int i = 0; i < tmpSize; i++)
        {
            bitMap(tmp[i] / (bitMap.sy() * bitMap.sz()), (tmp[i] / bitMap.sz()) % bitMap.sy(), tmp[i] % bitMap.sz()) = !bitMap(tmp[i] / (bitMap.sy() * bitMap.sz()), (tmp[i] / bitMap.sz()) % bitMap.sy(), tmp[i] % bitMap.sz());
        }
        free(tmp);
    }
    virtual ~Usrednianie() {}
};

//

class ZlozeniePrzeksztalcen : public Przeksztalcenie
{
public:
    int ilePrzeksztalcen;
    Przeksztalcenie **tabPrzeksztalcen;
    ZlozeniePrzeksztalcen() : ilePrzeksztalcen(0)
    {
        tabPrzeksztalcen = (Przeksztalcenie **)calloc(1000, sizeof(Przeksztalcenie *));
        //tabPrzeksztalcen = new Przeksztalcenie*[10000];
    }
    ~ZlozeniePrzeksztalcen()
    {
        free(tabPrzeksztalcen);
    }
    void dodajPrzeksztalcenie(Przeksztalcenie *p)
    {
        tabPrzeksztalcen[ilePrzeksztalcen++] = p;
    }
    virtual void przeksztalc(Bitmapa &bitMap)
    {
        for (int i = 0; i < ilePrzeksztalcen; i++)
        {
            tabPrzeksztalcen[i]->przeksztalc(bitMap);
        }
    }
};
