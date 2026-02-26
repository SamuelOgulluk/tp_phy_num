#include "tp4.hpp"

void save_harm_results(double L, int n, double dx, const VectorXd& x, const VectorXd& energies, const MatrixXd& ondes) {
    VectorXd eth(n);
    double hbar_w = sqrt(2.0);
    for (int p = 0; p < n; p++) eth[p] = (p + 0.5) * hbar_w;

    string suff = "_n" + to_string(n) + "_L" + to_string((int)L);
    ofstream f_val(("resultats/q9_harm_energies" + suff + ".res").c_str());
    MatrixXd E_out(n, 2);
    E_out.col(0) = energies; E_out.col(1) = eth;
    f_val << E_out; f_val.close();

    ofstream f_vec(("resultats/q9_harm_ondes" + suff + ".res").c_str());
    MatrixXd R(n, n + 1);
    R.col(0) = x; R.block(0, 1, n, n) = ondes;
    f_vec << R; f_vec.close();

    ofstream f_pot(("resultats/q9_harm_pot" + suff + ".res").c_str());
    for(int i=0; i<n; i++) f_pot << x[i] << " " << V_harmonique(x[i]) << endl;
    f_pot.close();
}

void solve_harmonique_pour_L(double L, int n) {
    double dx = L / (n - 1), idx2 = 1.0 / (dx * dx);
    VectorXd x(n); MatrixXd H(n, n); H.setZero();

    for (int i = 0; i < n; i++) {
        x[i] = -L / 2.0 + i * dx;
        H(i, i) = 2.0 * idx2 + V_harmonique(x[i]);
        if (i > 0) H(i, i - 1) = -idx2;
        if (i < n - 1) H(i, i + 1) = -idx2;
    }

    VectorXd energies; MatrixXd ondes;
    solve(H, energies, ondes);
    save_harm_results(L, n, dx, x, energies, ondes / sqrt(dx));
}

void solve_q9_harmonique() {
    solve_harmonique_pour_L(5.0, 100);
    solve_harmonique_pour_L(20.0, 100);
}