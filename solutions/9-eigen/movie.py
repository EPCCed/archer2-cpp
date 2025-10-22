import argparse
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def plot(simulation):
    n = 20
    steps = 200

    fig, ax = plt.subplots()
    xdata = np.arange(0, n)
    ydata = []
    ln, = ax.plot([], [], 'ro')

    data = np.loadtxt(f"{simulation}_sim.txt")

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

    ani.save(f"{simulation}.gif", writer="pillow")
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='movie.py', description='Create animation from simulation output.')
    parser.add_argument('simulation', default='implicit', const='implicit', nargs='?', choices=['implicit', 'explicit', 'sparse'])
    
    args = parser.parse_args()
    plot(args.simulation)
