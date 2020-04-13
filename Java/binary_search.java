//binary search with modifications 
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in); 
    public static int binarySearch(long x ,long[] a,int n){
                if(a[0]==x){
                    return 0;
                }
                if(n>1){
                    if(a[n-1]==x && a[n-2]!=x){
                        return n-1;
                    }
                }
                if(x > a[n-1]){
                    return n;
                }
                if(x < a[0]){
                    return 0;
                }
                int l,r,s;
                l=0;
                r=n-1;
                while(l != r){
                    if(l+1==r && a[l]!=x && a[r]!=x){
                        return r;
                    }
                    s=(l+r)/2;
                    //if(a[r]==x && l+1==r){ s = r;}
                    if(a[s]==x && a[s-1]!=x){
                        return s;
                    }
                    if(a[s]<x){
                        l=s;
                    }
                    else{
                        r=s;
                    }
                }
                return 0;
        }

    public static void main(String[] args) {
        int ileTestow = in.nextInt();
         
        for(int x = 0; x<ileTestow; x++)
        {   
            int N = in.nextInt();
            long[] tab = new long[N];
            for(int i = 0; i< N; i++){
                tab[i] = in.nextLong();
            }
            int ileZapytan = in.nextInt();
            for(int y = 0; y < ileZapytan; y++ ){
                long szukanaLiczba = in.nextLong();
                if(szukanaLiczba > tab[N-1]){
                    System.out.print("(" + N + ","+ 0 + ")"+" ");continue;
                }
                if(szukanaLiczba < tab[0]){
                    System.out.print("(" + 0 + ","+ 0 + ")"+" ");continue;
                }
                //
                int p = binarySearch(szukanaLiczba,tab,N);
                int k = binarySearch(szukanaLiczba+1,tab,N);
                System.out.print("(" + p + ","+ (k-p) + ")"+" ");

                //
            }
            System.out.println();
            //duplikaty
            int gdzieJestem=0;
            System.out.print(tab[0]+" ");
            for(int i=0;i<N;i++){
                if(tab[gdzieJestem]!=tab[i]){
                    gdzieJestem++;
                    tab[gdzieJestem]=tab[i];
                    if(gdzieJestem%50==0) { System.out.println();}
                    System.out.print(tab[i]+" ");
                    if(gdzieJestem>=199){break;}
                }
            }
            System.out.println();
            //
        }
    }
    
}
/*
test.in
8
12
-1 1 2 2 2 3 5 5 7 7
9 9
10
1 2 3 -1 4 9 5 6 7 8
10
1 2 2 2 2 2 3 3 3 3
5
1 2 3 4 0
10
0 0 0 0 0 0 0 0 0 1
4
0 -1 1 2
10
1 1 1 1 1 1 1 1 1 1
3
1 0 2
1
1
3
0 1 2
153
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152
2
3 4
6
2 2 3 3 3 3
2
2 3
9
0 0 0 3 6 9 9 9 9
5
0 1 6 8 9
test.out
(1,1) (2,3) (5,1) (0,1) (6,0) (10,2) (6,2) (8,0)
(8,2) (10,0)
-1 1 2 3 5 7 9
(0,1) (1,5) (6,4) (10,0) (0,0)
1 2 3
(0,9) (0,0) (9,1) (10,0)
0 1
(0,10) (0,0) (10,0)
1 
(0,0) (0,1) (1,0)
1 
(3,1) (4,1)
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 
50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 
100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 
150 151 152 
(0,0) (0,1) (1,0)
1 
(0,2) (2,4)
2 3 
(0,3) (3,0) (4,1) (5,0) (5,4)
0 3 6 9 
*/