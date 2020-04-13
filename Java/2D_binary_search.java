//multidimensional binary search

import java.util.Scanner;

public class Source {
    public static int binarySearchRekFirst(int x ,int[] a,int f ,int l){
        if(a[f]>x || a[l]<x) return -1;
        if(a[f]==x) return f;
        if(f+1==l){
            if(a[f]==x) return f;
            else if(a[l]==x) return l;
            else return -1;
        }
        int s = (f+l)/2;
        if(a[s]==x && a[s-1]!=x) return s;
        else if(a[s]<x) return binarySearchRekFirst(x,a,s,l);
        else return binarySearchRekFirst(x,a,f,s);
    }
    public static int binarySearchRekLast(int x ,int[] a,int f ,int l){
        if(a[f]>x || a[l]<x) return -1;
        if(a[l]==x) return l;
        if(f+1==l){
            if(a[l]==x) return l;
            else if(a[f]==x) return f;
            else return -1;
        }
        int s = (f+l)/2;
        if(a[s]==x && a[s+1]!=x) return s;
        else if(a[s]>x) return binarySearchRekLast(x,a,f,s);
        else return binarySearchRekLast(x,a,s,l);
    }
    public static void binarySearchRekF(int x, int [][] a, int n,int m,int i){
        int tmp = binarySearchRekFirst(x,a[i],0,m-1);
        if(tmp >= 0) System.out.println("RekPier: "+x+" w "+"("+i+","+tmp+")");
        else if(i<n-1) binarySearchRekF(x,a,n,m,++i);
        else System.out.println("RekPier: nie ma "+x);
    }
    public static void binarySearchRekL(int x, int [][] a, int n,int m,int i){
        int tmp = binarySearchRekLast(x,a[i],0,m-1);
        if(tmp >= 0) System.out.println("RekOst: "+x+" w "+"("+i+","+tmp+")");
        else if(i>0) binarySearchRekL(x,a,n,m,--i);
        else System.out.println("RekOst: nie ma "+x);
    }
    public static void binarySearchIterFirst(int x,int [][] a, int n,int m){
        for(int i = 0; i < n; i++){
            int tmp[] = a[i];
            int f = 0;
            int l = m-1;
            int s;
            if(tmp[0]==x) { System.out.println("IterPier: "+x+" w "+"("+i+","+0+")"); return; }
            else if(f==l && i == n-1) { System.out.println("IterPier: nie ma "+x); return; }
            else if(f==l && i != n-1) continue;
            while(true){
                s = (f+l)/2;
                if(f+1==l){
                    if(tmp[f]==x) { System.out.println("IterPier: "+x+" w "+"("+i+","+f+")"); return; }
                    else if(tmp[l]==x) { System.out.println("IterPier: "+x+" w "+"("+i+","+l+")"); return; }
                    else if(i == n-1) { System.out.println("IterPier: nie ma "+x); return; }
                    else break;
                }
                if(tmp[s]==x && tmp[s-1]!=x) { System.out.println("IterPier: "+x+" w "+"("+i+","+s+")"); return; }
                else if(tmp[s]<x) f=s;
                else l=s;
            }
        }
    }
    public static void binarySearchIterLast(int x,int [][] a, int n,int m){
        for(int i = n-1; i >= 0; i--){
            int tmp[] = a[i];
            int f = 0;
            int l = m-1;
            int s;
            if(tmp[m-1]==x) { System.out.println("IterOst: "+x+" w "+"("+i+","+(m-1)+")"); return; }
            else if(f==l && i == 0) { System.out.println("IterOst: nie ma "+x); return; }
            else if(f==l && i != 0) continue;
            while(true){
                s = (f+l)/2;
                if(f+1==l){
                    if(tmp[l]==x) { System.out.println("IterOst: "+x+" w "+"("+i+","+l+")"); return; }
                    else if(tmp[f]==x) { System.out.println("IterOst: "+x+" w "+"("+i+","+f+")"); return; }
                    else if(i == 0) { System.out.println("IterOst: nie ma "+x); return; }
                    else break;
                }
                if(tmp[s]==x && tmp[s+1]!=x) { System.out.println("IterOst: "+x+" w "+"("+i+","+s+")"); return; }
                else if(tmp[s]>x) l=s;
                else f=s;
            }
        }
    }
    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        int z = in.nextInt();
        in.nextLine();
        for(int x=0;x<z;x++){
            int n = in.nextInt();
            int m = in.nextInt();
            int tab[][] = new int[n][m];
            for(int y = 0;y<n;y++){
                for(int l=0;l<m;l++){
                    tab[y][l]=in.nextInt();
                }
            }
            int var = in.nextInt();
            binarySearchRekF(var,tab,n,m,0);
            binarySearchRekL(var,tab,n,m,n-1);
            binarySearchIterFirst(var,tab,n,m);
            binarySearchIterLast(var,tab,n,m);
            System.out.println("---");
        }
    }
    
}
/* 
test.in
3
2 3
10 10 10
10 10 10
10
4 3
10 10 10
10 20 30
20 30 30
40 40 40
20
2 2
10 10
10 10
20
test.out
RekPier: 10 w (0,0)
RekOst: 10 w (1,2)
IterPier: 10 w (0,0)
IterLast: 10 w (1,2)
---
RekPier: 20 w (1,1)
RekOst: 20 w (2,0)
IterPier: 20 w (1,1)
IterLast: 20 w (2,0)
---
RekPier: nie ma 20
RekOst: nie ma 20
IterFirst: nie ma 20
IterLast: nie ma 20
---
*/

