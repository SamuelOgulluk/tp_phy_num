// q9.cpp
#include "tp1.hpp"

double w0_q9 = 1.0;   // Pulsation propre


void deriv_q9(int n, double t, double y[], double dy[]) {
    dy[0] = y[1];
    dy[1] = -w0_q9 * w0_q9 * y[0];
}

double solution_analytique(double t, double x0, double v0, double w0) {
    return x0 * std::cos(w0 * t) + (v0 / w0) * std::sin(w0 * t);
}

void solve_q9_with_dt(double dt, const std::string& filename) {
    double Tmax = 50.0;
    int steps = static_cast<int>(Tmax / dt);
    const int n = 2;
    double state[n];
    state[0] = 1.0;  // x0 = 1.0
    state[1] = 0.0;  // v0 = 0.0
    double x0 = state[0];
    double v0 = state[1];
    std::ofstream fichier(filename);
    if (fichier.is_open()) {
        fichier << "t,x_numerique,x_analytique,erreur" << std::endl;
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;
            double x_th = solution_analytique(t, x0, v0, w0_q9);
            double erreur = state[0] - x_th;
            fichier << t << "," << state[0] << "," << x_th << "," << erreur << std::endl;
            euler(n, t, state, dt, deriv_q9);
        }
        fichier.close();
    }
}

void solve_q9() {
    // Test avec différents pas de temps
    solve_q9_with_dt(0.01, "resultats/q9_dt001.csv");
    solve_q9_with_dt(0.005, "resultats/q9_dt0005.csv");
    solve_q9_with_dt(0.001, "resultats/q9_dt0001.csv");
}
