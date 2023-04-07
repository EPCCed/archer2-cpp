import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

n = 20
steps = 200

fig, ax = plt.subplots()
xdata = np.arange(0, n)
ydata = []
ln, = ax.plot([], [], 'ro')

data = np.loadtxt("implicit_sim.txt")
def init():
    ax.set_xlim(0,n)
    ax.set_ylim(0,1.1)
    return ln,

def update(frame):
    ydata = data[frame]
    ln.set_data(xdata, ydata)
    return ln,

ani = FuncAnimation(fig, update, frames=np.arange(0, 200),
                    init_func=init, blit=True)


plt.show()
