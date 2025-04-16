import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("stability_region_order3.csv")
inside = data[data['inside'] == 1]

plt.figure(figsize=(7, 7))
plt.scatter(inside['x'], inside['y'], s=1, color='darkorange')
plt.title("Область устойчивости метода Адамса-Мултона, 3-й порядок)")
plt.xlabel("Re(hλ)")
plt.ylabel("Im(hλ)")
plt.axhline(0, color='black', linewidth=1)  # X-axis
plt.axvline(0, color='black', linewidth=1)  # Y-axis
plt.grid(True)
plt.savefig("stability.png")
plt.axis('equal')
plt.show()