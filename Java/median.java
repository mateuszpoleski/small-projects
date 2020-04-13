//finding k-th biggest element O(n) in place
import java.util.Scanner;

public class Source {
static void swap(int[] arr, int a, int b){
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}
static void insSort(int arr[],int f,int l) 
    { 
        for (int i = f; i < l+1; ++i) { 
            int key = arr[i]; 
            int j = i - 1; 
            while (j >= f && arr[j] > key) { 
                arr[j + 1] = arr[j]; 
                j--; 
            } 
            arr[j + 1] = key; 
        } 
    } 
    static int findMedianIndex(int arr[], int f,int l){ 
        insSort(arr, f, l);//i-pierwszy index, l-ostatni index
        return f+(l-f+1)/2;//jeśli mamy 2 mediany to większa 
    }
    static int partition(int arr[], int low, int high,int pivot,int[] pivotLastIndex) 
    { 
        int i; //standardowy partition
        for (i = low; i < high; i++){
            if (arr[i] == pivot) 
            break; 
        }
        int temp = arr[i];
        arr[i] = arr[high];
        arr[high] = temp;
        //int pivot = arr[high];  
        i = low; 
        int pivotCount = 0;
        for (int j=low; j<high; j++) 
        { 
            if(arr[j] < pivot) { 
                temp = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = temp; 
                i++;
            } 
            else if(arr[j] == pivot){//zliczamy takie same mediany
                pivotCount++;
            }
        } 
        temp = arr[i]; //mediana na pierwsza dobra pozcyje 
        arr[i] = arr[high]; 
        arr[high] = temp; 
        int top=high;
        int count=0;
        for(int j=i+1;j<high;j++){//wkladamy mediany obok siebie
            if (count == pivotCount) break;
            if(arr[j]!=pivot){
                swap(arr,j,top);
                top--;
                j--;
            }
            else count++;
        }
        pivotLastIndex[0] = i + pivotCount;//zapisujemy index ostatniego wystapienia mediany
        return i; //zwracamy index pierwszego wystapienia mediany
    }
    static int MM(int arr[],int k, int f,int l){
        if(l-f<30){ //arrSize<5
            insSort(arr,f,l);
            return arr[f+k-1]; 
        }
        int medArrInd=-1;
        int i;
        for(i=f;i+4<=l;i+=5){//rozkładamy na podtablice 5 el.
            swap(arr,++medArrInd+f,findMedianIndex(arr,i,i+4));
        }
        if(i<l){//ostatnio tablica <5 el.
            swap(arr,++medArrInd+f,findMedianIndex(arr,i,l));
        }
        int median = MM(arr,((medArrInd+1)/2)+1,f,f+medArrInd); //mediana median
        int medianLast[] = new int[1];//ostatni index mediany
        int p = partition(arr,f,l,median,medianLast); //pierwszy index mediany
        if(f+k<=p) return MM(arr,k,f,p-1); //jesli index pierwszej mediany wiekszy od k to zwracamy lewa podtablice
        if(f+k<=medianLast[0]+1) return median; //jesli index ostatniej mediany wiekszy od k to zwracamy mediane
        return MM(arr,k-medianLast[0]-1+f,medianLast[0]+1,l); // jesli index ostatniej mediany mniejszy od k to zwracamy prawo podtablice i zmieniamy szukany numer
        
    }
    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        
        int z = in.nextInt();
        for(int k=0;k<z;k++){
            int n = in.nextInt();
            int arr[] = new int[n];
            for(int i=0;i<n;i++){
                arr[i] = in.nextInt();
            }
            int m = in.nextInt();
            for(int i=0;i<m;i++){
                int x = in.nextInt();
                if(x<1 || x>n) System.out.println(x+" brak");
                else System.out.println(x+" "+MM(arr,x,0,n-1)); 
            }
        }
    }
    
}
/*
test.in:
3
5
1 2 3 4 5
3
1 2 3
5
5 3 4 4 3
5
2 5 1 3 4
10
1 1 1 1 1 1 1 1 1 1
5
1 10 0 -1 11
test.out:
1 1
2 2
3 3
2 3
5 5
1 3
3 4
4 4
1 1
10 1
0 brak
-1 brak
11 brak
*/