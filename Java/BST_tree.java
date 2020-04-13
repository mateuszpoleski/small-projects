//BST Trees with modifications

import java.util.Scanner;

public class Source {

    public static Scanner in = new Scanner(System.in);
    
    public static void main(String[] args) {
        int z = in.nextInt();
        for(int k=0;k<z;k++){
            Tree tree = new Tree();
            int n = in.nextInt();//liczba wierzcholkow
            String order = in.next();
            if(order.equals("PREORDER")){//tworzenie drzewa
                for(int a=0;a<n;a++){
                    int inpt = in.nextInt();
                    tree.insertR(inpt);
                }
            }
            else{//jesli postorder to najpierw na stos a potem normalnie
                ArrayStack stack = new ArrayStack(n);
                for(int a=0;a<n;a++){
                    stack.push(in.nextInt());
                }
                while(!stack.isEmpty()){
                    tree.insertR(stack.pop());
                }
            }
            int m = in.nextInt();//liczba polecen
            System.out.println("ZESTAW: "+(k+1));
            int arg = 0;
            for(int p=0;p<m;p++){
               //
                String com = in.next();
                if(com.equals("PARENT") || com.equals("INSERT") || com.equals("DELETE") || com.equals("SUCCESSOR") || com.equals("PREDECESSOR"))arg = in.nextInt();
                //
                switch(com){
                    case "PREORDER": 
                        System.out.print("PREORDER: ");
                        tree.preorder();
                        break;
                    case "INORDER": 
                        System.out.print("INORDER: ");
                        tree.inorder();
                        break;
                    case "POSTORDER": 
                        System.out.print("POSTORDER: ");
                        tree.postorder();
                        break;
                    case "LEVELORDER": 
                        System.out.print("LEVELORDER: ");
                        tree.levelorder();
                        break;
                    case "PARENT": 
                        int ans = tree.parent(arg);
                        if(ans != arg) System.out.println("PARENT "+arg+": "+ans);
                        else System.out.println("PARENT "+arg+": "+"BRAK");
                        break;
                    case "INSERT":
                        tree.insert(arg);
                        break;
                    case "DELETE":
                        tree.delete(arg);
                        break;
                    case "SUCCESSOR":
                        ans = tree.sucessor(arg);
                        if(ans != arg) System.out.println("SUCCESSOR "+arg+": "+ans);
                        else System.out.println("SUCCESSOR "+arg+": "+"BRAK");
                        break;
                    case "PREDECESSOR":
                        ans = tree.predecessor(arg);
                        if(ans != arg) System.out.println("PREDECESSOR "+arg+": "+ans);
                        else System.out.println("PREDECESSOR "+arg+": "+"BRAK");
                        break;
                    case "DISPLAY":
                        System.out.print("DISPLAY: ");
                        tree.display(tree.root, 0);
                        break;
               
                }
            }
            
        }
    }
    
}

class Node{
    public Node l,r;
    public int value;

    public Node(int _value) {
            this.value = _value;
            l = r = null;
    }
}
class Tree
{	
	Node root;

        //Tworzy puste drzewo
	public Tree() {
		root = null;
	}

	//Tworzy drzewo z wartoscia dla korzenia 
	public Tree(int root_value) {
		root = new Node(root_value);
	}

	//wstawianie rec. do tworzenia drzewa
        private Node insertRec(Node curr, int value){
            if(curr==null){
                return new Node(value);
            }
            if(value < curr.value){//curr > value
                curr.l = insertRec(curr.l,value);
            }
            else if(value > curr.value){//curr < value
                curr.r = insertRec(curr.r,value);
            }
            else{//juz jest taki element
                return curr;
            }
            return curr;
        }
	public void insertR(int v) {
		root = insertRec(root,v);      
	}
        public void preorder(){//korzen->L->R
            MyStack stack = new MyStack();
            Node curr = root;
            stack.push(curr);
            if(curr == null) return;
            while(!stack.isEmpty()){
                curr = stack.pop();
                System.out.print(curr.value+ " ");
                if(curr.r != null) stack.push(curr.r);
                if(curr.l != null) stack.push(curr.l);
            }
            System.out.println();
	}
        public void inorder(){//lewa->korzen->prawa
            MyStack stack = new MyStack();
            Node curr = root;
            while(curr != null || !stack.isEmpty()){
                if(curr != null){
                    stack.push(curr);//przechodze na lewo wszystko dajac na stos
                    curr = curr.l;
                }
                else{
                    curr = stack.pop();//wypisuje wartosc i przechodze na prawo
                    System.out.print(curr.value+" ");
                    curr = curr.r;
                }
            }
            System.out.println();
	}
        public void postorder(){//taki preorder tylko od prawej do lewej i czytany od konca :> lewa->prawa->korzen
            MyStack stack = new MyStack();
            MyStack stack2 = new MyStack();
            Node curr = root;
            stack.push(curr);
            if(curr == null) return;
            while(!stack.isEmpty()){
                curr = stack.pop();
                stack2.push(curr);
                if(curr.l != null) stack.push(curr.l);
                if(curr.r != null) stack.push(curr.r);
            }
            while(!stack2.isEmpty()){
                curr = stack2.pop();
                System.out.print(curr.value+" ");
            }
            System.out.println();
	}
        public void levelorder(){
            LinkedDoublyQueue q = new LinkedDoublyQueue();
            if(root==null) return;
            q.insertTail(root);
            while(!q.isEmpty()){
                Node curr = q.removeHead();//idziemy po kolei i wypisujemy,a to co zostaje to do kolejki
                System.out.print(curr.value+" ");
                if(curr.l != null) q.insertTail(curr.l);
                if(curr.r != null) q.insertTail(curr.r);
            }
            System.out.println();
	}
        public int parent(int x){
            Node curr,prev;
            curr = root; prev = null;
            if(root == null || root.value == x){
                return x;//nie ma rodzica dla x
            }
            while(curr != null){
               if(x < curr.value){
                   prev = curr;
                   curr = curr.l;
               }
               else if(x > curr.value){
                   prev = curr;
                   curr = curr.r;
               }
               else return prev.value;//
            }
            return x;//nie ma x
	}
        public void insert(int x){
            Node curr,prev,s;
            s = new Node(x);
            if(root == null) root = s;//puste drzewo
            else{
                curr = root; prev = null;
                while(curr != null){
                    prev = curr; // przechowuje index wczesniejszy przed nullem na ktory wstawiam nowy node
                    if(x < curr.value) curr = curr.l;
                    else if(x > curr.value) curr = curr.r;
                    else return;//jest juz taki element
                }
                if(x < prev.value) prev.l = s;
                else prev.r = s;
            }
            
	}
        public void delete(int x){
            if (root == null) return; 
            Node curr = root;
            Node prev = null;
            Boolean dir = false;
            while(curr != null){ 
                if(x < curr.value) { prev = curr ; curr = curr.l; dir = true;}
                else if(x > curr.value) { prev = curr ; curr = curr.r; dir = false;}
                else break; //znalezlismy x
            }
            if(curr == null) return; //nie ma takiej wartosc
            //1.Node nie ma dzieci
            if(curr.l == null && curr.r == null){
                if(curr.value == root.value) { root = null; return;} // usuwamy korzen
                if(dir) prev.l = null;
                else prev.r = null;
            }
            //2.Node ma tylko jedno dziecko
            else if(curr.l == null) { 
                    if(curr.value == root.value) { root = curr.r; return;} // usuwamy korzen
                    curr = curr.r;
                    if(dir) prev.l = curr;
                    else prev.r = curr;
            }//rodzic staje siÄ dzieckiem
            else if(curr.r == null){ 
                    if(curr.value == root.value) { root = curr.l; return;} // usuwamy korzen
                    curr = curr.l;
                    if(dir) prev.l = curr;
                    else prev.r = curr;
            }
            //3.Node ma dwoje dzieci
            else if(false){//losowe wybranie strony    
                //curr.value%2==1
                Node curr2 = curr.l;
                prev = curr;
                while(curr2.r != null){ //szukanie max z l
                    prev = curr2;
                    curr2 = curr2.r;
                }
                curr.value = curr2.value;
                //usuniecie max
                if(curr.value == prev.value){//while sie nie wykonal i prev == curr
                    curr.l = curr2.l;
                }
                else if(curr2.l == null && curr2.r == null){
                    if(prev.value > curr2.value) prev.l = null;
                    else prev.r = null;
                }
                else if(curr2.l == null) { 
                        curr2 = curr2.r;
                        if(prev.value > curr2.value) prev.l = curr2;
                        else prev.r = curr2;
                }
                else if(curr2.r == null){ 
                        curr2 = curr2.l;
                        if(prev.value > curr2.value) prev.l = curr2;
                        else prev.r = curr2;
                }
            }
            else{
                Node curr2 = curr.r;
                prev = curr;
                while(curr2.l != null){ //szukanie max z l
                    prev = curr2;
                    curr2 = curr2.l;
                }
                curr.value = curr2.value;
                //usuniecie max
                if(curr.value == prev.value){//while sie nie wykonal i prev == curr
                    curr.r = curr2.r;
                }
                else if(curr2.l == null && curr2.r == null){
                    if(prev.value > curr2.value) prev.l = null;
                    else prev.r = null;
                }
                else if(curr2.l == null) { 
                        curr2 = curr2.r;
                        if(prev.value > curr2.value) prev.l = curr2;
                        else prev.r = curr2;
                }
                else if(curr2.r == null){ 
                        curr2 = curr2.l;
                        if(prev.value > curr2.value) prev.l = curr2;
                        else prev.r = curr2;
                }
            }        
        }
        public int sucessor(int x){
            if (root == null) return x; 
            Node curr = root;
            while(curr != null){ 
                if(x < curr.value) curr = curr.l;
                else if(x > curr.value) curr = curr.r;
                else break; //znalezlismy x
            }
            if(curr == null) return x;
            if(curr.r != null){
                curr = curr.r;
                while(curr.l != null) curr = curr.l; //minimum z prawego drzewa
                return curr.value;
            }
            else{//szukamy wiekszwgo rodzica
                int value = curr.value;
                int newValue;
                do{
                    newValue = parent(value);
                    if(value == newValue) return x;
                    value = newValue;
                }
                while(value<curr.value);
                return value;
            }
        }
        public int predecessor(int x){
            if (root == null) return x; 
            Node curr = root;
            while(curr != null){ 
                if(x < curr.value) curr = curr.l;
                else if(x > curr.value) curr = curr.r;
                else break; //znalezlismy x
            }
            if(curr == null) return x;
            if(curr.l != null){
                curr = curr.l;
                while(curr.r != null) curr = curr.r; //minimum z prawego drzewa
                return curr.value;
            }
            else{
                int value = curr.value;
                int newValue;
                do{
                    newValue = parent(value);
                    if(value == newValue) return x;
                    value = newValue;
                }
                while(value>curr.value);
                return value;
            }
        }
        public void display(Node p, int h){
            if(p != null){
                display(p.r, h+1);
                for(int j=0; j<h; j++) System.out.print(' ');
                System.out.println(p.value);
                display(p.l, h+1);
            }
        } 

    
    
}
/*






















*/

    
class MyStack {
	private class StkNode {
		Node v;
		StkNode next;
		public StkNode(Node v) {
			this.v = v;
		}
	}
	
	private int size;
	private StkNode head;
	
	public MyStack() {
		size = 0;
		head = null;
	}
	
	
	public int size() {
		return size;
	}
	
	public boolean isEmpty() {
		return size == 0;
	}
	
	public void push(Node v) {
		StkNode newNode = new StkNode(v);
		if (head == null) {
			head = newNode;
		} else {
			newNode.next = head;
			head = newNode;
		}
		size++;
	}

	public Node pop() {
		if (head == null) return null;
		
		StkNode n = head;
		head = head.next;
		size--;
		
		return n.v;
	}
	
	public Node peek() {
		if (head == null) return null;
		
		return head.v;
	}
}

class ArrayStack {
	private int maxSize;
	private int[] Stk;
	private int sTop;
        
    public void show(){
    	if(!isEmpty())
    	{
    		for(int i=0;i<=sTop;i++)
    		{
    			System.out.print(Stk[i]+" ");
    		}
	        System.out.println();
    	}
    }
    /** 
     * Tworzy pusty stos o maksymalnym rozmiarze maxSize.
     */
    public ArrayStack(int _maxSize) {
    	maxSize=_maxSize;
    	Stk=new int[_maxSize];
    	sTop=-1;
    }
    /**
     * Sprawdza, czy stos jest pusty.
     */
    public boolean isEmpty() {
        if(sTop==-1) return true;
        return false;
    }
    /**
     * Sprawdza, czy stos jest peĹny.
     */
    public boolean isFull() {
    	if(sTop==maxSize-1) return true;
        return false;
    }
    /**
     * Zwraca aktualnÄ liczbÄ elementĂłw w stosie.
     */
    public int numberOfElements() {
        return sTop+1;
    }
    /**
     * Wstawia element x na szczyt stosu.
     */
    public void push(int x) {
    	if(!isFull())
    	{
    		sTop++;
    		Stk[sTop]=x;
    	}
    }
    /**
     * Zwraca wartoĹÄ na sczycie stosu.
     */
    public int top() {
    	if(!isEmpty())
    	{
    		return Stk[sTop];
    	}
    	else return -1;
    }
    /**
     * Zwraca wartoĹÄ na szczycie stosu jednoczeĹnie go usuwajÄc.
     */
    public int pop() {
    	if(!isEmpty())
    	{
    		sTop--;
    		return Stk[sTop+1];
    	}
        return 0;
    } 

    
}

class LNode
{
	public Node data;
	public LNode next;
	public LNode prev;
	LNode(Node x){
		data=x;
                prev=null;
		next=null;
	}
}

class LinkedDoublyQueue {
    private LNode head;
    private LNode tail;
    private int size;
     

    public LinkedDoublyQueue() {
    	head=null;
    	tail=null;
        size = 0;
    }

    public void insertHead(Node x) {
    	LNode tmp=new LNode(x);
    	if(!isEmpty()){
    		head.prev=tmp;
    		tmp.next=head;
                head = tmp;
    	}
    	else{
    		head=tail=tmp;
    	}
        size++;
    }
    /**
     * Wstawia element x na koniec kolejki.
     */
    public void insertTail(Node x) {
    	LNode tmp=new LNode(x);
    	if(!isEmpty()){
    		tail.next=tmp;
    		tmp.prev=tail;
                tail = tmp;
    	}
    	else{
    		head=tail=tmp;
    	}
        size++;
    } 
    public Node removeHead() {
    	if(!isEmpty()){
            Node x=head.data;
            if(head.next!=null){
            	head=head.next;
            	head.prev=null;
                size--;
                return x;
            }
            else {
                head=tail=null;//tylko 1 el.
                size--;
                return x;
            }
	        
    	}
    	else return null;
    }
   
    public Node removeTail() {
        if(!isEmpty())
        {
        	Node x=tail.data;
        	if(tail.prev!=null){
        		tail=tail.prev;
        		tail.next=null;
                        size--;
                        return x;
        	}
        	else {
                    head=tail=null;//jeden element
                    size--;
                    return x;
                }
        }
        return null;
    }
    public boolean isEmpty() {
    	return head==null;
    } 
    public int numberOfElements() {
    	return size;
    }

	 
}
/*
test.in
1
10
PREORDER
50 25 12 37 30 33 43 75 87 93
13
POSTORDER
LEVELORDER
PARENT 33
SUCCESSOR 50
PREDECESSOR 50
PARENT 50
DELETE 50
PARENT 50
POSTORDER
LEVELORDER
INSERT 35
INORDER
LEVELORDER
test.out
ZESTAW: 1
POSTORDER: 12 33 30 43 37 25 93 87 75 50 
LEVELORDER: 50 25 75 12 37 87 30 43 93 33 
PARENT 33: 30
SUCCESSOR 50: 75
PREDECESSOR 50: 43
PARENT 50: BRAK
PARENT 50: BRAK
POSTORDER: 12 33 30 43 37 25 93 87 75 
LEVELORDER: 75 25 87 12 37 93 30 43 33 
INORDER: 12 25 30 33 35 37 43 75 87 93 
LEVELORDER: 75 25 87 12 37 93 30 43 33 35 
*/