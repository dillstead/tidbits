from backtrack import Backtrack as Backtrack
import unittest

class PanelTypeData:
    def __init__(self, maxWidth):
        self.panels = []
        self.maxWidth = maxWidth 
        
class PanelType(Backtrack):
    def isSolution(self, a, k, userData):
        if a[k] == userData.maxWidth:
            return True
        else:
            return False
    
    def processSolution(self, a, k, userData):
        userData.panels.append(a[1:k + 1])
        
    def constructCandidates(self, a, k, userData): 
        candidates = []
        if a[k - 1] + 4 <= userData.maxWidth:
            candidates.append(a[k - 1] + 4)
            if a[k - 1] + 6 <= userData.maxWidth:
                candidates.append(a[k - 1] + 6)
        return candidates
    
class PanelOrderData:
    def __init__(self, panels, maxRows, maxWidth):
        self.panels = panels
        self.maxRows = maxRows
        self.maxWidth = maxWidth
        self.numOrders = 0 
        
class PanelOrder(Backtrack):
    def __init__(self):
        self.candidates = None
        
    def isSolution(self, a, k, userData):
        if k == 1:
            print("tried: " + str(a[k]))
        if k == userData.maxRows:
            return True
        else:
            return False
    
    def processSolution(self, a, k, userData):
        userData.numOrders += 1
        
    def constructCandidates(self, a, k, userData):
        if self.candidates is None:
            print("Constructing candidates")
            self.candidates = [[] for i in range(len(userData.panels))]
            for i in range(len(userData.panels)):
                for j in range(i + 1, len(userData.panels)):
                    if self.arePanelsCompatible(userData.panels[i], userData.panels[j], userData.maxWidth):
                        self.candidates[i].append(j)
                        self.candidates[j].append(i)
            print("Done constructing candidates")
            print(self.candidates)
        if k == 1:
            return [i for i in range(len(userData.panels))]
        else:
            return self.candidates[a[k - 1]]

    def arePanelsCompatible(self, panel1, panel2, maxWidth):
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

class PanelsTestCase(unittest.TestCase):
    def testPanelOrders(self):
        maxWidth = 64
        pTypeData = PanelTypeData(maxWidth)
        pTypes = PanelType()
        panel = [0 for i in range(maxWidth + 1)]
        pTypes.backtrack(panel, 0, pTypeData)
        print("num panel types: " + str(len(pTypeData.panels)))
        #for panel in pTypeData.panels:
        #    print(panel)
            
        maxRows = 2
        pOrderData = PanelOrderData(pTypeData.panels, maxRows, maxWidth)
        pOrder = PanelOrder()
        order = [0 for i in range(maxRows + 1)]
        pOrder.backtrack(order, 0, pOrderData)
        print("num panel orders: " + str(pOrderData.numOrders))
        
