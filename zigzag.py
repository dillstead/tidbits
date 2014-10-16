import sys

#zigzags = (1, 7, 4, 9, 2, 5)
zigzags = (1, 17, 5, 10, 13, 15, 10, 5, 16, 8)
#zigzags = (44,)
#zigzags = (70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32)
#zigzags = (374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 249, 22, 176, 279, 23, 22, 617, 462, 459, 244)

# Maximum zig zag ending at each position (a single number is always a sequence
# of 1)
xzigzags = [1 for i in range(len(zigzags))]
# Difference between each position and the previous number in the sequence
# (0 if no previous element - maximum zig zag is 1)
dzigzags = [0 for i in range(len(zigzags))]
for i in range(1, len(zigzags)):
    for j in range(i):
        diff = zigzags[i] - zigzags[j]
        print diff
        if (diff < 0 and dzigzags[j] >= 0) or (diff > 0 and dzigzags[j] <= 0):
            # Candidate 
            if xzigzags[j] + 1 > xzigzags[i]:
                xzigzags[i] = xzigzags[j] + 1
                dzigzags[i] = diff
print("Max sequence length is " + str(xzigzags[len(xzigzags) - 1]))
      
