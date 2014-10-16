import sys

def printActivities(i, j):
    choice = chosenActivity[i][j]
    if choice != -1:
        printActivities(i, choice)
        printActivities(choice, j)
        print(str(choice))
    
start = [1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12]
end = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
#start = [1, 5]
#end = [4, 6]
# dummy nodes
start.insert(0, 0)
end.insert(0, 0)
start.append(sys.maxsize)
end.append(sys.maxsize)
# ascending finish times 
end.sort()

maxActivities = [[0 for i in range(len(start))] for i in range(len(start))]
chosenActivity = [[-1 for i in range(len(start))] for i in range(len(start))]

# diagonal is 0
for i in range(0, len(start)):
    maxActivities[i][i] = 0

for j in range(1, len(start)):
    for i in range(j - 1, -1, -1):
        print("i: %d, j: %d" % (i, j))
        maxNumber = 0
        chosen = -1
        for k in range(i + 1, j):
            print("k: %d" % (k))
            # do I start after i finishes and finish before j starts?
            if end[i] <= start[k] and end[k] <= start[j] and (maxActivities[i][k] + maxActivities[k][j] + 1) >= maxNumber:
                maxNumber = maxActivities[i][k] + maxActivities[k][j] + 1
                chosen = k 
        maxActivities[i][j] = maxNumber
        chosenActivity[i][j] = chosen
for i in range(len(start)):
    print(maxActivities[i])
    
for i in range(len(start)):
    print(chosenActivity[i])
    
print("Maximum number of compatible activities is: %d" % (maxActivities[0][len(start) - 1]))
printActivities(0, len(start) - 1)
        