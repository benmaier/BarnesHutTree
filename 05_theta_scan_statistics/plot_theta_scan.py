import matplotlib.pyplot as pl
import numpy as np

data = np.loadtxt("run.csv",delimiter=",",skiprows=1)

theta = data[:,0]

F = data[:,1]
Fstd = data[:,2]
F_median = data[:,3]
F_lower = data[:,4]
F_upper = data[:,5]

t = data[:,6]
tstd = data[:,7]
t_median = data[:,8]
t_lower = data[:,9]
t_upper = data[:,10]

fig, ax = pl.subplots(4,1,figsize=(3,8),sharex=True)
ax[0].plot(theta, F)
ax[1].plot(theta, F_median)
ax[0].fill_between(theta, F-Fstd, F+Fstd, edgecolor='None', alpha=0.3)
ax[1].fill_between(theta, F_lower, F_upper, edgecolor='None', alpha=0.3)
ax[0].set_ylabel('mean relative force')
ax[1].set_ylabel('median relative force')

ax[2].plot(theta, t)
ax[3].plot(theta, t_median)
ax[2].fill_between(theta, t-tstd, t+tstd, edgecolor='None', alpha=0.3)
ax[3].fill_between(theta, t_lower, t_upper, edgecolor='None', alpha=0.3)
#ax[2].set_yscale('log')
#ax[3].set_yscale('log')
ax[2].set_ylabel('mean time (ns)')
ax[3].set_ylabel('median time (ns)')
#pl.ylim(0,2)
ax[3].set_xlabel('theta')

fig.tight_layout()

fig.savefig('accuracy_and_time.png')


pl.show()
