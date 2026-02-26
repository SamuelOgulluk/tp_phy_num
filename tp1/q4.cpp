#include "tp1.hpp"

double w0_q4 = 1.0;    // Pulsation propre

void deriv_q4(int n, double t, double y[], double dy[]) {
    dy[0] = y[1];
    dy[1] = -w0_q4 * w0_q4 * y[0];
}

void solve_q4() {
    double dt = 0.1;
    double Tmax = 50.0;
    int steps = static_cast<int>(Tmax / dt);
    
    // CI
    const int n = 2;
    double state[n];
    state[0] = 1.0;  // x0 = 1.0
    state[1] = 0.0;  // v0 = 0.0

    std::ofstream fichier("resultats/q4.csv");
    if (fichier.is_open()) {
        fichier << "t,x,v" << std::endl;
        
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;
            fichier << t << "," << state[0] << "," << state[1] << std::endl;
            
            // Intégration par Euler
            euler(n, t, state, dt, deriv_q4);
        }
        
        fichier.close();
    }
}
