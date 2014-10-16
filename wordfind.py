#grid = ("TEST", "GOAT", "BOAT")
#words = ("GOAT", "BOAT", "TEST", "TGB", "TTT", "ST")
#grid = ("SXXX", "XQXM", "XXLA", "XXXR")
#words = ("SQL", "RAM")
grid = ("EASYTOFINDEAGSRVHOTCJYG", "FLVENKDHCESOXXXXFAGJKEO", "YHEDYNAIRQGIZECGXQLKDBI", "DEIJFKABAQSIHSNDLOMYJIN",
 "CKXINIMMNGRNSNRGIWQLWOG", "VOFQDROQGCWDKOUYRAFUCDO", "PFLXWTYKOITSURQJGEGSPGG")
words = ("EASYTOFIND", "DIAG", "GOING", "THISISTOOLONGTOFITINTHISPUZZLE")

rows = len(grid)
cols = len(grid[0])

def matchDiagnonals(rows, cols, word):
    # left-to-right by diagonal, starting with lowest numbered row
    for diagonal in range(rows + cols):
        if diagonal < cols:
            x = 0
            y = diagonal
        else:
            x = diagonal - cols + 1
            y = 0
        maxSize = min(rows - x, cols - y)
        for i in range(maxSize):
            #print("%d, %d" % (x, y))
            tx = x
            ty = y
            w = 0
            while tx < rows and ty < cols and w < len(word):
                if grid[tx][ty] == word[w]:
                    tx += 1
                    ty += 1
                    w += 1
                else:
                    break
            if w == len(word):
                return (x, y)
            x += 1
            y += 1
    return None
    
def matchRows(rows, cols, word):
    # left-to-right by row
    for x in range(rows):
        for y in range(cols):
            #print("%d, %d" % (x, y))
            ty = y
            w = 0
            while ty < cols and w < len(word): 
                if grid[x][ty] == word[w]:
                    ty += 1
                    w += 1
                else:
                    break
            if w == len(word):
                return (x, y)
    return None

def matchCols(rows, cols, word):
    # top-to-bottom by column
    for y in range(cols):
        for x in range(rows):
            #print("%d, %d" % (x, y))
            tx = x
            w = 0
            while tx < rows and w < len(word): 
                if grid[tx][y] == word[w]:
                    tx += 1
                    w += 1
                else:
                    break
            if w == len(word):
                return (x, y)
    return None
    
for word in words:
    matches = []
    #print("Match: " + word)
    rowMatch = matchRows(rows, cols, word)
    if rowMatch != None:
        #print("Row match: %d, %d" % (rowMatch))
        matches.append(rowMatch)
        
    colMatch = matchCols(rows, cols, word)
    if colMatch != None:
        #print("Col match: %d, %d" % (colMatch))
        matches.append(colMatch)
        
    diagonalMatch = matchDiagnonals(rows, cols, word)
    if diagonalMatch != None:
        #print("Diagonal match: %d, %d" % (diagonalMatch))
        matches.append(diagonalMatch)
    
    if (len(matches) > 0):
        matches = sorted(matches)
        print(word + " matches at x: " + str(matches[0][0]) + " y: " + str(matches[0][1]))
    else:
        print("No matches for" + word + " found")

                
                    
                
                


        
        
    
