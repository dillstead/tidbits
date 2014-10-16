class Backtrack:
    def backtrack(self, a, k, userData):
        if (self.isSolution(a, k, userData)):
            self.processSolution(a, k, userData)
        else:
            k += 1
            candidates = self.constructCandidates(a, k, userData)
            for candidate in candidates:
                a[k] = candidate;
                self.makeMove(a, k, userData)
                self.backtrack(a, k, userData)
                self.unmakeMove(a, k, userData)
    
    def makeMove(self, a, k, userData):
        return
    
    def unmakeMove(self, a, k, userData):
        return
    
        
