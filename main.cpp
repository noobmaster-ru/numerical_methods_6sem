#include <iostream>
#include <cmath>
#include "constants.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>


void write_to_file(double tau,std::vector<double> u, std::string filename){
    int N = (int)((tn - t0) / tau);
    std::vector<double> t(N+1);
    t[0] = t0;
    for (int n = 0; n < N; ++n) {
        t[n + 1] = t[n] + tau;
    }
    std::ofstream file(filename);

    // Вывод результата в файл
    for (int i = 0; i <= N; ++i) {
        file << t[i] << "," << u[i] << "\n";
    }
    file.close();
}

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
    std::cerr << "n = " << n << ", Warning: не достигнута сходимость на шаге Адамса." << std::endl;
    return u_next;
}

// Функция, реализующая схему на отрезке [t0, tn] с шагом h
std::vector<double> solveODE(double tau) {
    int N = (int)((tn - t0) / tau);
    std::vector<double> u(N + 1), t(N + 1), f_val(N + 1);
    u[0] = u0;
    t[0] = t0;
    f_val[0] = f(u0, t0);

    // Один шаг Рунге–Кутты
    t[1] = t[0] + tau;
    u[1] = rungeKuttaStep(u[0], t[0], tau);
    f_val[1] = f(u[1], t[1]);

    for (int n = 1; n < N; ++n) {
        t[n + 1] = t[n] + tau;
        u[n + 1] = adamsMoultonStep(u[n - 1], u[n], f_val[n - 1], f_val[n], t[n + 1], tau, n);
        f_val[n + 1] = f(u[n + 1], t[n + 1]);
    }

    return u;
}


// Вычисление значения на сетке tau , tau/2 и tau/4 и запись их в файлы,
//      чтобы потом визуализировать в питоне и применить правило Рунге с fsolve
void begin() {
    std::vector<double> u_h  = solveODE(TAU);
    std::vector<double> u_h_2 = solveODE(TAU / 2);
    std::vector<double> u_h_4 = solveODE(TAU / 4);

    write_to_file(TAU,u_h,"data_u_h.txt");
    write_to_file(TAU/2,u_h_2,"data_u_h_2.txt");
    write_to_file(TAU/4,u_h_4,"data_u_h_4.txt");

}

int main() {
    begin();
    return 0;
}