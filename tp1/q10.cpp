// q10.cpp
#include "tp1.hpp"

// Déclaration externe de rk4
void rk4(int n, double x, double y[], double dx,
         void deriv(int, double, double[], double[]));

double w0_q10 = 1.0;   // Pulsation propre

// OA
void deriv_q10(int n, double t, double y[], double dy[]) {
    dy[0] = y[1];
    dy[1] = -w0_q10 * w0_q10 * y[0];
}

// Solution analytique pour l'oa
double solution_analytique_q10(double t, double x0, double v0, double w0) {
    return x0 * std::cos(w0 * t) + (v0 / w0) * std::sin(w0 * t);
}

void solve_q10_with_dt(double dt, const std::string& filename) {
    double Tmax = 50.0;
    int steps = static_cast<int>(Tmax / dt);
    const int n = 2;
    double state[n];
    state[0] = 1.0;
    state[1] = 0.0;
    double x0 = state[0];
    double v0 = state[1];
    std::ofstream fichier(filename);
    if (fichier.is_open()) {
        fichier << "t,x_numerique,x_analytique,erreur" << std::endl;
        for (int i = 0; i < steps; ++i) {
            double t = i * dt;
            double x_th = solution_analytique_q10(t, x0, v0, w0_q10);
            double erreur = state[0] - x_th;
            fichier << t << "," << state[0] << "," << x_th << "," << erreur << std::endl;
            rk4(n, t, state, dt, deriv_q10);
        }
        fichier.close();
    }
}

void solve_q10() {
    solve_q10_with_dt(0.01, "resultats/q10_dt001.csv");
    solve_q10_with_dt(0.1, "resultats/q10_dt01.csv");
    solve_q10_with_dt(0.5, "resultats/q10_dt05.csv");
}
