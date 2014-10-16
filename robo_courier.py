import sys
import heapq

class Orientation:
    N = 0
    NE = 1
    SE = 2
    S = 3
    SW = 4
    NW = 5
    MAX = 6

class Node:
    def __init__(self, x, y, orientation):
        self.x = x
        self.y = y
        self.orientation = orientation
        self.forward = 0
        self.cost = 0

    def __repr__(self):
        return "Node " + str(self.x) + " " + str(self.y) + "," + str(self.orientation) + "," + str(self.forward) + "," + str(self.cost)

    def __cmp__(self, other):
        if self.cost < other.cost:
            return -1
        elif self.cost > other.cost:
            return 1
        else:
            return 0

def turnAround(orientation):
    return rotateLeft(rotateLeft(rotateLeft(orientation)))

def rotateLeft(orientation):
    orientation = orientation - 1
    if orientation < Orientation.N:
        orientation = Orientation.NW
    return orientation

def rotateRight(orientation):
    orientation = orientation + 1
    if orientation > Orientation.NW:
        orientation = Orientation.N
    return orientation

def moveForward(x, y, orientation):
    if orientation == Orientation.N:
        y = y + 1
    elif orientation == Orientation.NE:
        x = x + 1
        y = y + 1
    elif orientation == Orientation.SE:
        x = x + 1
    elif orientation == Orientation.S:
        y = y - 1
    elif orientation == Orientation.SW:
        x = x - 1
        y = y - 1
    elif orientation == Orientation.NW:
        x = x - 1
    return x, y

def parseScoutPath(path):
    x = 0
    y = 0
    orientation = Orientation.N
    locations = {}
    # Add starting location
    locations[(x, y)] = ([None for i in range(Orientation.MAX)], [False for i in range(Orientation.MAX)])
    # Parse each move in path    
    for move in path:
        if move == 'F':
            # Update neighbor for orientation
            neighbors, visited = locations[(x, y)]
            newX, newY = moveForward(x, y, orientation)
            neighbors[orientation] = (newX, newY)
            # Update new location neighbor for opposite orientation
            try:
                neighbors, visited = locations[(newX, newY)] 
            except KeyError:
                # Add new location
                neighbors = [None for i in range(Orientation.MAX)]
                locations[(newX, newY)] = (neighbors, [False for i in range(Orientation.MAX)])
            neighbors[turnAround(orientation)] = (x, y)
            x, y = newX, newY
        elif move == 'L':
            orientation = rotateLeft(orientation)
        elif move == 'R':
            orientation = rotateRight(orientation)
    return x, y, locations

def getNeighbors(node, locations):
    newNeighbors = []
    # return all unvisited neighbors
    # rotate right
    x = node.x
    y = node.y
    orientation = rotateRight(node.orientation)
    neighbors, visited = locations[(x, y)]
    if not(visited[orientation]):
        neighbor = Node(x, y, orientation)
        # new cost
        neighbor.cost = node.cost + 3
        newNeighbors.append(neighbor)
    # rotate left
    orientation = rotateLeft(node.orientation)
    if not(visited[orientation]):
        neighbor = Node(x, y, orientation)
        # new cost
        neighbor.cost = currentNode.cost + 3
        newNeighbors.append(neighbor)
    # move forward, if applicable
    orientation = node.orientation
    if neighbors[orientation] != None:
        x, y = neighbors[orientation]
        neighbors, visited = locations[(x, y)]
        if not(visited[orientation]):
            neighbor = Node(x, y, orientation)
            # new forward
            neighbor.forward = node.forward + 1
            # new cost taking into account possible acceleration
            neighbor.cost = currentNode.cost + 4
            if neighbor.forward >= 3:
                neighbor.cost = node.cost + 2
            newNeighbors.append(neighbor)
    return newNeighbors

#scoutPath = "FRRFLLFLLFRRFLF"
#scoutPath = "RFLLF"
#scoutPath = "FLFRRFRFRRFLLFRRF"
#scoutPath = "FFFFFFFFFRRFFFFFFRRFFFFFFLLFFFFFFLLFFFFFFRRFFFF"
#scoutPath = "RFLLFLFLFRFRRFFFRFFRFFRRFLFFRLRRFFLFFLFLLFRFLFLRFFRFFLFLFFRFFLLFLLFRFRFLRLFLRRFLRFLFFLFFFLFLFFRLFRLFLLFLFLRLRRFLFLFRLFRF"
scoutPath = "LLFLFRLRRLRFFLRRRRFFFLRFFRRRLLFLFLLRLRFFLFRRFFFLFLRLFFRRLRLRRFFFLLLRFRLLRFFLFRLFRRFRRRFRLRLRLFFLLFLFFRFLRFRRLLLRFFRRRLRFLFRRFLFFRLFLFLFRLLLLFRLLRFLLLFFFLFRFRRFLLFFLLLFFRLLFLRRFRLFFFRRFFFLLRFFLRFRRRLLRFFFRRLLFLLRLFRRLRLLFFFLFLRFFRLRLLFLRLFFLLFFLLFFFRRLRFRRFLRRLRRLRFFFLLLLRRLRFFLFRFFRLLRFLFRRFLFLFFLFRRFRRLRRFLFFFLLRFLFRRFRFLRLRLLLLFLFFFLFRLLRFRLFRLFRLLFLFRLFFFFFFFRRLRLRLLRFLRLRRRRRRRRLFLFLFLRFLFRLFFRLFRRLLRRRRFFFRRRLLLLRRLFFLLLLLRFFFFRFRRLRRRFFFLLFFFFFLRRLRFLLRRLRLRFRRRRLFLLRFLRRFFFRFRLFFRLLFFRRLL"

endX, endY, locations = parseScoutPath(scoutPath)
pq = []
    
# Push start node
heapq.heappush(pq, Node(0, 0, Orientation.N))

while len(pq) > 0:
    currentNode = heapq.heappop(pq)
    # Mark as visited for this orientation
    neighbors, visited = locations[(currentNode.x, currentNode.y)]
    visited[currentNode.orientation] = True
    # Does our node represent the final coordinate?
    if currentNode.x == endX and currentNode.y == endY:
        # Finished
        break
    print("Visited: " + str(currentNode))
    neighbors = getNeighbors(currentNode, locations)
    for neighbor in neighbors:
        print("Push: " + str(neighbor))
        heapq.heappush(pq, neighbor)

print("Final node: " + str(currentNode))

    


    







