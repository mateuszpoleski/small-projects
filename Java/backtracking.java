//backtracking 


class NSum{
    
    //rec
    public static int[] findNComponentsRec  (int x, int n){
        int maxEl = (int)( Math.pow((double)x, 1.0/(double)n)+ 0.000001);
        int tab[]=new int[maxEl];
        ArrayStack tmpStack = new ArrayStack(maxEl);
        if(Math.pow(maxEl, n)==x){
            int tab1[]=new int[1];
            tab1[0]=maxEl;
            return tab1;
        }
        else if(x==1){
            int tab1[]=new int[1];
            tab1[0]=1;
            return tab1;
        }
        else if(maxEl==1){
            int tab1[]=new int[0];
            return tab1;
        }
        else{
            tab = findNComponentsRecAux(x,maxEl,n,tmpStack,tab);
            return tab;
        }
    }
    //recMain
    public static int[] findNComponentsRecAux (int sum, int number, int n, ArrayStack stack,int[] tab){
        //if(number<1) return tab;
        if(number==0){//sytuacja typu 9 2 1 (number siÄ zeruje)
            if(stack.numberOfElements()==1){
                int tab1[]=new int[0];
                return tab1;
            }//nie udaĹo siÄ znaleĹşÄ szukanej sumy 
            int tSuma=sum;
            int tNumber=number;
            stack.pop();//usuwamy 1 z sumy
            int tmpTop = stack.top();
            tSuma+=power(tmpTop,n) - power(tmpTop-1,n) + 1;//sume przywracamy do wczesniejszej wartosci
            tNumber=tmpTop-1;
            stack.pop();
            stack.push(tNumber);
            return findNComponentsRecAux(tSuma,tNumber - 1,n,stack,tab);
        }
        stack.push(number);
        int tmpSuma=sum-power(number,n);
        int tmpNumber=number-1;
        if(tmpSuma==0){//znalezione rozw.
            tab = stack.StackToTab();
            return tab;  
        }
        else if(tmpNumber==0){//cofamy sie o jedna liczbe naturalna w sumie
            stack.pop();//usuwamy 1 z sumy
            int tmpTop = stack.top();
            tmpSuma+=power(tmpTop,n) - power(tmpTop-1,n) + 1;//sume przywracamy do wczesniejszej wartosci
            tmpNumber=tmpTop-1;
            stack.pop();
            stack.push(tmpNumber);
            return findNComponentsRecAux(tmpSuma,tmpNumber - 1,n,stack,tab);
        }
        else if(tmpSuma>0){
            return findNComponentsRecAux(tmpSuma,Math.min( (int)(( Math.pow((double)tmpSuma, 1.0/(double)n)+ 0.000001)) , tmpNumber ),n,stack,tab); //nasza suma jest zbyt mała, dodajemy nast.l.N 
        }
        else {//tmpSuma<0
            stack.pop();//usuwamy liczbe dodana na poczatku
            return findNComponentsRecAux(sum,tmpNumber,n,stack,tab);
        }

    }
    
    //Iter
    public static int[] findNComponentsIter (int x, int n){
        int maxEl = (int)( Math.pow((double)x, 1.0/(double)n)+ 0.000001);
        int tab[]=new int[maxEl];
        ArrayStack tmpStack = new ArrayStack(maxEl);
        int tmpNumber = maxEl;
        int tmpSuma=x;
        if(Math.pow(maxEl, n)==x){
            int tab1[]=new int[1];
            tab1[0]=maxEl;
            return tab1;
        }
        else if(x==1){
            int tab1[]=new int[1];
            tab1[0]=1;
            return tab1;
        }
        else if(maxEl==1){
            int tab1[]=new int[0];
            return tab1;
        }
        else{
            while(tmpSuma!=0){
                if(tmpNumber==0){//sytuacja typu 9 2 1 (number siÄ zeruje)
                    if(tmpStack.numberOfElements()<=1){
                        int tab1[]=new int[0];
                        return tab1;
                    }//nie udaĹo siÄ znaleĹşÄ szukanej sumy 
                    tmpStack.pop();//usuwamy 1 z sumy
                    int tmpTop = tmpStack.top();
                    tmpSuma+=power(tmpTop,n) - power(tmpTop-1,n) + 1;//sume przywracamy do wczesniejszej wartosci
                    tmpNumber=tmpTop-1;
                    tmpStack.pop();
                    tmpStack.push(tmpNumber);
                    tmpNumber = Math.min( (int)( Math.pow((double)tmpSuma, 1.0/(double)n)+ 0.000001) , tmpNumber-1 );
                    continue;
                    //
                }
                tmpStack.push(tmpNumber);
                tmpSuma-=power(tmpNumber,n);
                tmpNumber--;
                if(tmpSuma==0){//znalezione rozw.
                    tab = tmpStack.StackToTab();
                    break;
                }
                else if(tmpNumber==0){//cofamy sie o jedna liczbe naturalna w sumie
                    tmpStack.pop();//usuwamy 1 z sumy
                    int tmpTop = tmpStack.top();
                    tmpSuma+=power(tmpTop,n) - power(tmpTop-1,n) + 1;//sume przywracamy do wczesniejszej wartosci
                    tmpNumber=tmpTop-1;
                    tmpStack.pop();
                    tmpStack.push(tmpNumber);
                    //return findNComponentsRecAux(tmpSuma,tmpNumber - 1,n,tmpStack,tab);
                    tmpNumber--;
                }
                else if(tmpSuma>0);//return findNComponentsRecAux(tmpSuma,tmpNumber,n,tmpStack,tab); //nasza suma jest zbyt maĹa, dodajemy nast.l.N
                else {//tmpSuma<0
                    tmpStack.pop();//usuwamy liczbe dodana na poczatku
                    tmpSuma +=power(tmpNumber+1,n);
                }
            }
            return tab;
        }
        
    
    }
        
    public static int power(int a, int n){
        int tmp=a;
        for(int i =1;i<n;i++){
            tmp*=a;
        }
        return tmp;
    }
    
public static class ArrayStack {
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
    public void pop() {
    	if(!isEmpty())
    	{
                Stk[sTop] = 0;
    		sTop--;
    	}
    } 
    public int[] StackToTab(){
        int tmpTab[] = new int[numberOfElements()];
        System.arraycopy(Stk,0, tmpTab, 0, numberOfElements());//zwracamy stos tylko bez 0 na koĹcu
        return tmpTab;
    }

    
}
    
}

/*
test
int arr1[] = Nsum.findNComponentsRec(25, 2); // arr1 = {4, 3}
int arr2[] = Nsum.findNComponentsRec(225, 3); // arr2 = {6, 2, 1}
int arr3[] = Nsum.findNComponentsRec(10000, 4); // arr3 = {10}
int arr4[] = Nsum.findNComponentsRec(399, 2); // arr4 = {19, 5, 3, 2}
int arr5[] = Nsum.findNComponentsRec(21, 3); // arr5 = {}
int arr6[] = Nsum.findNComponentsIter(25, 2); // arr6 = {4, 3}
int arr7[] = Nsum.findNComponentsIter(225, 3); // arr7 = {6, 2, 1}
int arr8[] = Nsum.findNComponentsIter(10000, 4); // arr8 = {10}
int arr9[] = Nsum.findNComponentsIter(399, 2); // arr9 = {19, 5, 3, 2}
int arr10[] = Nsum.findNComponentsIter(21, 3); // arr10 = {}
int arr11[] = Nsum.findNComponentsRec(93, 2); // arr11 = {2,5,8}
int arr12[] = Nsum.findNComponentsIter(93, 2); // arr12 = {2,5,8}
int arr13[] = Nsum.findNComponentsIter(242, 20); // arr13 = {}
int arr14[] = Nsum.findNComponentsRec(242, 20); // arr14 = {}

*/