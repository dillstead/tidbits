import sys

dim = 3
sx = 0
sy = 0
fx = 1
fy = 0
totalMoves = 1

#dim = 3
#sx = 0
#sy = 0
#fx = 1
#fy = 2
#totalMoves = 1

#dim = 3
#sx = 0
#sy = 0
#fx = 2
#fy = 2
#totalMoves = 1

#dim = 3
#sx = 0
#sy = 0
#fx = 0
#fy = 0
#totalMoves = 2

#dim = 100
#sx = 0
#sy = 0
#fx = 0
#fy = 99
#totalMoves = 50

moves = [[0,1],[1,0],[-1,0],[0,-1],[-1,-1],[1,1],[1,-1],[-1,1],[1,2],[2,1],[-1,2],[1,-2],[2,-1],[-2,1],[-2,-1],[-1,-2]]
numMoves = [[[0 for m in range(totalMoves + 1)] for y in range(dim)] for x in range(dim)]
numWays = [[[0 for m in range(totalMoves + 1)] for y in range(dim)] for x in range(dim)]

# Seed the starting position
numMoves[sx][sy][0] = 1
numWays[sx][sy][0] = 1
printMoves(numMoves, 0)

for m in range(totalMoves):
    for x in range(dim):
        for y in range(dim):
            if numMoves[x][y][m] == 1:
                for dx, dy in moves:
                    if x + dx >= 0 and x + dx < dim and y + dy >= 0 and y + dy < dim:
                        numMoves[x + dx][y + dy][m + 1] = 1
                        numWays[x + dx][y + dy][m + 1] += numMoves[x][y][m]
    printMoves(numMoves, 1)
