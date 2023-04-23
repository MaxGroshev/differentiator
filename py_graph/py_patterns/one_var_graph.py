import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots ()
ax.set_xlabel ('x')
ax.set_ylabel ('y')
ax.grid ()

ax.set_title  ('Graph of function')
x = np.linspace (-5, 5, 100)
