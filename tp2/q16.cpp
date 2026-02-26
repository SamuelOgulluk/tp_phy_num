#include "tp2.hpp"
#include <vector>

void run_divergence_simulation(double t_max, double dt, double yA[2], double yB[2], std::vector<double>& t_vec, std::vector<double>& th_A, std::vector<double>& th_B, std::vector<double>& diff) {
    double t = 0.0;
    auto wrap = [](double& val) { // on ramene dans [-pi, pi]
        if (val > M_PI) val -= 2.0 * M_PI;
        if (val < -M_PI) val += 2.0 * M_PI;
    };

    while (t <= t_max) {
        t_vec.push_back(t);
        th_A.push_back(yA[0]);
        th_B.push_back(yB[0]);
        diff.push_back(std::abs(yA[0] - yB[0]));

        rk4(2, t, yA, dt, deriv);
        rk4(2, t, yB, dt, deriv);

        wrap(yA[0]); 
        wrap(yB[0]);

        t += dt;
    }
}

void solve_q16() {
    g_non_lineaire = true;
    g_q = 0.5;
    g_Fe = 1.5;

    double t_max = 100.0, dt = 0.05;

    // CI proches
    double yA[2] = {10.0 * M_PI / 180.0, 0.0};
    double yB[2] = {9.999 * M_PI / 180.0, 0.0};

    std::vector<double> t_vec, th_A, th_B, diff;

    run_divergence_simulation(t_max, dt, yA, yB, t_vec, th_A, th_B, diff);

    save_csv("resultats/q16_data.csv", 
             {"t", "th_A", "th_B", "delta_abs"}, 
             {t_vec, th_A, th_B, diff});
}