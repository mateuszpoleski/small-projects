//game in two dimensional array with dynamical memory changes, one of my first programs, using C arrays
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int liczbaWierszy;
    cin >> liczbaWierszy;
    int liczbaWierszyKopia = liczbaWierszy;
    int **tablicaWierszy = (int **)malloc(liczbaWierszy * sizeof(int *));
    int *tablicaDlWierszy = (int *)malloc(liczbaWierszy * sizeof(int));
    for (int i = 0; i < liczbaWierszy; i++)
    {
        int dlWiersza;
        cin >> dlWiersza;
        *(tablicaDlWierszy + i) = dlWiersza;
        *(tablicaWierszy + i) = (int *)malloc(dlWiersza * sizeof(int));
        for (int j = 0; j < dlWiersza; j++)
        {
            cin >> *(*(tablicaWierszy + i) + j);
        }
    }

    while (true)
    {
        //spr. czy wygrana
        bool flagCzySkucha = true;
        if (*(*(tablicaWierszy)) == 0 && liczbaWierszyKopia == 1 && *(tablicaDlWierszy) == 1)
        {
            cout << "GRATULACJE";
            break;
        }

        char komenda;
        cin >> komenda;
        if (komenda == 'L')
        {
            //1.szukanie zera
            int indexWiersza;
            int indexKomorki;
            int cyfraPoPrzesunieciu;
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == 0)
                    {
                        indexWiersza = i;
                        indexKomorki = j;
                        cyfraPoPrzesunieciu = *(*(tablicaWierszy + i) + j + 1);
                    }
                }
            }
            //2.przesuniecie odpowiedniego wiersza
            for (int k = indexKomorki; k < *(tablicaDlWierszy + indexWiersza) - 1; k++)
            {
                *(*(tablicaWierszy + indexWiersza) + k) = *(*(tablicaWierszy + indexWiersza) + k + 1);
                if (k == *(tablicaDlWierszy + indexWiersza) - 2)
                    *(*(tablicaWierszy + indexWiersza) + k + 1) = -1;
            }
            (*(tablicaDlWierszy + indexWiersza))--;
            //4.przesuwanie pustego wiersza do gory
            if (*(tablicaDlWierszy + indexWiersza) == 0)
            {
                while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
                {
                    free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                    liczbaWierszyKopia--;
                }
                for (int i = 0; i < liczbaWierszyKopia - 1; i++)
                {
                    if (*(tablicaDlWierszy + i) == 0)
                    {
                        for (int j = i; j < liczbaWierszyKopia - 1; j++)
                        {
                            if (j == i)
                            {
                                free(*(tablicaWierszy + j));
                            }
                            *(tablicaWierszy + j) = (int *)realloc(*(tablicaWierszy + j + 1), *(tablicaDlWierszy + j + 1) * sizeof(int *));
                        }
                        for (int j = i; j < liczbaWierszyKopia - 1; j++)
                        {
                            *(tablicaDlWierszy + j) = *(tablicaDlWierszy + j + 1);
                        }
                        liczbaWierszyKopia--;
                    }
                }
            }
            //czy skucha
            if (indexWiersza - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza - 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexWiersza + 1 < liczbaWierszyKopia)
            {
                if (*(*(tablicaWierszy + indexWiersza + 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki + 1 < *(tablicaDlWierszy + indexWiersza))
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki + 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki - 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (flagCzySkucha)
            {
                cout << "SKUCHA";
                break;
            }

            //krzyzowe zastapienie liczb na -1
            *(*(tablicaWierszy + indexWiersza) + indexKomorki) = 0;
            for (int i = indexKomorki - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexKomorki + 1; i < *(tablicaDlWierszy + indexWiersza); i++)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza + 1; i < liczbaWierszyKopia; i++)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }

            //ponowne wyrownanie do lewej
            //3.wyrownanie do lewej
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                //3.1 zliczanie -1
                int licznikJedynek = 0;
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == -1)
                        licznikJedynek++;
                }
                //3.2 sortowanie -1 na koniec
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int k = 0; k < *(tablicaDlWierszy + i) - 1; k++)
                    {
                        if (*(*(tablicaWierszy + i) + k) == -1 && *(*(tablicaWierszy + i) + k + 1) != -1)
                        {
                            int temp = *(*(tablicaWierszy + i) + k);
                            *(*(tablicaWierszy + i) + k) = *(*(tablicaWierszy + i) + k + 1);
                            *(*(tablicaWierszy + i) + k + 1) = temp;
                            flag = true;
                        }
                    }
                }
                //3.3 korekta tablicyDlWierszy
                *(tablicaDlWierszy + i) -= licznikJedynek;
            }
            //4.przesuwanie pustego wiersza do gory
            while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
            {
                free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                liczbaWierszyKopia--;
            }
            for (int i = 0; i < liczbaWierszyKopia - 1; i++)
            {
                if (*(tablicaDlWierszy + i) == 0)
                {
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        if (j == i)
                        {
                            free(*(tablicaWierszy + j));
                        }
                        *(tablicaWierszy + j) = (int *)realloc(*(tablicaWierszy + j + 1), *(tablicaDlWierszy + j + 1) * sizeof(int *));
                    }
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        *(tablicaDlWierszy + j) = *(tablicaDlWierszy + j + 1);
                    }
                    liczbaWierszyKopia--;
                }
            }
        }
        else if (komenda == 'U')
        {
            //1.szukanie zera
            int indexWiersza;
            int indexKomorki;
            int cyfraPoPrzesunieciu;
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == 0)
                    {
                        indexWiersza = i;
                        indexKomorki = j;
                        cyfraPoPrzesunieciu = *(*(tablicaWierszy + i + 1) + j);
                    }
                }
            }
            //2.przesuniecie odpowiedniego wiersza
            for (int k = indexWiersza; k < liczbaWierszyKopia - 1; k++)
            {
                if (indexKomorki <= *(tablicaDlWierszy + k + 1))
                {
                    *(*(tablicaWierszy + k) + indexKomorki) = *(*(tablicaWierszy + k + 1) + indexKomorki);
                    if (k == liczbaWierszyKopia - 2)
                        *(*(tablicaWierszy + k + 1) + indexKomorki) = -1;
                }
                else
                {
                    *(*(tablicaWierszy + k) + indexKomorki) = -1;
                    break;
                }
            }
            //3.wyrownanie do lewej
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                //3.1 zliczanie -1
                int licznikJedynek = 0;
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == -1)
                        licznikJedynek++;
                }
                //3.2 sortowanie -1 na koniec
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int k = 0; k < *(tablicaDlWierszy + i) - 1; k++)
                    {
                        if (*(*(tablicaWierszy + i) + k) == -1 && *(*(tablicaWierszy + i) + k + 1) != -1)
                        {
                            int temp = *(*(tablicaWierszy + i) + k);
                            *(*(tablicaWierszy + i) + k) = *(*(tablicaWierszy + i) + k + 1);
                            *(*(tablicaWierszy + i) + k + 1) = temp;
                            flag = true;
                        }
                    }
                }
                //3.3 korekta tablicyDlWierszy
                *(tablicaDlWierszy + i) -= licznikJedynek;
            }
            //4.przesuwanie pustego wiersza do gory
            while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
            {
                free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                liczbaWierszyKopia--;
            }
            //czy skucha
            if (indexWiersza - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza - 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexWiersza + 1 < liczbaWierszyKopia)
            {
                if (*(*(tablicaWierszy + indexWiersza + 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki + 1 < *(tablicaDlWierszy + indexWiersza))
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki + 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki - 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (flagCzySkucha)
            {
                cout << "SKUCHA";
                break;
            }

            //krzyzowe zastapienie liczb na -1
            *(*(tablicaWierszy + indexWiersza) + indexKomorki) = 0;
            for (int i = indexKomorki - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexKomorki + 1; i < *(tablicaDlWierszy + indexWiersza); i++)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza + 1; i < liczbaWierszyKopia; i++)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }

            //ponowne wyrownanie do lewej
            //3.wyrownanie do lewej
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                //3.1 zliczanie -1
                int licznikJedynek = 0;
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == -1)
                        licznikJedynek++;
                }
                //3.2 sortowanie -1 na koniec
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int k = 0; k < *(tablicaDlWierszy + i) - 1; k++)
                    {
                        if (*(*(tablicaWierszy + i) + k) == -1 && *(*(tablicaWierszy + i) + k + 1) != -1)
                        {
                            int temp = *(*(tablicaWierszy + i) + k);
                            *(*(tablicaWierszy + i) + k) = *(*(tablicaWierszy + i) + k + 1);
                            *(*(tablicaWierszy + i) + k + 1) = temp;
                            flag = true;
                        }
                    }
                }
                //3.3 korekta tablicyDlWierszy
                *(tablicaDlWierszy + i) -= licznikJedynek;
            }
            //4.przesuwanie pustego wiersza do gory
            while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
            {
                free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                liczbaWierszyKopia--;
            }
            for (int i = 0; i < liczbaWierszyKopia - 1; i++)
            {
                if (*(tablicaDlWierszy + i) == 0)
                {
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        if (j == i)
                        {
                            free(*(tablicaWierszy + j));
                        }
                        *(tablicaWierszy + j) = (int *)realloc(*(tablicaWierszy + j + 1), *(tablicaDlWierszy + j + 1) * sizeof(int *));
                    }
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        *(tablicaDlWierszy + j) = *(tablicaDlWierszy + j + 1);
                    }
                    liczbaWierszyKopia--;
                }
            }
        }
        else if (komenda == 'D')
        {
            //1.szukanie zera
            int indexWiersza;
            int indexKomorki;
            int cyfraPoPrzesunieciu;
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == 0)
                    {
                        indexWiersza = i;
                        indexKomorki = j;
                        cyfraPoPrzesunieciu = *(*(tablicaWierszy + i - 1) + j);
                    }
                }
            }
            //2.przesuniecie odpowiedniego wiersza
            for (int k = indexWiersza; k > 0; k--)
            {
                if (indexKomorki <= *(tablicaDlWierszy + k - 1))
                {
                    *(*(tablicaWierszy + k) + indexKomorki) = *(*(tablicaWierszy + k - 1) + indexKomorki);
                    if (k == 1)
                        *(*(tablicaWierszy + k - 1) + indexKomorki) = -1;
                }
                else
                {
                    *(*(tablicaWierszy + k) + indexKomorki) = -1;
                    break;
                }
            }
            //3.wyrownanie do lewej
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                //3.1 zliczanie -1
                int licznikJedynek = 0;
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == -1)
                        licznikJedynek++;
                }
                //3.2 sortowanie -1 na koniec
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int k = 0; k < *(tablicaDlWierszy + i) - 1; k++)
                    {
                        if (*(*(tablicaWierszy + i) + k) == -1 && *(*(tablicaWierszy + i) + k + 1) != -1)
                        {
                            int temp = *(*(tablicaWierszy + i) + k);
                            *(*(tablicaWierszy + i) + k) = *(*(tablicaWierszy + i) + k + 1);
                            *(*(tablicaWierszy + i) + k + 1) = temp;
                            flag = true;
                        }
                    }
                }
                //3.3 korekta tablicyDlWierszy
                *(tablicaDlWierszy + i) -= licznikJedynek;
            }
            //4.przesuwanie pustego wiersza do gory
            if (*(tablicaDlWierszy) == 0)
            {
                while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
                {
                    free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                    liczbaWierszyKopia--;
                }
                for (int i = 0; i < liczbaWierszyKopia - 1; i++)
                {
                    if (*(tablicaDlWierszy + i) == 0)
                    {
                        for (int j = i; j < liczbaWierszyKopia - 1; j++)
                        {
                            if (j == i)
                            {
                                free(*(tablicaWierszy + j));
                            }
                            *(tablicaWierszy + j) = (int *)realloc(*(tablicaWierszy + j + 1), *(tablicaDlWierszy + j + 1) * sizeof(int *));
                        }
                        for (int j = i; j < liczbaWierszyKopia - 1; j++)
                        {
                            *(tablicaDlWierszy + j) = *(tablicaDlWierszy + j + 1);
                        }
                        liczbaWierszyKopia--;
                        indexWiersza--;
                    }
                }
            }
            //czy skucha
            if (indexWiersza - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza - 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexWiersza + 1 < liczbaWierszyKopia)
            {
                if (*(*(tablicaWierszy + indexWiersza + 1) + indexKomorki) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki + 1 < *(tablicaDlWierszy + indexWiersza))
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki + 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (indexKomorki - 1 >= 0)
            {
                if (*(*(tablicaWierszy + indexWiersza) + indexKomorki - 1) == cyfraPoPrzesunieciu)
                    flagCzySkucha = false;
            }
            if (flagCzySkucha)
            {
                cout << "SKUCHA";
                break;
            }

            //krzyzowe zastapienie liczb na -1
            *(*(tablicaWierszy + indexWiersza) + indexKomorki) = 0;
            for (int i = indexKomorki - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexKomorki + 1; i < *(tablicaDlWierszy + indexWiersza); i++)
            {
                if (*(*(tablicaWierszy + indexWiersza) + i) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + indexWiersza) + i) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza - 1; i >= 0; i--)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }
            for (int i = indexWiersza + 1; i < liczbaWierszyKopia; i++)
            {
                if (*(*(tablicaWierszy + i) + indexKomorki) == cyfraPoPrzesunieciu)
                {
                    *(*(tablicaWierszy + i) + indexKomorki) = -1;
                }
                else
                    break;
            }

            //ponowne wyrownanie do lewej
            //3.wyrownanie do lewej
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                //3.1 zliczanie -1
                int licznikJedynek = 0;
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    if (*(*(tablicaWierszy + i) + j) == -1)
                        licznikJedynek++;
                }
                //3.2 sortowanie -1 na koniec
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int k = 0; k < *(tablicaDlWierszy + i) - 1; k++)
                    {
                        if (*(*(tablicaWierszy + i) + k) == -1 && *(*(tablicaWierszy + i) + k + 1) != -1)
                        {
                            int temp = *(*(tablicaWierszy + i) + k);
                            *(*(tablicaWierszy + i) + k) = *(*(tablicaWierszy + i) + k + 1);
                            *(*(tablicaWierszy + i) + k + 1) = temp;
                            flag = true;
                        }
                    }
                }
                //3.3 korekta tablicyDlWierszy
                *(tablicaDlWierszy + i) -= licznikJedynek;
            }
            //4.przesuwanie pustego wiersza do gory
            while (*(tablicaDlWierszy + liczbaWierszyKopia - 1) == 0)
            {
                free(*(tablicaWierszy + liczbaWierszyKopia - 1));
                liczbaWierszyKopia--;
            }
            for (int i = 0; i < liczbaWierszyKopia - 1; i++)
            {
                if (*(tablicaDlWierszy + i) == 0)
                {
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        if (j == i)
                        {
                            free(*(tablicaWierszy + j));
                        }
                        *(tablicaWierszy + j) = (int *)realloc(*(tablicaWierszy + j + 1), *(tablicaDlWierszy + j + 1) * sizeof(int *));
                    }
                    for (int j = i; j < liczbaWierszyKopia - 1; j++)
                    {
                        *(tablicaDlWierszy + j) = *(tablicaDlWierszy + j + 1);
                    }
                    liczbaWierszyKopia--;
                }
            }
        }
        else if (komenda == 'P')
        {
            for (int i = 0; i < liczbaWierszyKopia; i++)
            {
                for (int j = 0; j < *(tablicaDlWierszy + i); j++)
                {
                    cout << *(*(tablicaWierszy + i) + j);
                }
                cout << endl;
            }
            cout << endl;
        }
        else if (komenda == 'Q')
        {

            break;
        }
    }
    for (int i = 0; i < liczbaWierszyKopia; i++)
    {
        free(*(tablicaWierszy + i));
    }
    free(tablicaWierszy);
    free(tablicaDlWierszy);

    return 0;
}
