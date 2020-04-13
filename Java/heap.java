//heap with modyfications

import java.util.Scanner;


public class Source {

    public static Scanner in = new Scanner(System.in);
    
    public static void main(String[] args) {
        int z = in.nextInt();//ilosc zestawow
        for(int k=0;k<z;k++){
            int N = in.nextInt();
            int P = in.nextInt();
            Heap heap = new Heap(N,P);
            String command = "";
            while(!command.equals("s")){
                command = in.next();
                int arg;
                switch(command){
                    case "i":
                        arg = in.nextInt();
                        int n;
                        for(int i = 0;i<arg;i++){
                            n=in.nextInt();
                            heap.insert(new Node(n));
                        }
                        break;
                    case "g":
                        arg = in.nextInt();
                        heap.removeMax(arg);
                        break;
                    case "s":
                        heap.sort();
                       break;
                } 
            }
        }
        
    }
    
}
//
class Node{
    public int key;
    public int count;
    public int index;
    Node(int key){
        this.key = key;
        this.index = 0;
        this.count = 1;
    }
    Node(){
        this.index = 0;
        this.key = 0;
        this.count = 1;
    }
    void incrCount(){
        this.count++;
    }
}
//

class Tree
{	
    private class TreeNode{
    public TreeNode l,r;
    public Node value;

    public TreeNode(Node _value) {
            this.value = _value;
            l = r = null;
    }
}
	TreeNode root;

	public Tree() {
		root = null;
	}

	public Tree(Node root_value) {
		root = new TreeNode(root_value);
	}

        public int insert(Node x,Boolean czyMiejsce){
            TreeNode curr,prev,s;
            s = new TreeNode(x);
            if(root == null && czyMiejsce) { root = s; return -1;}//puste drzewo
            else{
                curr = root; prev = null;
                while(curr != null){
                    prev = curr; // przechowuje index wczesniejszy przed nullem na ktory wstawiam nowy node
                    if(x.key < curr.value.key) curr = curr.l;
                    else if(x.key > curr.value.key) curr = curr.r;
                    else { curr.value.incrCount() ;return curr.value.index;}
                }
                if(czyMiejsce){
                    if(x.key < prev.value.key) prev.l = s;
                    else prev.r = s;
                    return -1;
                }
                else return -2;
            }
            
	}
        public void delete(Node x){
            if (root == null) return; 
            TreeNode curr = root;
            TreeNode prev = null;
            Boolean dir = false;
            while(curr != null){ 
                if(x.key < curr.value.key) { prev = curr ; curr = curr.l; dir = true;}
                else if(x.key > curr.value.key) { prev = curr ; curr = curr.r; dir = false;}
                else break; //znalezlismy x
            }
            if(curr == null) return; //nie ma takiej wartosc
            //1.Node nie ma dzieci
            if(curr.l == null && curr.r == null){
                if(curr.value.key == root.value.key) { root = null; return;} // usuwamy korzen
                if(dir) prev.l = null;
                else prev.r = null;
            }
            //2.Node ma tylko jedno dziecko
            else if(curr.l == null) { 
                    if(curr.value.key == root.value.key) { root = curr.r; return;} // usuwamy korzen
                    curr = curr.r;
                    if(dir) prev.l = curr;
                    else prev.r = curr;
            }//rodzic staje siÄ dzieckiem
            else if(curr.r == null){ 
                    if(curr.value.key == root.value.key) { root = curr.l; return;} // usuwamy korzen
                    curr = curr.l;
                    if(dir) prev.l = curr;
                    else prev.r = curr;
            }
            //3.Node ma dwoje dzieci
            else if(false){//losowe wybranie strony    
                
            }
            else{
                TreeNode curr2 = curr.r;
                prev = curr;
                while(curr2.l != null){ //szukanie max z l
                    prev = curr2;
                    curr2 = curr2.l;
                }
                curr.value.key = curr2.value.key;
                //usuniecie max
                if(curr.value.key == prev.value.key){//while sie nie wykonal i prev == curr
                    curr.r = curr2.r;
                }
                else if(curr2.l == null && curr2.r == null){
                    if(prev.value.key > curr2.value.key) prev.l = null;
                    else prev.r = null;
                }
                else if(curr2.l == null) { 
                        curr2 = curr2.r;
                        if(prev.value.key > curr2.value.key) prev.l = curr2;
                        else prev.r = curr2;
                }
                else if(curr2.r == null){ 
                        curr2 = curr2.l;
                        if(prev.value.key > curr2.value.key) prev.l = curr2;
                        else prev.r = curr2;
                }
            }        
        }
        

    
    
}
//
class Heap {
    
	
	public Node[] arr;
        public Tree tree;
	public int N;//max liczba roznych
        public int P;//max liczba laczna
        public int actSize;//aktualny rozmiar
        public int actN;
        
	
	public Heap(int N,int P) {
		this.arr = new Node[N];
                this.P = P;
                this.N = N;
                this.actSize = 0;
                this.actN = 0;
                this.tree = new Tree();
	}
	

	public void upheap(int k) {
		int i = (k-1)/2; //indeks przodka elementu a[k]
                Node tmp = arr[k];
                while(( k>0 && arr[i].count<tmp.count ) || 
                        (k>0 && (arr[i].count == tmp.count && arr[i].key<tmp.key)) ){
                    arr[k] = arr[i];
                    arr[k].index=k;
                    k = i; //przeniesienie wezla w dol
                    i = (i-1)/2;  //przejscie do przodka
                }
                arr[k] = tmp; // teraz a[k] ma swoje miejsce
                arr[k].index=k;
	}


	public void downheap(int k) {
		int j;
                Node tmp = arr[k];
                while(k < actN/2){
                    j = 2*k+1;
                    if(j < actN-1 && arr[j].count<arr[j+1].count || j < actN-1 && ( arr[j].count==arr[j+1].count && arr[j].key<arr[j+1].key) ) j++; 
                    if(tmp.count > arr[j].count || tmp.count == arr[j].count && tmp.key > arr[j].key ) break;
                    arr[k] = arr[j];
                    arr[k].index = k;
                    k = j;
                }
                arr[k] = tmp;
                arr[k].index = k;
	}


	public void insert(Node v) {
		if(actSize != P){
                    int flag = tree.insert(v,actN!=N);
                    if(flag==-1){
                       v.index = actN; 
                       arr[actN] = v;
                       upheap(actN);
                       actN++;
                    }
                    else if(flag>0){
                        upheap(flag);
                    }
                    if(flag!=-2) actSize++;
                }
	}
	

	public void removeMax(int n) {
            if(actSize==0) System.out.println("0 0"); 
            else{
                Node tmp = getMax();
                if(tmp.count>n){
                    System.out.println(tmp.key+" "+n); 
                    tmp.count-=n;
                    downheap(0);
                    actSize-=n;
                }
                else{
                    System.out.println(tmp.key+" "+tmp.count);
                    actSize-=tmp.count;
                    tree.delete(tmp);
                    arr[0] = arr[actN-1];
                    arr[0].index = 0;
                    actN--;
                    downheap(0);
                }
            }
	}
	

	public Node getMax() {
		return arr[0];
	}
	

	public int size() {
		return actSize;
	}
	

	public int height() {
		return (int)Math.floor(Math.log(actSize)/Math.log(2));
	}
        public void print(){
            for(int i =0;i<actN;i++){
                System.out.print(arr[i].count+":"+arr[i].key+" ");
            }
            System.out.println();
        }
        public void sort(){
             if(actSize==0) System.out.println("0 0"); 
             else{
                while (actN > 0) {
                    System.out.print(arr[0].key+" "+arr[0].count+" "); 
                    Node tmp = arr[0];
                    arr[0] = arr[actN-1];
                    arr[actN-1] = tmp;
                    actN-- ;
                    downheap(0);
                    }
                System.out.println();

                }
        }
}

/*
test.in
2
5 15
g 2
i 2 1 1
g 1
i 3 2 3 4
g 2
i 7 4 4 4 4 4 1 3
g 3
i 9 2 6 1 6 7 7 7 7 2
g 2
s


8 15
i 10 1 2 3 4 5 6 7 8 9 10
g 2
g 1
g 5
i 10 1 1 1 1 1 1 1 1 4 4
g 3
i 15 1 1 1 1 1 1 1 1 1 1 1 1 3 3 3
g 30
g 2
i 11 3 3 3 5 5 5 5 10 10 2 1
s

test.out
0 0
1 1
4 1
4 3
2 2
1 3 6 2 4 2 3 2 2 1 
8 1
7 1
6 1
1 3
1 9
4 2
5 5 3 4 10 2 2 2 4 1 1 1 
*/