//iteratice quicksort in place
 package source;

import java.util.Scanner;

public class Source {
    public static int findMax(long arr[],int l,int p){
        int max = l;
        for(int i=l;i<p+1;i++){
            if(arr[max]<arr[i]) max = i;
        }
        return max;
    }

    public static int partition(long arr[], int low, int high) 
    { 
        long pivot = arr[high];  
        int i = (low-1); 
        for (int j=low; j<high; j++) 
        { 
            if (arr[j] <= pivot) 
            { 
                i++; 
                long temp = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = temp; 
            } 
        } 
 
        long temp = arr[i+1]; 
        arr[i+1] = arr[high]; 
        arr[high] = temp; 
  
        return i+1; 
    }
    
    //
    public static void quickSort(int L,int R,long a[]){
        int n = R+1;
        Boolean flag=false;
        int rTmp=R;
        R = 0;
        while(R!=n-1){
            L=R;//przejscie do prawej podtablicy 
             { // po wyjsciu z petli szukamy nowego konca przedzialu P'
                if(R==rTmp){ // jesli nie znajde odpowiedniej liczby w pierwszym przejsciu, nie wiem czy potrzebne 
                    R=L;
                    L++;
                    if(L>=rTmp) return; // tablica posortowana 
                }      
                R++;
            }
            if(flag){ // jesli nie jest to pierwsze przejscie 
                long tmp = a[L]; //naprawa wczesniejszej zamiany kolejnosci (do szukania P')
                a[L] = a[R];
                a[R] = a[L+1];
                a[L+1] = tmp;
            }
            if(!flag){ // Jesli pierwsze przejscie to chcemy zrobic partition(0,n-1)
                R=rTmp;
                flag = true;
            }
            while(L<R){
                int q = partition(a,L,R); // podzial na dwie podtablice 
                if(L==n-1 && L==R) return; //tablica posortowana
                if(L != q && R != q ){ // jesli piwot nie jest na koncach przedzialu 
                    int k = findMax(a,L,q-1);
                    long tmp2 = a[q-1];
                    if(k==q-1){// oznaczenie konca przedzialu prawego P',przypadek specjalny gdy max jest na indexie q-1
                        a[q-1] = a[q];
                        a[q] = a[R];
                        a[R] = tmp2; 
                    }
                    else{// oznaczenie konca przedzialu prawego P'
                        a[q-1] = a[q];
                        a[q] = a[R];
                        a[R] = a[k];
                        a[k] = tmp2;  
                    }
                    R = q-1;//przechodzimy do lewej podtablicy
                }
                else{//pivot ro koniec przedziału 
                    if(L+1==R){
                        break; //ostatnie dwa elementy,zostały posortowane i przechodzimy do prawej podtablicy 
                    }
                    else if(R==q){ //element na dobrym miejscu, wiec tylko zawezamy przedzial i powtarzamy procedure 
                        R--;
                    }
                    else{
                        L++;
                    }
                }
            }
        }
    }
    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        int z = in.nextInt();
        in.nextLine();
        for(int k=0;k<z;k++){
            int n = in.nextInt();
            in.nextLine();
            long arr[] = new long[n];
            for(int i=0;i<n;i++){
                arr[i] = in.nextInt();
            }
            quickSort(0,n-1,arr);
            for(int i=0;i<n;i++){
                System.out.print(arr[i]+" "); 
            }
        }
    }
    
}

/*
test.in
6
9
1 2 3 4 5 6 7 8 9
9
9 8 7 6 5 4 3 2 1
9
1 9 2 8 3 7 4 6 5
9
-10 10 -8 8 -6 6 -4 4 -2 2 0 
1
1
12
123 435 124 -24 11 -45 -109 0 2 1 1234 45783 123400

test.out
1 2 3 4 5 6 7 8 9

1 2 3 4 5 6 7 8 9

1 2 3 4 5 6 7 8 9

-10 -8 -6 -4 -2 0 2 4 6 8 10

1 

-109 -45 -24 0 1 2 11 123 124 435 1234 45783

*/

