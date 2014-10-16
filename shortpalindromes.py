import sys

word = sys.argv[1]
shortestPalindrome = ""

def isPalindrome(word):
    s = 0
    e = len(word) - 1
    while s <= e and word[s] == word[e]:
        s += 1
        e -= 1
    return s >= e

shortestPalindromes = [["" for j in range(len(word))] for i in range(len(word) + 1)]    

for i in range(1, len(word) + 1):
    print("i: %d" % (i))
    for j in range(len(word) + 1 - i):
        print("j: %d, ss: %d - %d" % (j, j, j + i))
        print("sub: %s" % (word[j:j + i]))
        # If substring is already a palindrome, store it.
        # if isPalindrome(word[j:j + i]):
        if i == 1:
            shortestPalindromes[i][j] = word[j]
        else:
            if word[j:j + i][0] == word[j:j + i][-1]:
                shortestPalindromes[i][j] = word[j:j + i][0] + shortestPalindromes[i - 2][j + 1] + word[j:j + i][0]
            else:
                candidate1 = word[j:j + i][0] + shortestPalindromes[i - 1][j + 1] + word[j:j + i][0]
                candidate2 = word[j:j + i][-1] + shortestPalindromes[i - 1][j] + word[j:j + i][-1]
                print("candidate1: %s" % (candidate1))
                print("candidate2: %s" % (candidate2))

                if len(candidate1) < len(candidate2) or (len(candidate1) == len(candidate2) and cmp(candidate1, candidate2) < 0):
                    print("candidate1: %s replacing: %s" % (candidate1, shortestPalindromes[i][j]))
                    shortestPalindromes[i][j] = candidate1
                else:
                    print("candidate2: %s replacing: %s" % (candidate2, shortestPalindromes[i][j]))
                    shortestPalindromes[i][j] = candidate2
                
print shortestPalindromes
print("The shortest palindrome is: %s" % (shortestPalindromes[len(word)][0]))

# swap shortest, add to front or back, save if greater
# i:1 j:0, 1, 2, 3  0:4
# 0

# i:2 j:0 - 1; 1 - 2; 2 - 3 0:3
#       0 - 0, 1 - 1; 1 - 1, 2 - 2; 2 - 2, 3 - 3
# lookup 0; 1 determine best, save 
# lookup 1; 2 determine best, save
# lookup 2; 3 determine best, save

# i:3 j:0 - 2; 1 - 3 0:2
#       0 - 1, 1 - 2; 1 - 2, 2 - 3
# lookup 0 - 1; 1 - 2 determine best, save
# lookup 1 - 2; 2 - 3 determine best, save


# i:4 j:0 - 3 0:1
#       0 - 2, 1 - 3
# 2 length 3
# lookup 0 - 2; 1 - 3 determine best, save
