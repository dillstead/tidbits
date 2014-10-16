import sys

#stripes = "RGBGR"
stripes = "ABACADA"

# pos 
# stroke
# total strokes

tracker = [[0 for j in range(2)] for i in range(len(stripes))]
tracker[0][0] = 1
tracker[0][1] = 1

# 0 -> 1
for pos in range(1, len(stripes)):
    back = pos - 1
    minStroke = sys.maxint
    while back >= 0 and stripes[pos] != stripes[back]:
        if tracker[back][0] < minStroke:
            minStroke = tracker[back][0]
        back -= 1
    print back
    if back >= 0 and tracker[back][0] <= minStroke:
        tracker[pos][0] = tracker[back][1]
        tracker[pos][1] = tracker[pos - 1][1]
    else:
        tracker[pos][0] = tracker[pos - 1][1] + 1
        tracker[pos][1] = tracker[pos - 1][1] + 1
print tracker



    

