// q8.cpp
#include "tp1.hpp"


void deriv_particle(int n, double t, double y[], double dy[]) {
    dy[0] = y[2];
    dy[1] = y[3];
    dy[2] = 1.0 + y[3];
    dy[3] = -y[2];
}

void solve_q8() {
    double dt = 0.01;
    double Tmax = 20.0;
    int steps = static_cast<int>(Tmax / dt);
    const int n = 4;
    double state[n] = {0.0, 0.0, 0.0, 0.0};
    std::ofstream fichier("resultats/q8.csv");
    if (fichier.is_open()) {
        fichier << "t,x,y" << std::endl;
        for (int i = 0; i < steps; ++i) {
            fichier << i * dt << "," << state[0] << "," << state[1] << std::endl;
            euler(n, i * dt, state, dt, deriv_particle);
        }
        fichier.close();
    }
}