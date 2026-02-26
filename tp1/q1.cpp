#include "tp1.hpp"

void solve_q1() {
    double k = 1.0;
    double Tmax = 5.0;
    double dt = 0.1;
    double x0 = 10.0;
    int steps = static_cast<int>(Tmax / dt);
    
    std::vector<double> x(steps);
    x[0] = x0;
    
    std::ofstream fichier("resultats/q1.csv");
    if (fichier.is_open()) {
        fichier << "t,x_euler,x_analytique" << std::endl;
        
        for (int i = 0; i < steps - 1; ++i) {
            double t = i * dt;
            x[i+1] = x[i] - k * x[i] * dt;
            double x_analytique = x0 * std::exp(-k * t);
            fichier << t << "," << x[i] << "," << x_analytique << std::endl;
        }
        fichier.close();
    }
}