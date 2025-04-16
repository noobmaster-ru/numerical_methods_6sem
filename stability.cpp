#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>

using namespace std;
using cd = complex<double>;

// Проверка устойчивости: решаем характеристическое уравнение 2-го порядка
bool is_stable(cd z) {
    // Характеристическое уравнение:
    // (1 - 5/12 z) r^2 - (1 + 8/12 z) r + (1/12 z) = 0
    cd a = (1.0 - (5.0 / 12.0) * z);
    cd b = -(1.0 + (8.0 / 12.0) * z);
    cd c = (1.0 / 12.0) * z;

    cd D = sqrt(b * b - 4.0 * a * c);
    cd r1 = (-b + D) / (2.0 * a);
    cd r2 = (-b - D) / (2.0 * a);

    return (abs(r1) <= 1.0 && abs(r2) <= 1.0);
}

int main() {
    ofstream fout("stability_region_order3.csv");
    fout << "x,y,inside\n";

    double xmin = -10.0, xmax = 10.0;
    double ymin = -10.0, ymax = 10.0;
    double step = 0.01;

    for (double x = xmin; x <= xmax; x += step) {
        for (double y = ymin; y <= ymax; y += step) {
            cd z(x, y);
            int inside = is_stable(z) ? 1 : 0;
            fout << x << "," << y << "," << inside << "\n";
        }
    }

    fout.close();
    cout << "Готово! Данные сохранены в stability_region_order3.csv" << endl;
    return 0;
}