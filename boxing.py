import sys
import functools
presses = ([1], [1000], [1001], [1500], [3000], [3003])
#presses = ([1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6, 7], [1, 2, 3, 4, 5, 6], [0, 1, 2], [1, 2, 3, 4, 5, 6, 7, 8])
numJudges = len(presses)
numPresses = functools.reduce(lambda x, y : x + y, map(lambda x: len(x), presses))

# flatten presses into a time line for further processing
pressTimeLine = []
for i in range(numPresses):
    minTime = sys.maxsize
    minIndex = 0
    for j in range(len(presses)):
        if len(presses[j]) > 0:
            if presses[j][0] < minTime:
                minTime = presses[j][0]
                minIndex = j
    minPress = presses[minIndex].pop(0)
    #print("min press: %d" % minPress)
    pressTimeLine.append((minIndex, minPress))
    
startIndex = 0
unique = 0
counts = [0 for i in range(numJudges)]
maxCredits = 0
for i in range(numPresses):
    judge, press = pressTimeLine[i]
    if press - pressTimeLine[startIndex][1] > 1000:
        # press exceeds interval, start new interval by dropping old presses
        # adjust tallies accordingly as punches drop out of the interval
        while True:
            oldJudge, oldPress = pressTimeLine[startIndex]
            print("removing judge: %d, press: %d" % (oldJudge, oldPress))
            counts[oldJudge] -= 1
            if counts[oldJudge] == 0:
                unique -= 1
            startIndex += 1
            if press - pressTimeLine[startIndex][1] <= 1000:
                break
        print("new interval")
    print("adding judge: %d, press: %d" % (judge, press))
    # tally judge and unique presses in the current interval
    if counts[judge] == 0:
        unique += 1
    counts[judge] += 1
    # if there are enough unique presses in the interval, report it
    if unique == 3:
        print("adding credit")
        maxCredits += 1
        # reset tallies
        unique = 0
        counts = [0 for i in range(numJudges)]
        
print("max credits: %d" % (maxCredits))
    
    

        
            
        
     
    
    
    
        
    

    

    
    
    
    
    

    
            
        
         



