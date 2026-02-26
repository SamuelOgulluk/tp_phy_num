#include "tp2.hpp"
#include <vector>

void simulation_wrapper(double q, double Fe, std::vector<double>& th, std::vector<double>& dth) {
    g_q = q;
    g_Fe = Fe;
    double t = 0.0, dt = 0.04, t_max = 50.0;
    double y[2] = {10.0 * M_PI / 180.0, 0.0};

    while(t <= t_max) {
        th.push_back(y[0]);
        dth.push_back(y[1]);
        rk4(2, t, y, dt, deriv);
        t += dt;
    }
}

void solve_q14() {
    g_non_lineaire = false;

    std::vector<double> th_lib, dth_lib;
    std::vector<double> th_amort, dth_amort;
    std::vector<double> th_force, dth_force;

    simulation_wrapper(0.0, 0.0, th_lib, dth_lib);
    simulation_wrapper(1.0, 0.0, th_amort, dth_amort);
    simulation_wrapper(1.0, 1.0, th_force, dth_force);

    save_csv("resultats/q14_data.csv", 
             {"th_lib", "dth_lib", "th_amort", "dth_amort", "th_force", "dth_force"}, 
             {th_lib, dth_lib, th_amort, dth_amort, th_force, dth_force});
}