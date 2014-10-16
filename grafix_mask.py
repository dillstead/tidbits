# Using linked list-ish disjoint set data structures

#rectangles = ("0 292 399 307",)
rectangles = ("0 192 399 207", "0 392 399 407", "120 0 135 599", "260 0 275 599")
height = 400
width = 600
#height = 3
#width = 4
#rectangles = ("0 1 2 3",)

def createSet(gridPoint):
    gridPoint.cSet = []
    gridPoint.cSet.append(gridPoint)
    return gridPoint.cSet
    
def findSet(gridPoint):
    return gridPoint.cSet

def union(gridPoint1, gridPoint2):
    if gridPoint1.cSet == gridPoint2.cSet:
        return gridPoint1.cSet
    
    if len(gridPoint1.cSet) > len(gridPoint2.cSet):
        larger = gridPoint1
        smaller = gridPoint2
    else:
        larger = gridPoint2
        smaller = gridPoint1
        
        larger.cSet.extend(smaller.cSet)
        smaller.cSet = larger.cSet
        return larger.cSet
    
class GridPoint:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.cSet = None

grid = [[True for i in range(width)] for j in range(height)]
for rectangle in rectangles:
    tlx, tly, brx, bry = map(lambda x : int(x), rectangle.split())
    for x in range(tlx, brx + 1):
        for y in range(tly, bry + 1):
            # Blocked
            grid[x][y] = False

gridPoints = [[None for i in range(width)] for j in range(height)]
for x in range(0, height):
    for y in range(0, width):
        gridPoints[x][y] = GridPoint(x, y)
        createSet(gridPoints[x][y])
        
for x in range(0, height):
    for y in range(0, width):
        if grid[x][y]:
            # Open space, merge sets to the left and above
            if x - 1 >= 0 and grid[x - 1][y]:
                union(gridPoints[x][y], gridPoints[x - 1][y])
            if y - 1 >= 0 and grid[x][y - 1]:
                union(gridPoints[x][y], gridPoints[x][y - 1])
            
areas = []
for x in range(0, height):
    for y in range(0, width):
        if grid[x][y]:
            cSet = findSet(gridPoints[x][y])
            area = 0
            for gridPoint in cSet:
                grid[gridPoint.x][gridPoint.y] = False
                area += 1
            areas.append(area)

print("Sorted areas: ")
areas.sort()
print(areas)

            
        
            
        

