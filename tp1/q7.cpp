// q7.cpp
#include "tp1.hpp"

void euler(int n, double t, double y[], double dt, 
           void deriv(int, double, double[], double[])) {
    double dy[n];
    
    deriv(n, t, y, dy);
    
    // Euler explicite ici
    for (int i = 0; i < n; ++i) {
        y[i] = y[i] + dy[i] * dt;
    }
}

void solve_q7() { // exemple de résolution de q6
    double dt = 0.1;
    double Tmax = 20.0;
    int steps = static_cast<int>(Tmax / dt);
    
    const int n = 2;
    double state[n];
    state[0] = 1.0;  // x0 = 1.0
    state[1] = 0.0;  // v0 = 0.0

    std::ofstream fichier("resultats/q7.csv");
    if (fichier.is_open()) {
        fichier << "t,x,v" << std::endl;
        
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;
            
            fichier << t << "," << state[0] << "," << state[1] << std::endl;
            
            euler(n, t, state, dt,deriv3);
        }
        
        fichier.close();
    }
}