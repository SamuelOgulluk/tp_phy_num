#include "tp4.hpp"

double V_puits(double) {
    return 0.0;
}

double V_harmonique(double x) {
    return x * x/2; // k=1, m=1 -> omega^2 = 1
}

double V_double(double x, double a, double r1, double r2, double r3, double r4) {
    return a * (x - r1) * (x - r2) * (x - r3) * (x - r4);
}

void solve_q1_q2_potentiels() {
    const int n = 100;
    const double L = 5.0;
    const double dx = L / (n - 1);

    const double a = 1.0;
    const double r1 = -2.0, r2 = -0.5, r3 = 0.5, r4 = 2.0;

    ofstream fichier("resultats/q1_q2_potentials.res");

    for (int i = 0; i < n; i++) {
        const double x = -L / 2.0 + i * dx;
        fichier << x << " "
                << V_puits(x) << " "
                << V_harmonique(x) << " "
                << V_double(x, a, r1, r2, r3, r4) << endl;
    }

    fichier.close();
    cout << "Fichier q1_q2_potentials.res généré." << endl;
}