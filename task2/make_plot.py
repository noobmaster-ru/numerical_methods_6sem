import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from constants import t0, tn, u0, tn, TAU, COEFF


def f(t,u):
    return COEFF*u

def func(u0, h, t_range):
    """Возвращает истинные значения u(t) на равномерной сетке."""
    t_vals = np.arange(t_range[0], t_range[1] + h, h)
    sol = solve_ivp(f, t_range, [u0], t_eval=t_vals, method='RK45')
    return sol.y[0]

if __name__ == "__main__":
    df = pd.read_csv('data.txt', header=None, names=['time', 'u_val'])

    t = df['time']
    u = df['u_val']

    true_vals = func(u0, TAU, (t0, tn))
    plt.figure(figsize=(14, 7.5))  
    plt.plot(t, u, label="Метод Адамса-Мултона", marker="o")
    plt.plot(t, true_vals, label="Истинное решение", linestyle="--")
    plt.xlabel("t")
    plt.ylabel("u(t)")
    plt.legend()
    plt.grid()
    plt.show()
