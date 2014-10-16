import sys

class Mine:
    id = -1
    
    def __init__(self, mineDef):
        self.oreProbs = [int(oreProb) for oreProb in mineDef.split(", ")]
        Mine.id += 1
        self.id= Mine.id
    
    def allocateMiners(self, numMiners):
        # determine profit
        profit = 0
        for i in range(len(self.oreProbs)):
            if i < numMiners:
                profit += ((numMiners - i) * -20  + i * 50) * self.oreProbs[i] 
            elif i > numMiners:
                profit += numMiners * 60 * self.oreProbs[i]
            else:
                profit += numMiners * 50 * self.oreProbs[i]
            i += 1
        return profit / 100

mines = []    
mineDefs = ("000, 030, 030, 040, 000, 000, 000", "020, 020, 020, 010, 010, 010, 010")

for mineDef in mineDefs:
    mines.append(Mine(mineDef))

for mine in mines:
    print("mine: %d  " % (mine.id))
    for numMiners in range(1, 7):
        profit = mine.allocateMiners(numMiners)
        sys.stdout.write("%d:%d  " % (numMiners, profit))
    print("")     
