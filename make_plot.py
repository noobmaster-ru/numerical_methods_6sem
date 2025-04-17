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
    sol = solve_ivp(f, t_range, [u0], t_eval=t_vals, method='RK45',atol=1e-12, rtol=1e-12)
    return sol.y[0]

def exact(u0, h, t_range):
    """Возвращает истинные значения u(t) на равномерной сетке."""
    t_vals = np.arange(t_range[0], t_range[1] + h, h)
    sol = solve_ivp(f, t_range, [u0], t_eval=t_vals, method='RK45',atol=1e-12, rtol=1e-12)
    return sol.y[0][-1]

if __name__ == "__main__":
    df_h = pd.read_csv('data_u_h.txt', header=None, names=['time', 'u_val'])
    t = df_h['time']
    u_h = df_h['u_val']

    df_h_2 = pd.read_csv('data_u_h_2.txt', header=None, names=['time', 'u_val'])
    u_h_2 = df_h_2['u_val']
    df_h_4 = pd.read_csv('data_u_h_4.txt', header=None, names=['time', 'u_val'])
    u_h_4 = df_h_4['u_val']

    true_vals = func(u0, TAU, (t0, tn))

    u_exact = exact(u0, TAU, (t0, tn))
    errors = [
        abs(u_h.iloc[-1] - u_exact),
        abs(u_h_2.iloc[-1] - u_exact),
        abs(u_h_4.iloc[-1] - u_exact)
    ]
    hs = [ TAU, TAU / 2, TAU / 4 ]
    u_approx = [ 
        u_h.iloc[-1],
        u_h_2.iloc[-1],
        u_h_4.iloc[-1]
    ]
    # Оценка порядка
    p1 = np.log2(errors[0] / errors[1])
    p2 = np.log2(errors[1] / errors[2])
    p = np.log2((u_approx[0]-u_approx[1])/(u_approx[1] -u_approx[2]))
    print(f"Точное значение u(1) ≈ {u_exact:.8f}")
    for h, u, e in zip(hs, u_approx, errors):
        print(f"h = {h:.8f} | u_h = {u:.8f} | error = {e:.8f}")

    print(f"\nОценка порядка сходимости:")
    print(f"p1 ≈ log2(E(h)/E(h/2)) = {p1:.8f}")
    print(f"p2 ≈ log2(E(h/2)/E(h/4)) = {p2:.8f}")
    print(f"p ≈ {p:.8f}")

    plt.figure(figsize=(14, 7.5))  
    plt.title("Решение задачи Коши", fontsize=14, weight='bold')
    plt.plot(t, u_h, label=f"Метод Адамса-Мултона, tau = {TAU}, du/dt = {COEFF}u, p ≈ {p1:.3f}", marker="o", linewidth=0.1)
    plt.plot(t, true_vals, label="Истинное решение, fsolve", linestyle="-")
    plt.xlabel("t",fontsize=12)
    plt.ylabel("u(t)",fontsize=12)
    plt.grid(True, which='both', linestyle='--', alpha=0.5)
    plt.legend(fontsize=12)
    plt.tight_layout()

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    plt.savefig(f"plot_{timestamp}.png",dpi=300)
    plt.show()