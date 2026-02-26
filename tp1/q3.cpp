#include "tp1.hpp"

void solve_q3() {
    double dt = 0.1;
    double Tmax = 20.0;
    int steps = static_cast<int>(Tmax / dt);
    // CI
    const int n = 2;
    double state[n];
    state[0] = 1.0;  // x0 = 1.0
    state[1] = 0.0;  // v0 = 0.0

    std::ofstream fichier("resultats/q3.csv");
    if (fichier.is_open()) {
        fichier << "t,x,v" << std::endl;
        
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;            
            fichier << t << "," << state[0] << "," << state[1] << std::endl;
            euler(n, t, state, dt, deriv3);
        }
        fichier.close();
    }
}
