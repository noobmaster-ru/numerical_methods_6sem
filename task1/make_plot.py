import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv('data.txt', header=None, names=['h', 'diff'])


h = df['h']
error = df['diff']

plt.figure(figsize=(14, 7.5))  
plt.plot(h, error, marker='o', linestyle='-', color='blue', label='error')
plt.xlabel('h', fontsize=14)
plt.ylabel('Difference between appr and real derivative', fontsize=14)
plt.yscale('log')
plt.xscale('log')
plt.title('|approx - exact_derivative| vs h', fontsize=16)
plt.grid(True)
plt.legend()
plt.savefig("picture.jpg")
plt.show()
