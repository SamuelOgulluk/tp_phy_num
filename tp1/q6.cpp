// q6.cpp
#include "tp1.hpp"
double w0_global = 1.0;   // Pulsation propre pour deriv3

void deriv3(int n, double t, double y[], double dy[]) {
    dy[0] = y[1];                       
    dy[1] = -w0_global * w0_global * y[0]; 
}

void euler_q6(int n, double t, double y[], double dt, double dy[]) {
    deriv3(n, t, y, dy);
    for (int i = 0; i < n; ++i) {
        y[i] += dy[i] * dt;
    }
}

void solve_q6() {
    double dt = 0.1;
    double Tmax = 20.0;
    int steps = static_cast<int>(Tmax / dt);
    const int n = 2;
    double state[n];
    state[0] = 1.0;  // x0 = 1.0
    state[1] = 0.0;  // v0 = 0.0
    std::ofstream fichier("resultats/q6.csv");
    if (fichier.is_open()) {
        fichier << "t,x,v" << std::endl;
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;   
            fichier << t << "," << state[0] << "," << state[1] << std::endl;
            double dy[n];
            euler_q6(n, t, state, dt, dy);
        }
        fichier.close();
    }
}
