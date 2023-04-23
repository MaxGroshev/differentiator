import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots ()
ax.set_xlabel ('x')
ax.set_ylabel ('y')
ax.grid ()

ax.set_title  ('Graph of function')
x = np.linspace (-5, 5, 100)
y = ((-1)*(np.sin((-1)*(x))))
ax.plot (x, y)
plt.savefig('./py_graph/first_pic.png')
