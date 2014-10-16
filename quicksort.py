def swap(list, idx1, idx2):
    tVal = list[idx1]
    list[idx1] = list[idx2]
    list[idx2] = tVal
    
def quickSort(list, sIdx, eIdx):
    if eIdx - sIdx < 1:
        return
    pIdx = partition(list, sIdx, eIdx)
    quickSort(list, sIdx, pIdx - 1)
    quickSort(list, pIdx, eIdx)
    
def partition(list, sIdx, eIdx):
    pIdx = int(sIdx + (eIdx - sIdx) / 2)
    pVal = list[pIdx]
    swap(list, sIdx, pIdx)
    lIdx = sIdx
    rIdx = eIdx
    while lIdx < rIdx:
        if list[lIdx] > pVal and list[rIdx] <= pVal:
            swap(list, lIdx, rIdx)
            lIdx += 1
            rIdx -= 1
        else:
            if list[lIdx] <= pVal:
                lIdx += 1
            if list[rIdx] > pVal:
                rIdx -= 1
    swap(list, sIdx, rIdx)
    return rIdx

#test = [2, 1, 3, 6, 8, 9, 8, 11, 8]
test = [10, 9, 10]
#test = [2, 1, 3, 6, 8, 9, 8]
quickSort(test, 0, len(test) - 1)
print(test)
