import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from matplotlib.animation import FuncAnimation
import pandas as pd

# Load data from the CSV file
data = pd.read_csv('Mydata.csv')

# Separate the data into x, y, and z arrays
x = data.iloc[:, 0]
y = data.iloc[:, 1]
z = data.iloc[:, 2]

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot a surface (plane)
ax.plot_trisurf(x, y, z, cmap='viridis', edgecolor='none')

# Set labels
ax.set_xlabel('Charge in Supercapacitor\n(in charge units)', rotation=45)
ax.set_ylabel('Supercapacitor charging rate\n(in charge units per millisecond)', rotation=-45)
ax.set_zlabel('Probability that Supercapacitor\nis not available')

def update_plot(i):
    ax.view_init(elev=10, azim=i)

# Create the animation without using blit
anim = FuncAnimation(fig, update_plot, frames=np.arange(0, 360, 1), interval=0.005)

# Display the animation (optional)
plt.show()
