#coding and decoding steps of creating a heap
def decodeBuilding(arr,code):
    for i in range(0,len(arr)//2):
        stepCode = [code.pop()]
        j = len(code)-1
        while j >= 0 and code[j][0] != '1':
            stepCode.insert(0, code.pop())
            j -= 1
        stepCode = check(stepCode)
        #
        idx = i
        f = True
        for c in stepCode:
            if c[1] == '1':
                idx = 2*idx + 1
            elif c[2] == '1':
                idx = 2*idx + 2
            else:
                f = False
        tmp = arr[idx]
        while idx > i:
            arr[idx] = arr[(idx-1)//2]
            idx = (idx-1)//2
        if f:
            arr[i] = tmp
        print(arr)
def decodeSorting(arr,code):
    newArr = [0]*len(arr)
    for i in range(len(arr)):
        stepCode = []
        if len(code) != 0:
            stepCode.append(code.pop())
        j = len(code)-1
        while j >= 0 and code[j][0] != '1':
            stepCode.insert(0, code.pop())
            j -= 1
        stepCode = check(stepCode)
        #
        idx = 0
        f = True
        for c in stepCode:
            if c[1] == '1':
                idx = 2*idx + 1
            elif c[2] == '1':
                idx = 2*idx + 2
            else:
                f = False
        tmp = newArr[idx]
        print("Przed przesiewaniem:                   ",stepCode,newArr)
        while idx > 0:
            newArr[idx] = newArr[(idx-1)//2]
            idx = (idx-1)//2
        if f:
            newArr[0] = tmp
        newArr[i] = arr[i]
        newArr[0], newArr[i] = newArr[i], newArr[0]
        print("Po przesiewaniu i dodaniu nowej liczby:",newArr)
    return newArr
def check(arr):
    n = len(arr)-1
    if len(arr) > 1:
        if arr[n] == "100":
            if(arr[n-1][1] == '1'):
                arr.pop()
                arr[n-1]="110"
            else:
                arr.pop()
                arr[n - 1] = "101"
    return arr

def Floyd(arr,i,size,code):
    left = 2*i + 1
    right = 2*i + 2
    if(right < size and arr[right] > arr[left]):
        larger = right
        s = "01"
    else:
        larger = left
        s = "10"
    f = True
    f2 = True
    if(larger < size and arr[larger] > arr[i]):
        f = False
        arr[i] , arr[larger] = arr[larger] , arr[i]
        if(2*larger + 1 < size):
            f2 = False
            code.append("0"+s)
            Floyd(arr,larger,size,code)
    if(f and f2):
        code.append("100")
    elif(f2):
        code.append("1" + s)
def BuildHeap(arr):
    for i in range((len(arr)//2)-1, -1, -1):
        Floyd(arr, i,len(arr),heapCode)
def ShiftDown(arr):
    for i in range(len(arr), 0, -1):
        arr[i-1], arr[0] = arr[0], arr[i-1]
        Floyd(arr,0,i-1,sortCode)
def HeapSort(arr):
    BuildHeap(arr)
    ShiftDown(arr)

heapCode = []
sortCode = []
arr = [5,8,1,10,21,30,3,7,11,31,29,17]
arrCopy = arr.copy()
print("Tablica danych bez wlasnosci kopca:",arr)
BuildHeap(arrCopy)
print("Tablica z wlasnoscia kopca",arrCopy)
print("Kodowanie budowy kopca",heapCode)
print()
print("Kolejne etapy dekodowania budowy kopca: ")
decodeBuilding(arrCopy,heapCode)
print()
HeapSort(arr)
print("Kodowanie sortowania",sortCode)
print("Kolejne etapy dekodowania sortowania: ")
decodeSorting(arr,sortCode)
print()
print("Posortowana tablica: ",arr)

