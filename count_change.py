denoms = (1, 6, 10)
target = 20

ways = [0 for i in range(target + 1)]

for d in denoms:
    for i in range(1, target + 1):
        if i == d:
            ways[i] += 1
        if i + d <= target:
            ways[i + d] += ways[i]
print(ways)
print(ways[target])

    