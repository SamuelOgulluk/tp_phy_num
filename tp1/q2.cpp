// q2.cpp
#include "tp1.hpp"

void solve_q2() {
    double k = 1.0;
    double k2 = 0.1;
    double dt = 0.1;
    double Tmax = 5.0;
    int steps = static_cast<int>(Tmax / dt);

    std::vector<double> y(steps, 0.0);
    std::vector<double> x(steps, 0.0);
    x[0] = 10.0; // x0

    std::ofstream fichier("resultats/q2.csv");
    if (fichier.is_open()) {
        fichier << "t,x,y" << std::endl;
        //Euler mais sur deux variables (la deuxieme est la dérivée de la premiere)
        for (int i = 0; i < steps - 1; ++i) {
            double t = i * dt;
            double dxdt = -k * x[i];
            double dydt = k * x[i] - k2 * y[i];
            
            x[i+1] = x[i] + dxdt * dt;
            y[i+1] = y[i] + dydt * dt;
            
            fichier << t << "," << x[i] << "," << y[i] << std::endl;
        }
        fichier.close();
    }
}