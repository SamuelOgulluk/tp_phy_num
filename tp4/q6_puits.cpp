#include "tp4.hpp"

void save_puits_results(int n, double L, const VectorXd& x, const VectorXd& energies, const MatrixXd& ondes) {
    VectorXd energies_theo(n);
    for (int p = 0; p < n; p++) {
        double k = M_PI * (p + 1) / L;
        energies_theo[p] = k * k;
    }

    std::ofstream f_val("resultats/q6_puits_energies.res");
    MatrixXd E_out(n, 2);
    E_out.col(0) = energies; E_out.col(1) = energies_theo;
    f_val << E_out; f_val.close();

    std::ofstream f_vec("resultats/q6_puits_ondes.res");
    MatrixXd R(n, n + 1);
    R.col(0) = x; R.block(0, 1, n, n) = ondes;
    f_vec << R; f_vec.close();
}

void solve_q6_puits() {
    int n = 100; double L = 5.0;
    double dx = L / (n - 1);
    double idx2 = 1.0 / (dx * dx);

    VectorXd x(n); MatrixXd H(n, n); H.setZero();
    for (int i = 0; i < n; i++) {
        x[i] = -L / 2.0 + i * dx;
        H(i, i) = 2.0 * idx2 + V_puits(x[i]);
        if (i > 0) H(i, i - 1) = -idx2;
        if (i < n - 1) H(i, i + 1) = -idx2;
    }

    VectorXd energies; MatrixXd ondes;
    solve(H, energies, ondes);
    save_puits_results(n, L, x, energies, ondes / sqrt(dx));
}