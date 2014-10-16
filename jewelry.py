import sys
import math

#values = (1, 2, 3, 3)
values = (1, 2, 5, 3, 4, 5)
#values = (3, 3)
numValues = len(values)
sumValues = sum(values)

def numSumsBefore(values):
    before = [[0 for j in range(sumValues + 1)] for i in range(numValues - 1)]    
    for i in range(numValues - 1):
        before[i][0] = 1
    # Start with the first item and fill out the table with all possible sums.
    for i in range(numValues - 1):
        for j in range(i + 1):
            for k in range(sumValues, values[j] - 1, -1):
                before[i][k] += before[i][k - values[j]]
    return before

def numSumsAfter(values):
    after = [[0 for j in range(sumValues + 1)] for i in range(numValues - 1)]    
    for i in range(numValues - 1):
        after[i][0] = 1
    # Start with the last item and fill out the table with all possible sums.
    for i in range(numValues - 1, 0, -1):
        for j in range(numValues - 1, i - 1, -1):
            for k in range(sumValues, values[j] - 1, -1):
                after[i - 1][k] += after[i - 1][k - values[j]]
    return after

def factorial(x):
    if x == 0:
        return 1
    if x == 1 or x == -1:
        return x
    if x > 0:
        return x * factorial(x - 1)
    else:
        return x * factorial(x + 1)
    
def choose(total, choices):
    return factorial(total) / (factorial(total - choices) * factorial(choices))

def countGroupMembers(values):
    members = [0 for i in range(values[-1] + 1)]
    for i in values:
        members[i] += 1
    return members

def indexGroups(values):
    indices = [1 for i in range(numValues)]
    for i in range(1, numValues):
        if values[i] == values[i - 1]:
            indices[i] = indices[i - 1] + 1
    return indices

values = sorted(values)
numMembers = countGroupMembers(values)
indices = indexGroups(values)
#print("Values: " + str(values))
#print("Num Members: " + str(numMembers))
#print("Indices: " + str(indices))
before = numSumsBefore(values)
#print("Before")
#print(range(sumValues + 1))
#for i in range(numValues - 1):
#    print(before[i])
after = numSumsAfter(values)
#print("After")
#print(range(sumValues + 1))
#for i in range(numValues - 1):
#    print(after[i])

count = 0
for i in range(0, numValues - 1):
    for j in range(values[i] * indices[i], sumValues + 1):
        if i > 0:
            newValue = before[i][j] - before[i - 1][j]
        else:
            newValue = before[i][j]
        count += (choose(numMembers[values[i]], indices[i]) * newValue * after[i][j])
print("Count: " + str(count))



