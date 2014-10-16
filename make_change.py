import sys

denominations = [1, 5, 10, 25, 50]
total = int(sys.argv[1])
minCoins = [0 for i in range(total + 1)]
lastCoins = [0 for i in range(total + 1)]

for value in range(1, total + 1):
    minCoin = value
    lastCoin = 0
    for denomination in denominations:
        if value - denomination >= 0:
            if minCoins[value - denomination] + 1 <= minCoin:
                minCoin = minCoins[value - denomination] + 1
                lastCoin = denomination
    minCoins[value] = minCoin
    lastCoins[value] = lastCoin

print("Minimum coins to make " + str(total) + " cents is " + str(minCoins[value]))

value = total
while value > 0:
    print(str(lastCoins[value]))
    value = value - lastCoins[value]
    




