wines = (1, 4, 2, 3, 9)
#wines = (1, 4)
memo = [[-1 for i in range(0, len(wines))] for j in range(0, len(wines))]

def chooseWineMemo(year, left, right):
    global numCalls
    numCalls += 1
    print("chooseWine y:" + str(year) + " l:" + str(left) + " r:" + str(right))
    if memo[left][right] != -1:
        return memo[left][right]
    if left == right:
        return year * wines[left]
    maxProfit = max(wines[left] * year + chooseWineMemo(year + 1, left + 1, right), 
                     wines[right] * year + chooseWineMemo(year + 1, left, right - 1))
    memo[left][right] = maxProfit
    return maxProfit
    
def chooseWine(year, left, right):
    global numCalls
    numCalls += 1
    print("chooseWine y:" + str(year) + " l:" + str(left) + " r:" + str(right))
    if left == right:
        return year * wines[left]
    return max(wines[left] * year + chooseWine(year + 1, left + 1, right), 
               wines[right] * year + chooseWine(year + 1, left, right - 1))

numCalls = 0
maxProfit = chooseWine(1, 0, len(wines) - 1)
print("max profit is: " + str(maxProfit) + " num calls:" + str(numCalls))
numCalls = 0
maxProfit = chooseWineMemo(1, 0, len(wines) - 1)
print(memo)
print("max profit is: " + str(maxProfit) + " num calls:" + str(numCalls))



