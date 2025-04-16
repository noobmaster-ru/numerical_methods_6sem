#include <iostream>
#include <cmath>
#include "constants.h"
#include <fstream>
#include <vector>
#include <iomanip>

// // 13.91 - cходимость теряется
// Правая часть ОДУ
double f(double u, double t) {
    return COEFF*u;
}

// Метод Рунге-Кутты 4 порядка для начальных двух шагов
double rungeKuttaStep(double u, double t, double tau) {
    double k1 = f(u, t);
    double k2 = f(u + tau * k1 / 2.0, t + tau / 2.0);
    double k3 = f(u + tau * k2 / 2.0, t + tau / 2.0);
    double k4 = f(u + tau * k3, t + tau);
    return u + tau * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
}

// Метод Адамса–Мултона третьего порядка
double adamsMoultonStep(double u_prev, double u_curr, double f_prev, double f_curr, double t_next, double tay ,int n, int max_iter = 10, double tol = 1e-6) {
    double u_next = u_curr; // начальное приближение
    for (int k = 0; k < max_iter; ++k) {
        double f_next = f(u_next, t_next);
        double u_new = u_curr + tay / 12.0 * (5 * f_next + 8 * f_curr - f_prev);
        if (fabs(u_new - u_next) < tol) {
            return u_new;
        }
        u_next = u_new;
    }
    std::cerr << "n = " << n << ", Warning: не достигнута сходимость на шаге Адамса. Завершение." << std::endl;
    exit(1); // завершить программу с кодом 1 (ошибка)
    return u_next;
}

// Функция, реализующая схему на отрезке [t0, T] с шагом h
std::vector<double> solveODE(double tay) {
    int N = (int)((tn - t0) / tay);
    std::vector<double> u(N + 1), t(N + 1), f_val(N + 1);
    u[0] = u0;
    t[0] = t0;
    f_val[0] = f(u0, t0);

    // Один шаг Рунге–Кутты
    t[1] = t[0] + tay;
    u[1] = rungeKuttaStep(u[0], t[0], tay);
    f_val[1] = f(u[1], t[1]);

    for (int n = 1; n < N; ++n) {
        t[n + 1] = t[n] + tay;
        u[n + 1] = adamsMoultonStep(u[n - 1], u[n], f_val[n - 1], f_val[n], t[n + 1], tay, n);
        f_val[n + 1] = f(u[n + 1], t[n + 1]);
    }

    return u;
}

// Оценка порядка сходимости по Рунге
void estimateOrder() {
    int N = (int)((tn - t0) / TAU);
    std::vector<double> u_h  = solveODE(TAU);
    std::vector<double> u_h_2 = solveODE(TAU / 2);
    std::vector<double> u_h_4 = solveODE(TAU / 4);

    std::vector<double> t(N + 1);
    t[0] = t0;
    for (int n = 0; n < N; ++n) {
        t[n + 1] = t[n] + TAU;
    }
    // Сравнение в узлах кратных шагу h
    double max_diff1 = 0.0;
    double max_diff2 = 0.0;

    for (size_t i = 0; i < u_h.size(); ++i) {
        double diff1 = fabs(u_h[i] - u_h_2[2 * i]);
        double diff2 = fabs(u_h_2[2 * i] - u_h_4[4 * i]);
        if (diff1 > max_diff1) max_diff1 = diff1;
        if (diff2 > max_diff2) max_diff2 = diff2;
    }
    double p = log2(max_diff1 / max_diff2);
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "||U_h - U_h/2||  = " << max_diff1 << std::endl;
    std::cout << "||U_h/2 - U_h/4||  = " << max_diff2 << std::endl;
    std::cout << "Оценка порядка схемы: p ≈ " << p << std::endl;
    

    std::ofstream file("data.txt");
    file << p << "," << 52 << "\n";
    // Вывод результата
    for (int i = 0; i <= N; ++i) {
        // std::cout << "t = " << t[i] << "\t u = " << u[i] << std::endl;
        file << t[i] << "," << u_h[i] << "\n";
    }
    file.close();
}

int main() {


    estimateOrder();

    return 0;
}