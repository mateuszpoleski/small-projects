//conversions RPN <==> INF
package source;
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);
    
    public static void main(String[] args) {
        int z = in.nextInt();
        in.nextLine();
        for(int x=0;x<z;x++){
            String tmpString = in.nextLine();
            Boolean ONP = false;
            //naprawa wczytanego napisu
            char[] expr = tmpString.toCharArray();
            int exprLength = 0;
            if(expr[0]=='O') ONP=true;
            for(int y = 0;y<tmpString.length();y++){
                if( isOperator2(tmpString.charAt(y)) || isNum(tmpString.charAt(y)) || isUnaryOprator(tmpString.charAt(y)) || isBrackets(tmpString.charAt(y)) ){
                   if( isBrackets(tmpString.charAt(y)) && ONP) continue; //nawias w ONP nie przechodzi 
                   expr[exprLength] = tmpString.charAt(y);
                    exprLength++;
                }
            }
            //
            //spr. czy poprawne algebraicznie
            if(ONP){
                if( isOnpRight(expr,exprLength) ){
                    onpToInf(expr,exprLength);
                            
                }
                else{
                    System.out.println("INF: error");
                }
            }
            else{
                if( isInfRight(expr,exprLength) ){
                    infToOnp(expr,exprLength);
                }
                else{
                    System.out.println("ONP: error");
                }
            }



        }
        
    }
    public static void infToOnp(char[] token, int size){
        String result="";
        ArrayCharStack charStack=new ArrayCharStack(256);
        for(int i=0;i<size;i++){
            if( isNum(token[i]) ) result+=token[i]; // znak to litera(cyfra)-przepisujemy na wyjście
            else{//operator || nawias
                if(!isBrackets(token[i])){//operator
                    if(!charStack.isEmpty() && charStack.top()!='('){// && ')' 
                        while(!charStack.isEmpty() && charStack.top()!='(' && ( (isLeft(token[i]) && returnPri(charStack.top())>=returnPri(token[i]))   ||   (!isLeft(token[i]) && returnPri(charStack.top())>returnPri(token[i])) ) ){
                            //przepisujemy operatory ze stosu aż nawias albo na stosie większy priorytet niż nasz aktualny (jeśli łączność lewo.str. to >=, prawo to > )
                            result+=charStack.pop();
                        }
                    }
                    charStack.push(token[i]); // na koniec operator na stos
                }
                else if( token[i]=='(' ) charStack.push(token[i]);
                else if( token[i]==')' ){ // przepisujemy wszystko ze stosu aż do nawiasu
                    while(charStack.top()!='(' && !charStack.isEmpty()){
                        result+=charStack.pop();
                    }
                    charStack.pop();//usuwamy ')'
                }
            }
        }
        while(!charStack.isEmpty()){
            result+=charStack.pop();
        }
        System.out.println("ONP: " + result);
    }
    public static void onpToInf(char[] token, int size){
        String tmp="";
        ArrayIntStack intStack=new ArrayIntStack(256);
        ArrayStringStack stringStack=new ArrayStringStack(256);
        for(int i=0;i<size;i++){
            if(isNum(token[i])){//liczba
                stringStack.push(""+token[i]);
                intStack.push(returnPri(token[i]));
            }
            else{//operator
                tmp="";
                String str2 = stringStack.pop();
                if(token[i]!='~'){
                    String str1 = stringStack.pop();
                    if(isLeft(token[i])){
                        if(!intStack.isEmpty() && intStack.top() <= returnPri(token[i])) tmp="("+str2+")";
                        else tmp = str2;
                        intStack.pop();
                        if(!intStack.isEmpty() && intStack.top() < returnPri(token[i])) tmp="("+str1+")"+ token[i] + tmp;
                        else tmp = str1 + token[i] + tmp;
                    }
                    else{
                        if(!intStack.isEmpty() && intStack.top() < returnPri(token[i])) tmp="("+str2+")";
                        else tmp = str2;
                        intStack.pop();
                        if(!intStack.isEmpty() && intStack.top() <= returnPri(token[i])) tmp = "("+str1+")"+ token[i] + tmp;
                        else tmp = str1 + token[i] + tmp;
                    }
                }
                else//operator unarny
                    {
                        if(!intStack.isEmpty() && intStack.top() < returnPri(token[i])) tmp = token[i] + "("+ str2 +")";
                        else tmp = token[i] + str2;
                    }
                intStack.pop();
                stringStack.push(tmp);
                intStack.push(returnPri(token[i]));
            }

        }
        System.out.println("INF: "+ stringStack.top() );
    }
    public static int returnPri(char x){
        if(x=='0') return -1;
        if(x=='=') return 0;
        else if(x=='<'||x=='>') return 1;
        else if(x=='+'||x=='-') return 2;
        else if(x=='*'||x=='/'||x=='%') return 3;
        else if(x=='^') return 4;
        else if(x=='~') return 5;
        else return 6;//liczba
    }
    public static boolean isLeft(char x){
        return (x=='*'||x=='/'||x=='%'||x=='>'||x=='<'||x=='+'||x=='-');
    }
    public static Boolean isOperator2(char x){
        return ( x=='=' || x=='<' || x=='>' || x == '*' || x == '+' || x=='-' || x=='%' || x=='^' || x=='/' );
    }
    public static Boolean isBrackets(char x){
        return (  x=='(' || x==')' );
    }
    public static Boolean isUnaryOprator(char x){
        return ( x=='~' );
    }
    public static Boolean isNum(char x){
        return ( x >= 'a' && x <= 'z' );
    }
    public static Boolean isOnpRight(char[] token, int size){
        int stkSize=0;
        Boolean flag = false; // czy już była jakaś liczba na stosie
        for(int i=0;i<size;i++){
            
            if(flag && stkSize < 1) return false; // po pierwszym włożeniu na stosie zawsze conajmniej 1 el.
            if( isNum(token[i]) ) {
                stkSize++;
                flag = true;
            }
            else if( isOperator2(token[i]) ) {
                stkSize--;
            }
        }
        return stkSize == 1;
    }
    public static Boolean isInfRight(char[] token, int size){
        int stkSize=0;
        int state = 0;
        int brackets = 0;
        Boolean alrdOperator = false;
        for(int i=0;i<size;i++){
            //
            if(brackets<0) return false;
            //
            if( isNum(token[i]) ) {
                stkSize++;
                if(state == 0 || state == 2) state = 1;
                else return false;
            }
            else if( isOperator2(token[i]) ) {
                if(token[i]!='=') alrdOperator=true;
                if(token[i]=='=' && alrdOperator) return false;
                stkSize--;
                if(state == 1) state = 0;
                else return false;
            }
            else if ( token[i] == ')'){
                brackets--;
                if(state == 2 || state == 0) return false;
            }
            else if ( token[i] == '('){
                brackets++;
                if(state == 2) state = 0;
                else if(state == 1) return false;
            }
            else if ( token[i] == '~'){
                if(state == 0) state = 2;
                else if(state == 1) return false;
            }
        }
        return(state == 1 && brackets == 0 && stkSize == 1);
    }

}

class ArrayIntStack {
    private int maxSize;
    private int[] Stk;
    private int sTop;

    public ArrayIntStack(int _maxSize) {
        maxSize=_maxSize;
        Stk=new int[_maxSize];
        sTop=-1;
    }
    public boolean isEmpty() {
        if(sTop==-1) return true;
        return false;
    }
    public boolean isFull() {
        if(sTop==maxSize-1) return true;
        return false;
    }
    public int numberOfElements() {
        return sTop+1;
    }
    public void push(int x) {
        if(!isFull())
        {
            sTop++;
            Stk[sTop]=x;
        }
    }
    public int top() {
        if(!isEmpty())
        {
            return Stk[sTop];
        }
        else return -1;
    }
    public int pop() {
        if(!isEmpty())
        {
            sTop--;
            return Stk[sTop+1];
        }
        return 0;
    }
}
class ArrayCharStack {
    private int maxSize;
    private char[] Stk;
    private int sTop;

    public ArrayCharStack(int _maxSize) {
        maxSize=_maxSize;
        Stk=new char[_maxSize];
        sTop=-1;
    }
    public boolean isEmpty() {
        if(sTop==-1) return true;
        return false;
    }
    public boolean isFull() {
        if(sTop==maxSize-1) return true;
        return false;
    }
    public int numberOfElements() {
        return sTop+1;
    }
    public void push(char x) {
        if(!isFull())
        {
            sTop++;
            Stk[sTop]=x;
        }
    }
    public char top() {
        if(!isEmpty())
        {
            return Stk[sTop];
        }
        else return 'e';
    }
    public char pop() {
        if(!isEmpty())
        {
            sTop--;
            return Stk[sTop+1];
        }
        return 'e';
    }
}
class ArrayStringStack {
    private int maxSize;
    private String[] Stk;
    private int sTop;

    public ArrayStringStack(int _maxSize) {
        maxSize=_maxSize;
        Stk=new String[_maxSize];
        sTop=-1;
    }
    public boolean isEmpty() {
        if(sTop==-1) return true;
        return false;
    }
    public boolean isFull() {
        if(sTop==maxSize-1) return true;
        return false;
    }
    public int numberOfElements() {
        return sTop+1;
    }
    public void push(String x) {
        if(!isFull())
        {
            sTop++;
            Stk[sTop]=x;
        }
    }
    public String top() {
        if(!isEmpty())
        {
            return Stk[sTop];
        }
        else return "error";
    }
    public String pop() {
        if(!isEmpty())
        {
            sTop--;
            return Stk[sTop+1];
        }
        return "error";
    }
}
/*
test.in
20
INF: ()x=a=b=c 
INF: (())x=a=b=c
INF: ())x=a=b=c
INF: ()))x=a=b=c
INF: ())()(x=a=b=c
INF: a+b++(~a-a)
INF: a+b+/(~a-a)
INF: -a+b+(~a-a)
INF: a + b * c / ( d - e ) ^ f ^ g
ONP: +abc-+
ONP: abc-+-
ONP: abc-+a*z+y/^d
ONP: d~p~9.g+m+s++
ONP: ab/c+d^e+
ONP: a~~~~
ONP: a~~~
INF: a~+b
INF: a~~
INF: a+b~
INF: ()a+b
INF: (a+b)+()
INF: ~()a
INF: ~(a+b)

--------------------------------

test.out
INF: ()x=a=b=c 
INF: (())x=a=b=c
INF: ())x=a=b=c
INF: ()))x=a=b=c
INF: ())()(x=a=b=c
INF: a+b++(~a-a)
INF: a+b+/(~a-a)
INF: -a+b+(~a-a)
INF: a + b * c / ( d - e ) ^ f ^ g
ONP: +abc-+
ONP: abc-+-
ONP: abc-+a*z+y/^d
ONP: d~p~9.g+m+s++
ONP: ab/c+d^e+
ONP: a~~~~
ONP: a~~~
INF: a~+b
INF: a~~
INF: a+b~
INF: ()a+b
INF: (a+b)+()

*/
    

