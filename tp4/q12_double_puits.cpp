#include "tp4.hpp"

void save_double_results(const VectorXd& x, const VectorXd& energies, const MatrixXd& ondes, string label, double a, double r1, double r2, double r3, double r4) {
    string suff = "_" + label;
    ofstream f_e(("resultats/q12_double_energies" + suff + ".res").c_str());
    f_e << energies; f_e.close();
    
    ofstream f_o(("resultats/q12_double_ondes" + suff + ".res").c_str());
    MatrixXd R(x.size(), x.size() + 1);
    R.col(0) = x; R.block(0, 1, x.size(), x.size()) = ondes;
    f_o << R; f_o.close();
    
    ofstream f_p(("resultats/q12_double_pot" + suff + ".res").c_str());
    for(int i=0; i<x.size(); i++) f_p << x[i] << " " << V_double(x[i], a, r1, r2, r3, r4) << endl;
    f_p.close();
}

void solve_double_puits_config(int n, double L, double a, double r1, double r2, double r3, double r4, string label) {
    double dx = L / (n - 1), idx2 = 1.0 / (dx * dx);
    VectorXd x(n); MatrixXd H(n, n); H.setZero();

    for (int i = 0; i < n; i++) {
        x[i] = -L / 2.0 + i * dx;
        H(i, i) = 2.0 * idx2 + V_double(x[i], a, r1, r2, r3, r4);
        if (i > 0) H(i, i - 1) = -idx2;
        if (i < n - 1) H(i, i + 1) = -idx2;
    }

    VectorXd energies; MatrixXd ondes;
    solve(H, energies, ondes);
    save_double_results(x, energies, ondes / sqrt(dx), label, a, r1, r2, r3, r4);
}

void solve_q12_double_puits() {
    int n = 1000; double L = 20.0;
    solve_double_puits_config(n, L, 1.0, -2.0, -0.5, 0.5, 2.0, "q12_sym");
    solve_double_puits_config(n, L, 400.0, -2.0, -0.5, 0.5, 2.0, "q13_deep");
    solve_double_puits_config(n, L, 1.0, -2.0, -0.5, 0.0, 2.0, "q14_asym");
}