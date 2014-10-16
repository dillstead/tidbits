import sys

def overlaps(flower1, flower2):
    # Returns true if flowers overlap, false if they don't
    return (flower1[1] >= flower2[1] and flower1[1] <= flower2[2]) or (flower2[1] >= flower1[1] and flower2[1] <= flower1[2])

def addOverlap(overlap, flower):
    # Add the flower to its proper position in the overlap sequence
    # If overlaps with current:
    #   Height is greater, continue
    #   Height is smaller, put in front of current and exit
    # If doesn't overlap with current:
    #   Height is greater, put in front of current and exit
    #   Height is less, put after current and exit
    i = 0
    while i < len(overlap):
        if not overlaps(overlap[i], flower) and flower[0] > overlap[i][0]:
            # Put after
            i += 1
            break
        if (overlaps(overlap[i], flower) and flower[0] < overlap[i][0]) or (not overlaps(overlap[i], flower) and flower[0] > overlap[i][0]):
            # Put before
            break
        i += 1
    overlap.insert(i, flower)
    
def getOverlaps(flowers):
    # Create buckets for each overlapping sequence
    # Sequences will be sorted, pushing the largest flowers to
    # the front
    overlaps = []
    bloom = 0
    wilt = 0
    for flower in flowers:
        if flower[1] >= bloom and flower[1] <= wilt:
            # Add to existing sequence in the proper position
            print("add")
            print flower
            addOverlap(overlap, flower)
            # If necessary, expand time frame
            bloom= flower[1]
            wilt = max(wilt, flower[2])
        else:
            # Start new sequence
            print("new")
            print flower
            overlap = [flower]
            # New time frame
            bloom = flower[1]
            wilt = flower[2]
            overlaps.append(overlap)
    return overlaps

#height = (5, 4, 3, 2, 1)
#blooms = (1, 1, 1, 1, 1)
#wilts = (365, 365, 365, 365, 365)
#height = (5, 4, 3, 2, 1)
#blooms = (1, 5, 10, 15, 20)
#wilts = (4, 9, 14, 19, 24)
#height = (5, 4, 3, 2, 1)
#blooms = (1, 5, 10, 15, 20)
#wilts = (5, 10, 15, 20, 25)
#height = (5, 4, 3, 2, 1)
#blooms = (1, 5, 10, 15, 20)
#wilts = (5, 10, 14, 20, 25)
#height = (1, 2, 3, 4, 5, 6)
#blooms = (1, 3, 1, 3, 1, 3)
#wilts = (2, 4, 2, 4, 2, 4)
height = (3, 2, 5, 4)
blooms = (1, 2, 11, 10)
wilts = (4, 3, 12, 13)

flowers = [(height[i], blooms[i], wilts[i]) for i in range(len(height))]
# Sort by blooms time.  If same bloom time, put shorter flower first.
flowers.sort(key=lambda flower: flower[0])
flowers.sort(key=lambda flower: flower[1])
print flowers

overlaps = getOverlaps(flowers)
print overlaps

for i in range(len(flowers)):
    maxHeight = 0
    maxIndex = 0
    for j in range(len(overlaps)):
        if len(overlaps[j]) > 0 and overlaps[j][0][0] > maxHeight:
            maxIndex = j
            maxHeight = overlaps[j][0][0]
    flower = overlaps[maxIndex].pop(0)
    sys.stdout.write("%d " % flower[0])
sys.stdout.write("\n")
