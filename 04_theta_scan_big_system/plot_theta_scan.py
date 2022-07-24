import matplotlib.pyplot as pl
import numpy as np

data = np.loadtxt("run.csv",delimiter=",",skiprows=1)
print(data)
theta = data[:,0]
F = data[:,1]

pl.plot(theta, F)
pl.xlabel('theta')
pl.ylabel('force')

pl.show()
