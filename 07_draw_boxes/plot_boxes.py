import matplotlib.pyplot as pl
import numpy as np

d = np.loadtxt('boxes.csv', skiprows=1, delimiter=',')
x = d[:,0]
y = d[:,1]
w = d[:,2]
h = d[:,3]


iboxes = np.where(np.logical_and(w > 0., h > 0.))[0]
ipoints = np.where(np.logical_and(w == 0., h == 0.))[0]

px = x[ipoints]
py = y[ipoints]

fig, ax = pl.subplots(1,1,figsize=(5,5))

ax.set_aspect('equal', 'box')
ax.plot(px,py,'xk',markersize=3)

from matplotlib.collections import PatchCollection
from matplotlib.patches import Rectangle

rects = []
for i in iboxes:
    rect = Rectangle((x[i], y[i]), w[i], h[i])
    rects.append(rect)

patches = PatchCollection(rects,
                          alpha = 0.05,
                          edgecolor='k',
                          #zorder=-1000,
                          )

ax.add_collection(patches)

fig.tight_layout()
fig.savefig('boxes.png')


pl.show()
