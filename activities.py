import sys

start = (0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, sys.maxint)
finish = (0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, sys.maxint)

def selectActivities(start, finish, i, n):
    numActivities = 0
    m = i + 1
    while m <= n:
        if start[m] >= finish[i]:
            numActivities += 1
            i = m
        m += 1
    return numActivities

numActivities = selectActivities(start, finish, 0, len(start) - 2)
print("The maximum number of activities that can be scheduled is: " + str(numActivities))


