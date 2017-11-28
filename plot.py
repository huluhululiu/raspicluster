import numpy as np
import matplotlib as mpl

## agg backend is used to create plot as a .png file
mpl.use('agg')

import matplotlib.pyplot as plt

data = np.genfromtxt('latency')

data_to_plot = [data]
print(data)

fig = plt.figure(1, figsize=(9, 6))

# Create an axes instance
ax = fig.add_subplot(111)

# Create the boxplot
boxplot(data)

# Save the figure
fig.savefig('fig1.png', bbox_inches='tight')