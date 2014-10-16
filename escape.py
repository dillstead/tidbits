import sys
import heapq

class Constants:
    X1 = 0
    Y1 = 1
    X2 = 2
    Y2 = 3
    MAXDIM = 4
    
class State:
    UNVISITED = 0
    VISITED = 1

class Terrain:
    NORMAL = 0
    HARMFUL = 1
    DEADLY = 2
    
class Node:
    def __init__(self, x, y):
        self.xPos = x
        self.yPos = y
        self.damage = 0

    def __repr__(self):
        return "Node x: " + str(self.xPos) + " y: " + str(self.yPos) + " damage: " + str(self.damage)

    def __cmp__(self, other):
        if self.damage < other.damage:
            return -1
        elif self.damage > other.damage:
            return 1
        else:
            return 0

def fill(grid, coords, value):
    # lower right
    startX = min(coords[Constants.X1], coords[Constants.X2])
    startY = min(coords[Constants.Y1], coords[Constants.Y2])
    if coords[Constants.Y1] < coords[Constants.Y2]:
        height = coords[Constants.Y2] - coords[Constants.Y1]
    else:
        height = coords[Constants.Y1] - coords[Constants.Y2]
    if coords[Constants.X1] < coords[Constants.X2]:
        width = coords[Constants.X2] - coords[Constants.X1]
    else:
        width = coords[Constants.X1] - coords[Constants.X2]
    for x in range(startX, startX + width + 1):
        for y in range(startY, startY + height + 1):
            grid[x][y] = value

def getNeighbors(node):
    neighbors = []
    # return all unvisited neighbors not in deadly regions and not off the grid
    if node.xPos + 1 < Constants.MAXDIM and visited[node.xPos + 1][node.yPos] == State.UNVISITED and board[node.xPos + 1][node.yPos] != Terrain.DEADLY:
        neighbors.append(Node(node.xPos + 1, node.yPos))
    if node.xPos - 1 > 0 and visited[node.xPos - 1][node.yPos] == State.UNVISITED and board[node.xPos - 1][node.yPos] != Terrain.DEADLY:
        neighbors.append(Node(node.xPos - 1, node.yPos))
    if node.yPos + 1 < Constants.MAXDIM and visited[node.xPos][node.yPos + 1] == State.UNVISITED and board[node.xPos][node.yPos + 1] != Terrain.DEADLY:
        neighbors.append(Node(node.xPos, node.yPos + 1))
    if node.yPos - 1 > 0 and visited[node.xPos][node.yPos - 1] == State.UNVISITED and board[node.xPos][node.yPos - 1] != Terrain.DEADLY:
        neighbors.append(Node(node.xPos, node.yPos - 1))
    return neighbors

visited = [[State.UNVISITED for i in range(Constants.MAXDIM)] for j in range(Constants.MAXDIM)]
board = [[Terrain.NORMAL for i in range(Constants.MAXDIM)] for j in range(Constants.MAXDIM)]

#fin = open(sys.argv[1])
#content = fin.read()
#find.close()
#tokens = content.split(",")
#fin = open(sys.argv[2])
#costs = fin.read()
#find.close()

#harmfulCoords = map(int, "500 0 500 0".split(" "))
harmfulCoords = map(int, "1 1 2 3".split(" "))
fill(board, harmfulCoords, Terrain.HARMFUL)
#deadlyCoords = map(int, "0 0 0 0".split(" "))
#fill(board, deadlyCoords, Terrain.DEADLY)

for y in range(Constants.MAXDIM - 1, -1, -1):
    for x in range(Constants.MAXDIM):
        sys.stdout.write(str(board[x][y]))
    sys.stdout.write("\n")

pq = []
heapq.heappush(pq, Node(0, 0))
minDamage = -1

while len(pq) > 0:
    currentNode = heapq.heappop(pq)
    visited[currentNode.xPos][currentNode.yPos] = State.VISITED
    if currentNode.xPos == Constants.MAXDIM - 1 and currentNode.yPos == Constants.MAXDIM - 1:
        # finished
        minDamage = currentNode.damage
        break
    neighbors = getNeighbors(currentNode)
    for neighbor in neighbors:
        # adjust damage based on where you are going to be stepping
        damageAdjustment = currentNode.damage + board[neighbor.xPos][neighbor.yPos]
        neighbor.damage += damageAdjustment
        heapq.heappush(pq, neighbor)

print("Minimum damage: " + str(minDamage))

    
