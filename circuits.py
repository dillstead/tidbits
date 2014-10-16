import sys

def dfs(startIndex):
    nodeStack = []        
    nodes[startIndex].state = State.DISCOVERED
    nodeStack.append(nodes[startIndex])
    while len(nodeStack) != 0:
        addedNode = False
        topNode = nodeStack[len(nodeStack) - 1] 
        for i in range(len(nodes)):
            checkEntry = adjMatrix[topNode.index][i]
            checkNode = nodes[i]
            if checkEntry != -1:
                topNode.maxCost = max(topNode.maxCost, checkEntry + checkNode.maxCost)
                if checkNode.state == State.UNDISCOVERED:
                    checkNode.state = State.DISCOVERED
                    nodeStack.append(checkNode)
                    addedNode = True
        if not addedNode:
            topNode.state = State.EXPLORED
            nodeStack.pop()
        
class State:
    UNDISCOVERED = "u"
    DISCOVERED = "d"
    EXPLORED = "e"

class Node:
    def __init__(self, index):
        self.index = index
        self.maxCost = 0
        self.state = State.UNDISCOVERED

    def __repr__(self):
        return "Node " + str(self.index) + " max cost: " + str(self.maxCost) + " state: " + str(self.state)

#fin = open(sys.argv[1])
#content = fin.read()
#find.close()
#tokens = content.split(",")
#fin = open(sys.argv[2])
#costs = fin.read()
#find.close()

connects = []
tokens = "{\"1 2\",\"2\",\"\",\"2\"}".split(",")
for token in tokens:
    connects.append(token.strip("{\"}").split(" "))

costs = []
tokens = "{\"5 3\",\"7\",\"\",\"13\"}".split(",")
for token in tokens:
    costs.append(token.strip("{\"}").split(" "))
    
adjMatrix = [[-1 for i in range(len(connects))] for j in range(len(connects))]
nodes = [Node(i) for i in range(len(connects))]
print nodes

for i, connect in enumerate(connects):
    for j, element in enumerate(connect):
        try:
            adjMatrix[i][int(element)] = int(costs[i][j])
        except ValueError:
            pass
print adjMatrix

# connects: 1 2, 2, _
# costs: 5 3, 7, _
#   0 1 2  3
# 0 _ 5 3  _
# 1 _ _ 7  _
# 2 _ _ _  _
# 3 _ _ 13 _

for i in range(len(nodes)):
    if nodes[i].state != State.EXPLORED:
        dfs(i)
print nodes
maxCost = 0
for i in range(len(nodes)):
    maxCost = max(maxCost, nodes[i].maxCost)
print("Max cost: " + str(maxCost))

# procedure DFS-iterative(G,v):
#      label v as discovered
#      let S be a stack
#      S.push(v)
#      while S is not empty        
#            t ? S.top 
#            if t is what we're looking for: 
#                return t
#            if there is an edge u adjacent to t that is undiscovered and unexplored
#                 mark u as discovered
#                S.push(u)
#                    else
#                mark t as explored  //Note the distinction between discovered and explored
#               S.pop()
