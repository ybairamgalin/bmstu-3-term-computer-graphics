import matplotlib.pyplot as plt
import sys, subprocess

subprocess.call(["pwd"], shell=True)
file = open("../basicGeometry/time.txt", "r")

lines = file.readlines()

for line in lines:
    line.replace(" \n", "")

x = [500, 1000, 5000, 10000, 15000, 20000]
y = [1, 2, 5, 10, 15, 25]
values = [[], [], [], [], []]

for line in lines:
    split = line.split()
    values[0].append(int(split[0]))
    values[1].append(int(split[1]))
    values[2].append(int(split[2]))
    values[3].append(int(split[3]))
    values[4].append(int(split[4]))

plt.plot(x, values[0], label="Canonical")
plt.plot(x, values[1], label="Parametric")
plt.plot(x, values[2], label="Bresenham")
plt.plot(x, values[3], label="Mid point")
plt.plot(x, values[4], label="Lib")

plt.legend(loc="upper left")
plt.show()
