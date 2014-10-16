import sys

def printBestChoice(partitions, items, choices):
    if partitions == 0:
        return
    printBestChoice(partitions - 1, choices[partitions][items], choices)
    sys.stdout.write(" " + str(choices[partitions][items]))
    
#       1                       9 len: 9
work = (1, 2, 3, 4, 5, 6, 7, 8, 9)
#work = (1, 2, 3)
partitions = 2

sums = [[0 for j in range(len(work) + 1)] for i in range(len(work) + 1)]
for i in range(1, len(work) + 1):
    for j in range(i, len(work) + 1):
        sums[i][j] = sums[i][j - 1] + work[j - 1]
        
# initialize boundary, 0 partitions of x items is equal to the sum of x items    
sizes = [[0 for j in range(len(work) + 1)] for i in range(partitions + 1)] 
for j in range(1, len(work) + 1):
    sizes[0][j] = sums[1][j]

# use to reconstruct best way to partition
# partition point of 3 means partition between 2 and 3
choices = [[0 for j in range(len(work) + 1)] for i in range(partitions + 1)] 

# fill in the table from the bottom up
for i in range(1, partitions + 1):
    for j in range(i + 1, len(work) + 1):
        bestChoice = 0
        smallest = sys.maxsize
        for k in range(1, j):
            if max(sizes[i - 1][k], sums[k + 1][j]) < smallest:
                bestChoice = k
                smallest = max(sizes[i - 1][k], sums[k + 1][j])
        choices[i][j] = bestChoice 
        sizes[i][j] = smallest
        
#print(sizes)
#print(choices)
print("The best way to partition has at most %d work units." % (sizes[partitions][len(work)]))
sys.stdout.write("Partition at")
printBestChoice(partitions, len(work), choices)
print(".")



        





    
    
