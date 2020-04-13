#sorting strings in some specific given order
import sys
def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]
        mergeSort(L)
        mergeSort(R)
        i = j = k = 0
        while i < len(L) and j < len(R):
            if comp(L[i],R[j]) == 1:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1
def quickSort(nums, low, high):
    if low < high:
        p = qsortPartition(nums, low, high)
        quickSort(nums, low, p - 1)
        quickSort(nums, p + 1, high)

def qsortPartition(nums, low, high):
    i = low - 1
    piv = nums[high]
    for j in range(low, high):
        #if nums[j] < piv:
        if comp(nums[j],piv) == 1:
            i += 1
            nums[i], nums[j] = nums[j], nums[i]
    nums[i + 1], nums[high] = nums[high], nums[i + 1]
    return i + 1
def compIntAsString(int1,int2):
    # 1 - int1 > int2
    # 2 - int1 < int2
    # 0 - int1 = int2
    n1 = len(int1)
    n2 = len(int2)
    if n1 > n2:
        return 1
    if n1 < n2:
        return 2
    for i in range(n1):
        if int1[i] > int2[i]:
            return 1
        elif int1[i] < int2[i]:
            return 2
    return 0
def comp(str1,str2):
    # -1 when str1 > str2
    #  0 when str1 == str2
    #  1 when str1 < str2
    #  2 when error
    n1 = len(str1)
    n2 = len(str2)
    idx1 = 0
    idx2 = 0
    zeroComp = False
    zeroRes = 0
    while idx1 < n1 and idx2 < n2:
        c1 = str1[idx1]
        c2 = str2[idx2]
        if c1 > '9' and c2 > '9':
            if c1 < c2:
                return 1
            elif c1 > c2:
                return -1
            else:
                idx1 += 1
                idx2 += 1
        elif c1 > '9':
            return -1
        elif c2 > '9':
            return 1
        else: # c1,c2 is a number
            z1 = 0
            z2 = 0
            s1 = ['0']
            s2 = ['0']
            yetZero1 = False
            yetZero2 = False
            #do min(n1,n2)
            while idx1 < n1 and str1[idx1] <= '9' and idx2 < n2 and str2[idx2] <= '9':
                if str1[idx1] == '0':
                    if not yetZero1:
                        z1 += 1
                    else:
                        s1.append(str1[idx1])
                elif str1[idx1] != '0':
                    yetZero1 = True
                    s1.append(str1[idx1])
                if str2[idx2] == '0':
                    if not yetZero2:
                        z2 += 1
                    else:
                        s2.append(str2[idx2])
                elif str2[idx2] != '0':
                    yetZero2 = True
                    s2.append(str2[idx2])
                idx2 += 1
                idx1 += 1

            #test if we know already
            ts1 = ''.join(s1)
            ts2 = ''.join(s2)
            ns1 = [ts1]
            ns2 = [ts2]
            if idx1 >= n1 or str1[idx1] > '9':
                if int(ts1) < int(ts2):
                    return 1
            if idx2 >= n2 or str2[idx2] > '9':
                if int(ts1) > int(ts2):
                    return -1
            while idx1 < n1 and str1[idx1] <= '9':
                if str1[idx1] == '0':
                    if not yetZero1:
                        z1 += 1
                    else:
                        ns1.append(str1[idx1])
                else:
                    yetZero1 = True
                    ns1.append(str1[idx1])
                idx1 += 1
            while idx2 < n2 and str2[idx2] <= '9':
                if str2[idx2] == '0':
                    if not yetZero2:
                        z2 += 1
                    else:
                        ns2.append(str2[idx2])
                else:
                    yetZero2 = True
                    ns2.append(str2[idx2])
                idx2 += 1
            ts1 = ''.join(ns1)
            ts2 = ''.join(ns2)
            if int(ts1) > int(ts2):
                return -1
            elif int(ts1) < int(ts2):
                return 1
            else:
                if not zeroComp:
                    if z1 > z2:
                        zeroComp = True
                        zeroRes = 1
                    elif z1 < z2:
                        zeroComp = True
                        zeroRes = -1
    if idx1 == n1 and idx2 == n2:
        if zeroComp:
            return zeroRes
        else:
            return 0
    elif idx1 == n1:
        return 1
    elif idx2 == n2:
        return -1
    else:
        return 2


lines = []
for line in sys.stdin:
    for word in line.split():
        lines.append(word)
mergeSort(lines)
for line in lines:
    print(line)




