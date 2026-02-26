// q11.cpp
#include "tp1.hpp"

void rk2(int n, double x, double y[], double dx, void deriv(int, double, double[], double[])){
    int i;
    double ddx;
    double k1[n], k2[n], yp[n];
    ddx = dx / 2; 

    deriv(n, x, y, k1);
    for (i = 0; i < n; i++) {
        yp[i] = y[i] + k1[i] * ddx;
    }

    deriv(n, x + ddx, yp, k2); 
    for (i = 0; i < n; i++) {
        y[i] = y[i] + k2[i] * dx;
    }
}


double w0_q11 = 1.0;   // Pulsation propre

// Fonction dérivée pour l'oscillateur harmonique
void deriv_q11(int n, double t, double y[], double dy[]) {
    dy[1] = -w0_q11 * w0_q11 * y[0];
    dy[0] = y[1];                          
}

double solution_analytique_q11(double t, double x0, double v0, double w0) {
    return x0 * std::cos(w0 * t) + (v0 / w0) * std::sin(w0 * t);
}

void solve_q11_with_dt(double dt, const std::string& filename) {
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
            double x_th = solution_analytique_q11(t, x0, v0, w0_q11);
            double erreur = state[0] - x_th;
            fichier << t << "," << state[0] << "," << x_th << "," << erreur << std::endl;
            rk2(n, t, state, dt, deriv_q11);
        }
        fichier.close();
    }
}

void solve_q11() {
    solve_q11_with_dt(0.01, "resultats/q11_dt001.csv");
    solve_q11_with_dt(0.1, "resultats/q11_dt01.csv");
    solve_q11_with_dt(0.5, "resultats/q11_dt05.csv");
}

