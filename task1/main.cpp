#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

double derivative_approx(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

int main() {
    double x0 =  M_PI / 4;  // Точка, в которой считаем производную
    double exact_derivative = std::cos(x0);  // Точное значение производной sin(x) -> cos(x)
    std::ofstream file("data.txt");
    std::cout << std::setw(7) << "h" 
              << std::setw(30) << "Approx. Derivative " 
              << std::setw(13) << "Error" << std::endl;
    
    for (double h = 1.0; h >= 1e-17;  h /= 10) {
        double approx = derivative_approx(std::sin, x0, h);
        double error = std::abs(approx - exact_derivative);
        
        std::cout << std::scientific << std::setprecision(8)
                  << std::setw(10) << h 
                  << std::setw(20) << approx
                  << std::setw(20) << error << std::endl;
        file << h << "," << error << "\n";
    }
    file.close();
    return 0;
}