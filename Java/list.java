//Excercise with list implementation and some modifications
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        int z = in.nextInt();
        in.nextLine();
        for(int x=0;x<z;x++){
            int n = in.nextInt();
            in.nextLine();
            TrainList trainList = new TrainList();
            for(int y=0;y<n;y++){
                //
                String tmpS = in.nextLine();
                String com="";
                String arg1="";
                String arg2="";
                char inpt;
                int spaces=0;
                for(int k = 0;k<tmpS.length();k++){
                    inpt = tmpS.charAt(k);
                    if(inpt==' '){
                        spaces++;
                        continue;
                    }
                    if(spaces==0) com+=inpt;
                    if(spaces==1) arg1+=inpt;
                    if(spaces==2) arg2+=inpt;
                }
                //
                Train tmp;
                switch(com){
                    case "New": 
                        tmp = new Train(arg1);
                        tmp.insertFirst(arg2);
                        trainList.insertLast(tmp);
                        break;
                    case "InsertFirst": 
                        tmp = trainList.findTrain(arg1);
                        tmp.insertFirst(arg2);
                        break;
                    case "InsertLast": 
                        tmp = trainList.findTrain(arg1);
                        tmp.insertLast(arg2);
                        break;
                    case "Display": 
                        tmp = trainList.findTrain(arg1);
                        tmp.display();
                        System.out.println();
                        break;
                    case "Reverse": 
                        tmp = trainList.findTrain(arg1);
                        tmp.reverse();
                        break;
                    case "Union":
                        trainList.union(arg1,arg2);
                        break;
                    case "DelFirst":
                        trainList.delFirst(arg1, arg2);
                        break;
                    case "DelLast":
                        trainList.delLast(arg1, arg2);
                        break;
                    case "Trains":
                        trainList.displayTrains();
                        break;
                        
                }
            }   
        }
    }
    
}
class Train {
    public W first;
    public W last;
    public String name;
    public Train next;
 
    public Train(String _name) {
    	first=null;
    	last=null;
        next=null;
        name = _name;
    }
    public void display(){       
    	{
            W tmp;
            Boolean tmpReverse=false;
            if(first.prev==null) tmpReverse=false;
            else if(first.next==null) tmpReverse=true;
            tmp=first;
            W tmpNext;
            System.out.print(name +": ");
            while(tmp!=null)
            {
                if(!isEmpty()) System.out.print(tmp.name+" ");
                if(tmpReverse){
                    tmpNext=tmp.prev;
                    if(tmpNext != null && tmpNext.prev==tmp) tmpReverse=false;
                    tmp=tmp.prev;
                }
                else{
                    tmpNext=tmp.next;
                    if(tmpNext != null && tmpNext.next==tmp) tmpReverse=true;
                    tmp=tmp.next;
                }
            }
    	}
    }

    public void insertFirst(String x) {
    	W tmp=new W(x);
    	if(!isEmpty()){
    		if(first.prev==null){
                    first.prev=tmp;
                    tmp.next=first;
                    first = tmp;
                }
                else if(first.next==null){
                    first.next=tmp;
                    tmp.prev=first;
                    first=tmp;
                }
    	}
    	else{
    		first=last=tmp;
    	}
    }

    public void insertLast(String x) {
    	W tmp=new W(x);
    	if(!isEmpty()){
    		if(last.next==null){
                    last.next=tmp;
                    tmp.prev=last;
                    last = tmp;
                }
                else if(last.prev==null){
                    last.prev=tmp;
                    tmp.next=last;
                    last=tmp;
                }
    	else{
            first=last=tmp;
    	}
        }
    }

    public W removeFirst() {
    	if(!isEmpty()){
            W tmp=first;
            
            if(first.next==null&&first.prev==null)
    		{
    			first=last=null;
    			return tmp;
    		}
            if(first.prev==null&&first.next.prev==first)
            {
            	first=first.next;
            	first.prev=null;
            }
            else if(first.prev==null&&first.next.next==first)
            {
            	first=first.next;
            	first.next=null;
            }
            else if(first.next==null&&first.prev.prev==first)
            {
            	first=first.prev;
            	first.prev=null;
            }
            else if(first.next==null&&first.prev.next==first)
            {
            	first=first.prev;
            	first.next=null;
            }
            return tmp;
	        
    	}
    	return null;
    }
   
    public W removeLast() {
        if(!isEmpty())
        {
        	W tmp = last;
                
                if(last.next==null&&last.prev==null)
    		{
    			last=first=null;
    			return tmp;
    		}
    		else if(last.next==null&&last.prev.next==last)
    		{
    			last=last.prev;
    			last.next=null;
    		}
    		else if(last.next==null&&last.prev.prev==last)
    		{
    			last=last.prev;
    			last.prev=null;
    		}
    		else if(last.prev==null&&last.next.next==last)
    		{
    			last=last.next;
    			last.next=null;
    		}
    		else if(last.prev==null&&last.next.prev==last)
    		{
    			last=last.next;
    			last.prev=null;
    		} 
                return tmp;
        }
        return null;
    }
    
    public boolean isEmpty() {
    	return first==null;
    } 
    
     public void reverse() {
        W tmp=first;
        first=last;
        last=tmp;
    } 
	 
}

class W
{
	public String name;
	public W next;
	public W prev;
	W(String x){
		name = x;
                prev = null;
		next = null;
	}
}

class TrainList
{
    private Train first;
    private Train last;
    public TrainList(){
        first = last = null;
    }
    public Train findTrain(String name){
        Train tmp = first;
        while(tmp!=null){
            if(tmp.name.equals(name)){
                
                return tmp;
            }
            tmp = tmp.next;
        }
        return tmp;
    }
    public void displayTrains(){
        Train tmp = first;
        while(tmp!=null){
            System.out.print(tmp.name+" ");
            tmp=tmp.next;
        }
        System.out.println();
    }
    public void display(String name)
	{
            Train tmp=findTrain(name);
            System.out.print(tmp.name+":");
            tmp.display();
            System.out.println();
	}
    public void insertFirst(Train x) {
    	if(!isEmpty()){
    		x.next=first;
                first = x;
    	}
    	else{
    		first=last=x;
    	}
    }

    public void insertLast(Train x) {
    	if(!isEmpty()){
    		last.next=x;
                last = x;
    	}
    	else{
    		first=last=x;
    	}
    }
    
    public void union(String str1,String str2){
        //szukanie T2 do usuniecia 
        Train x = findTrain(str1);
        Train y = first;
        Train tmp = first;
        while(tmp.next!=null){
            if(tmp.next.name.equals(str2)){
                y=tmp.next;
                if(tmp.next.next!=null){
                    tmp.next = tmp.next.next;
                    break;
                }
                else{//ostatni el
                    tmp.next=null;
                    last=tmp;
                    break;
                }      
            }
            tmp = tmp.next;
        }
        if(y==first){//pierwszy el to nasz szukany
            if(first.next==null){//tylko 1 el i jest to nasz szukany
                first=last=null;
            }
            else{
                first = first.next;
            }
        }
        //
        if(x.last.next==null&&y.first.prev==null)
		{
			y.first.prev=x.last;
			x.last.next=y.first;
			x.last=y.last;
		}
		else if(x.last.next==null&&y.first.next==null)
		{
			y.first.next=x.last;
			x.last.next=y.first;
			x.last=y.last;
		}
		else if(x.last.prev==null&&y.first.prev==null)
		{
			y.first.prev=x.last;
			x.last.prev=y.first;
			x.last=y.last;
		}
		else if(x.last.prev==null&&y.first.next==null)
		{
			y.first.next=x.last;
			x.last.prev=y.first;
			x.last=y.last;
		}
    }
   
    public boolean isEmpty() {
    	return first==null;
    } 
    public void delFirst(String str1, String str2){
        //szukanie T1 i ew. usuwamy
        Train y = first;
        Train tmp = first;
        while(tmp.next!=null){
            if(tmp.next.name.equals(str1)){
                y=tmp.next;
                if(y.first==y.last){//jeśli to jedyny wagon to usuwamy pociąg
                        if(tmp.next.next!=null){
                        tmp.next = tmp.next.next;
                        break;
                    }
                    else{//ostatni el
                        tmp.next=null;
                        last=tmp;
                        break;
                    } 
                }  
                else break;
            }
            tmp = tmp.next;
        }
        if(y==first){//pierwszy el to nasz szukany
            if(first.next==null){//tylko 1 el i jest to nasz szukany
                if(y.first==y.last) first=last=null;
            }
            else{
                if(y.first==y.last) first = first.next;
            }
        }
        //
        W tmpW;
        tmpW = y.removeFirst();
        Train tmpTr2 = new Train(str2);
        tmpTr2.insertFirst(tmpW.name);
        insertLast(tmpTr2);
    }
    public void delLast(String str1, String str2){
        //szukanie T1 i ew. usuwamy
        Train y = first;
        Train tmp = first;
        while(tmp.next!=null){
            if(tmp.next.name.equals(str1)){
                y=tmp.next;
                if(y.first==y.last){//jeśli to jedyny wagon to usuwamy pociąg
                        if(tmp.next.next!=null){
                        tmp.next = tmp.next.next;
                        break;
                    }
                    else{//ostatni el
                        tmp.next=null;
                        last=tmp;
                        break;
                    } 
                }  
                else break;
            }
            tmp = tmp.next;
        }
        if(y==first){//pierwszy el to nasz szukany
            if(first.next==null){//tylko 1 el i jest to nasz szukany
                if(y.first==y.last) first=last=null;
            }
            else{
                if(y.first==y.last) first = first.next;
            }
        }
        //
        W tmpW;
        tmpW = y.removeLast();
        Train tmpTr2 = new Train(str2);
        tmpTr2.insertFirst(tmpW.name);
        insertLast(tmpTr2);
    }
    
}
/*
test.in
1
100
New T1 W1
InsertLast T1 W2
InsertLast T1 W3
New T2 E1
InsertLast T2 E2
InsertLast T2 E3
New T3 R1
InserLast T3 R2
InsertLast T3 R3
Display T1
T1: W1 W2 W3 
Display T2
T2: E1 E2 E3 
Display T3
T3: R1 R3 
Reverse T2
Display T2
T2: E3 E2 E1 
Union T1 T2
Display T1
T1: W1 W2 W3 E3 E2 E1 
Union T1 T3
Display T1
test.out
T1: W1 W2 W3 
T2: E1 E2 E3 
T3: R1 R3 
T2: E3 E2 E1 
T1: W1 W2 W3 E3 E2 E1 
T1: W1 W2 W3 E3 E2 E1 R1 R3 
*/