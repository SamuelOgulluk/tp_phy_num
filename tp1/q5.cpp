// q5.cpp
#include "tp1.hpp"
#include <cmath>

double k_q5 = 1.0;   // Constante de désintégration de X
double k2_q5 = 0.1;  //  Y

// Forward declaration
void deriv_q5(int n, double t, double y[], double dy[]);

void euler_q5(int n, double t, double y[], double dt, double dy[]) {

    deriv_q5(n, t, y, dy);
    
    for (int i = 0; i < n; ++i) {
        y[i] += dy[i] * dt;
    }
}

void deriv_q5(int n, double t, double y[], double dy[]) {
    dy[0] = -k_q5 * y[0];           // dx/dt
    dy[1] = k_q5 * y[0] - k2_q5 * y[1]; // dy/dt
}

void solve_q5() {
    double dt = 0.1;
    double Tmax = 5.0;
    int steps = static_cast<int>(Tmax / dt);
    
    // CI
    const int n = 2;
    double state[n];
    state[0] = 10.0; // x0 = 10.0
    state[1] = 0.0;  // y0 = 0.0

    std::ofstream fichier("resultats/q5.csv");
    if (fichier.is_open()) {
        fichier << "t,x,y" << std::endl;
        
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;
            
            fichier << t << "," << state[0] << "," << state[1] << std::endl;
            
            double dy[n];
            euler_q5(n, t, state, dt, dy);
        }
        
        fichier.close();
    }
}
