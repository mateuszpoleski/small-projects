//two dimensional kadane algorithm with some modification
package source;
import java.util.Scanner;

public class Source {
    
    public static Scanner in = new Scanner(System.in); 

    public static void main(String[] args) {
        
        int ileTestow = in.nextInt();
         
        for(int x = 0; x<ileTestow; x++)
        {   
            boolean flag = true;
            boolean czyZero = true;
            int xZero,yZero;
            int lewo,prawo,gora,dol,suma,wiersze,kolumny;
            int b1,e1,max1,curr,b2;
            lewo = prawo = dol = gora = suma = xZero = yZero = 0;
            wiersze = in.nextInt();
            kolumny = in.nextInt(); 
            
            int[][] tab = new int[wiersze][kolumny];
            int[] tmp = new int[wiersze];
            for (int i = 0; i < wiersze; i++) {
                for (int j = 0; j < kolumny; j++) {
                    tab[i][j] = in.nextInt();
                    if(tab[i][j] >= 0) flag=false;
                    if(czyZero && tab[i][j] == 0) { czyZero=false; xZero=i; yZero=j; }
                }
            }
            if(flag) { System.out.println("empty"); continue; }
            //
            for(int L = 0;L<kolumny;L++){
                for(int P=L; P<kolumny;P++){
                    b1 = b2 = curr = e1 = max1 = 0;
                    if(L == P){
                        for(int i = 0; i< wiersze; i++){
                            tmp[i]=tab[i][L];
                        }
                    }
                    else{
                        for(int i = 0; i< wiersze; i++){
                            tmp[i]+=tab[i][P];
                        }
                    }
                        for (int i=0; i < wiersze; i++){
                             curr = curr + tmp[i];
                             if (curr <= 0) {
                                curr = 0;
                                b2 = i+1;
                             }
                             else
                             if (curr > max1) {
                                max1 = curr;
                                b1 = b2;
                                e1 = i;
                             }
                             else if( curr == max1 && e1-b1 > i-b2){
                                max1 = curr;
                                b1 = b2;
                                e1 = i;
                             }
                        }
                        if(max1 > suma){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                        else if(max1 == suma && (prawo - lewo + 1)*(dol - gora + 1) > (P - L + 1)*(e1-b1 + 1)){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                        else if(max1 == suma && gora > b1 && (prawo - lewo + 1)*(dol - gora + 1) == (P - L + 1)*(e1-b1 + 1)){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                        else if(max1 == suma && gora >= b1 && dol > e1 && (prawo - lewo + 1)*(dol - gora + 1) == (P - L + 1)*(e1-b1 + 1)){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                        else if(max1 == suma && gora >= b1 && dol >= e1 && lewo > L && (prawo - lewo + 1)*(dol - gora + 1) == (P - L + 1)*(e1-b1 + 1)){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                        else if(max1 == suma && gora >= b1 && dol >= e1 && lewo >= L && prawo > P && (prawo - lewo + 1)*(dol - gora + 1) == (P - L + 1)*(e1-b1 + 1)){
                            suma = max1;
                            lewo = L;
                            prawo = P;
                            gora = b1;
                            dol = e1;
                        }
                }
                     
            }
            //
            if(suma==0){
                System.out.println("[" + xZero + ".." + xZero + "," + yZero + ".." + yZero + "]");
                System.out.println("max_sum=" + suma);
            }
            else{
                System.out.println("[" + gora + ".." + dol + "," + lewo + ".." + prawo + "]");
                System.out.println("max_sum=" + suma);
            }
        }
    }
    
}
/*
test.in:
12
2 6
 2 2 -3 -1 0 -1
 2 2 -1 -2 8 -1
2 5
 0 -1 1 1 1
 6 -2 1 1 1
3 5
 0 -1 -1 7 0
 7 -7 -1 0 0
-1 -2 -3 -4 -5
1 5
 -1 -2 -3 -1 -2
2 2
 0 0 
 0 0 
3 6
 0 0 0 -2 2 2
 0 2 2 -7 2 2
 0 2 2 -2 0 0
4 8
 -1 10 -3 5 -4 -8 3 -3
 8 -2 -6 -8 2 -5 4 1
 3 -2 9 -9 -1 10 -5 2
 1 -3 5 -7 8 -2 2 -6
2 2
 -2 0
 0 -2
1 8
 -2 7 -4 8 -5 4 1 -3
1 1
 8 
3 3
 1 1 1
 1 -5 -5
 1 -5 -5
4 1
 1 2 -3 3
test.out:
[1..1,0..4]
max_sum=9
[0..1,0..4]
max_sum=9
[0..0,3..3]
max_sum=7
empty
[0..0,0..0]
max_sum=0
[0..1,4..5]
max_sum=8
[0..3,0..2]
max_sum=19
[0..0,1..1]
max_sum=0
[0..0,1..3]
max_sum=11
[0..0,0..0]
max_sum=8
[0..0,0..2]
max_sum=3
[3..3,0..0]
max_sum=3
*/