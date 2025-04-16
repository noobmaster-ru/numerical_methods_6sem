import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from constants import t0, tn, u0, tn, TAU, COEFF
from datetime import datetime

def f(t,u):
    return COEFF*u

def func(u0, h, t_range):
    """Возвращает истинные значения u(t) на равномерной сетке."""
    t_vals = np.arange(t_range[0], t_range[1] + h, h)
    sol = solve_ivp(f, t_range, [u0], t_eval=t_vals, method='RK45')
    return sol.y[0]

if __name__ == "__main__":
    df = pd.read_csv('data.txt', header=None, names=['time', 'u_val'])

    p_appr = df['time'][0]
    t = df['time'][1:]
    u = df['u_val'][1:]

    true_vals = func(u0, TAU, (t0, tn))
    plt.figure(figsize=(14, 7.5))  
    plt.title("Решение задачи Коши", fontsize=14, weight='bold')
    plt.plot(t, u, label=f"Метод Адамса-Мултона, tau = {TAU}, du/dt = {COEFF}u, p_appr = {p_appr} ", marker="o", linewidth=0.1)
    plt.plot(t, true_vals, label="Истинное решение, fsolve", linestyle="-")
    plt.xlabel("t",fontsize=12)
    plt.ylabel("u(t)",fontsize=12)
    plt.grid(True, which='both', linestyle='--', alpha=0.5)
    plt.legend(fontsize=12)
    plt.tight_layout()

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    plt.savefig(f"plot_{timestamp}.png",dpi=300)
    plt.show()