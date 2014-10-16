import unittest
import time

def print_timing(func):
    def wrapper(*arg):
        t1 = time.time()
        res = func(*arg)
        t2 = time.time()
        print('%s took %0.3f ms' % (func.__name__, (t2-t1)*1000.0))
        return res
    return wrapper

def extendPrevPanelTypes(panelTypes, cur, prev):
    for prevPanelType in panelTypes[cur - prev]:
        newPanelType = list(prevPanelType)
        newPanelType.append(newPanelType[-1] + prev)
        panelTypes[cur].append(newPanelType)
    
@print_timing
def enumeratePanelTypes(maxWidth):
    panelTypes = [[] for w in range(maxWidth + 1)]
    panelTypes[4] = [[4]]
    panelTypes[6] = [[6]]
    for w in range(8, maxWidth + 1, 2):
        extendPrevPanelTypes(panelTypes, w, 4)
        extendPrevPanelTypes(panelTypes, w, 6)
    return panelTypes[maxWidth]

@print_timing
def findValidNeighbors(panelTypes, maxWidth):
    neighbors = [[] for i in range(len(panelTypes))]
    for i in range(len(panelTypes)):
        for j in range(i + 1, len(panelTypes)):
            if arePanelsCompatible(panelTypes[i], panelTypes[j], maxWidth):
                neighbors[i].append(j)
                neighbors[j].append(i)
    return neighbors

def arePanelsCompatible(panel1, panel2, maxWidth):
    i = 0 
    j = 0
    while i < len(panel1) and j < len(panel2):
        if panel1[i] < panel2[j]:
            i += 1
        elif panel1[i] > panel2[j]:
            j += 1
        else:
            if panel1[i] == maxWidth:
                return True
            return False
    return True

@print_timing
def getPanelCounts(neighbors, numPanelTypes, maxRows):
    panelCounts = [[0 for j in range(numPanelTypes)] for i in range(maxRows + 1)]
    for j in range(numPanelTypes):
        panelCounts[1][j] = 1
    for i in range(2, maxRows + 1):
        for j in range(numPanelTypes):
            panelCounts[i][j] = sum(list(map(lambda x: panelCounts[i - 1][x], neighbors[j])))
    return sum(panelCounts[maxRows])

class PanelsTestCase(unittest.TestCase):
    def testPanelOrders(self):
        maxWidth = 36
        maxRows = 5
        #maxWidth = 36
        #maxRows = 5
        panelTypes = enumeratePanelTypes(maxWidth)
        neighbors = findValidNeighbors(panelTypes, maxWidth)
        panelCounts = getPanelCounts(neighbors, len(panelTypes), maxRows)
        print(panelCounts)


        