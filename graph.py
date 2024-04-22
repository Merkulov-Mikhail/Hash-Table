import matplotlib.pyplot as plt
import matplotlib.pylab as plb
import numpy as np


try:
    files = ["results/hash1.txt",
             "results/hash2.txt",
             "results/hash3.txt",
             "results/hash4.txt",
             "results/hash5.txt",
             "results/hash6.txt",
             "results/hash7.txt",]
    for file in files:
        data = list(map(int, open(file, "r").readline().split()))
        plt.bar(list(range(1, len(data) + 1)), data)
        graph = plb.gcf()
        graph.canvas.manager.set_window_title(file)
        plt.show()

except ZeroDivisionError:
    print("Can't find the results")
