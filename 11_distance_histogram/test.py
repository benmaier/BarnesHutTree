import sys
import numpy as np
import matplotlib.pyplot as pl

def hist(be,data,counts, density=True):
    new_counts = np.zeros(len(be)-1,dtype=int)
    for ndx, C in zip(np.searchsorted(be, data), counts):
        if ndx == 0 or ndx >= len(new_counts):
            continue
        new_counts[ndx] += C
    if density:
        dx = np.diff(be)
        all_counts = new_counts.sum()
        new_counts = new_counts.astype(float) / dx / all_counts

    return new_counts

s = sys.stdin.read()

lines = s.split('\n')
dataBrute = [ line.split(' ') for line in lines[:-1] if line.startswith('0')]
dataTree = [ line.split(' ') for line in lines[:-1] if line.startswith('1')]

fig, axs = pl.subplots(1,2,figsize=(8,4),sharex=True)
axs[0].set_xscale('log')
axs[0].set_yscale('log')

bin_edges = np.logspace(-10,1/2,101,base=2)
x = np.sqrt(bin_edges[1:] * bin_edges[:-1])

for data in [dataBrute, dataTree]:
    A = np.array(data,dtype=object)

    dist = A[:,1].astype(float)
    counts = A[:,2].astype(int)

    histogram = hist(bin_edges, dist, counts)
    for ax in axs:
        ax.plot(x, histogram)

pl.show()
