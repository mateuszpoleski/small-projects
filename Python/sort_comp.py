#comaprison of few sorting algorithms
import time

def bubbleSort(nums):
    n = len(nums)
    for i in range(n):
        isSwapped = False
        for j in range(0, n - i - 1):
            if nums[j] > nums[j + 1]:
                nums[j], nums[j + 1] = nums[j + 1], nums[j]
                isSwapped = True
        if not isSwapped:
            break

def insertSort(nums):
    n = len(nums)
    for i in range(1, n):
        key = nums[i]
        j = i - 1
        while j >= 0 and key < nums[j]:
            nums[j + 1] = nums[j]
            j -= 1
        nums[j + 1] = key

def quickSort(nums, low, high):
    if low < high:
        p = qsortPartition(nums, low, high)
        quickSort(nums, low, p - 1)
        quickSort(nums, p + 1, high)

def qsortPartition(nums, low, high):
    i = low - 1
    piv = nums[high]
    for j in range(low, high):
        if nums[j] < piv:
            i += 1
            nums[i], nums[j] = nums[j], nums[i]
    nums[i + 1], nums[high] = nums[high], nums[i + 1]
    return i + 1

tab = []
def permuteNat(nums,chosen):
    if len(nums) == 0:
        tab.append(chosen.copy())
        print(chosen)
    else:
        for i,num in enumerate(nums):
            tmp = num
            chosen.append(num)
            nums.remove(num)
            permuteNat(nums,chosen)
            nums.insert(i,tmp)
            chosen.remove(tmp)




def permuteUtl(nums, new):
    if len(new) == len(nums):
        ret.append(new)
    else:
        for num in nums:
            if num in new:
                pass
            else:
                tmp = new.copy()
                tmp.append(num)
                permuteUtl(nums, tmp)


def permute(nums):
    ans = []
    permuteNat(nums, [])
    return ans


def sortCompPermute(size):
    insertTimes = []
    bubbleTimes = []
    quickTimes = []


    da = [1,2,3,4]
    data = permute(da)
    print(data)

    for d in data:
        # InsertionSort
        dataCpy = d.copy()
        start = time.perf_counter()
        insertSort(dataCpy)
        end = time.perf_counter()
        insertTime = end - start
        insertTimes.append(insertTime)

        # BubbleSort
        dataCpy = d.copy()
        start = time.perf_counter()
        bubbleSort(dataCpy)
        end = time.perf_counter()
        bubbleTime = end - start
        bubbleTimes.append(bubbleTime)

        # QuickSort
        dataCpy = d.copy()
        start = time.perf_counter()
        quickSort(dataCpy, 0, len(dataCpy) - 1)
        end = time.perf_counter()
        quickTime = end - start
        quickTimes.append(quickTime)

    insertLowestTime = min(insertTimes)
    bubbleLowestTime = min(bubbleTimes)
    quickLowestTime = min(quickTimes)
    insertHighestTime = max(insertTimes)
    bubbleHighestTime = max(bubbleTimes)
    quickHighestTime = max(quickTimes)

    print("Sorting ", size, " elements:", "\n")
    print("Bubble Sort:")
    print("Best case time:", bubbleLowestTime)
    print("Average time:", sum(bubbleTimes) / len(data))
    print("Worst case time:", bubbleHighestTime, "\n")

    print("Insertion Sort:")
    print("Best case time:", insertLowestTime)
    print("Average time:", sum(insertTimes) / len(data))
    print("Worst case time:", insertHighestTime, "\n")

    print("Quick Sort:")
    print("Best case time:", quickLowestTime)
    print("Average time:", sum(quickTimes) / len(data))
    print("Worst case time:", quickHighestTime, "\n")

    print("BubbleSort/InsertSort Optimistic:", bubbleLowestTime / insertLowestTime)
    print("BubbleSort/QuickSort Optimistic:", bubbleLowestTime / quickLowestTime, "\n")

    print("BubbleSort/InsertSort Average:", sum(bubbleTimes) / sum(insertTimes))
    print("BubbleSort/QuickSort Average:", sum(bubbleTimes) / sum(quickTimes), "\n")

    print("BubbleSort/InsertSort Worst:", bubbleHighestTime / insertHighestTime)
    print("BubbleSort/QuickSort Worst:", bubbleHighestTime / quickHighestTime, "\n")

###

sortCompPermute(8)
print(tab)
