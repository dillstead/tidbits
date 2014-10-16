import sys

def markBadNeighbors(neighbors, bad):
    # Marks the bad west and south neighbors or each intersection
    for coordinates in bad:
        print coordinates
        x1, y1, x2, y2 = map(int, coordinates.split())
        if x1 == x2:
            # Bad south neighbor
            neighbors[x1][min(y1, y2)][SOUTH] = BLOCKED
        else:
            # Bad west neighbor
            neighbors[min(x1, x2)][y1][WEST] = BLOCKED

# Neighbor index
WEST = 0
SOUTH = 1
# Is traversal to a particular neighbor blocked or allowed?
BLOCKED = 0
ALLOWED = 1

#width = 6
#height = 6
#bad = ["0 0 0 1", "6 6 5 6"]

width = 1
height = 1
bad = ["0 1 0 0"]

# Tracks whether or not a block can reach its west or south neighbor
neighbors = [[[ALLOWED for k in range(2)] for j in range(height + 1)] for i in range(width + 1)]
# Stores the total number of steps for each reaching path
blocks = [[0 for j in range(height + 1)] for i in range(width + 1)]

print neighbors
print blocks

markBadNeighbors(neighbors, bad)
print neighbors

# Scan blocks for top to bottom, left to right filling the number of steps
# in all paths that reach the block
for x in range(width + 1):
    for y in range(height + 1):
        # Check south neighbor
        if y - 1 >= 0 and neighbors[x][y - 1][SOUTH] == ALLOWED:
            blocks[x][y] += blocks[x][y - 1]
            blocks[x][y] += 1
        # Check west neighbor
        if x - 1 >= 0 and neighbors[x - 1][y][WEST] == ALLOWED:
            blocks[x][y] += blocks[x - 1][y]
            blocks[x][y] += 1
totalPaths = blocks[width][height] / (width + height)
print("Total paths: %d" % totalPaths)



        
        




        
        
