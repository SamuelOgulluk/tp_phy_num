#include "tp2.hpp"
#include <vector>

void run_simulations(const std::vector<double>& Fe_vals, double t_max, double dt, 
                     std::vector<double>& t_vec, std::vector<std::vector<double>>& resultats) {
    for (double Fe : Fe_vals) {
        g_Fe = Fe;
        double t = 0.0;
        double y[2] = {10.0 * M_PI / 180.0, 0.0};
        std::vector<double> current_th;

        while (t <= t_max) {
            if (resultats.empty()) t_vec.push_back(t); // on remplis t une seule fois
            
            current_th.push_back(y[0]);
            
            rk4(2, t, y, dt, deriv);
            
            // on se ramène dans [-pi, pi]
            if (y[0] > M_PI) y[0] -= 2.0 * M_PI; 
            if (y[0] < -M_PI) y[0] += 2.0 * M_PI;
            
            t += dt;
        }
        resultats.push_back(current_th);
    }
}

void solve_q15() {
    g_non_lineaire = true;
    g_q = 0.5;

    std::vector<double> Fe_vals = {1.4, 1.44, 1.465, 1.5};
    double t_max = 100.0;
    double dt = 0.05;
    
    std::vector<double> t_vec;
    std::vector<std::vector<double>> resultats; // Stocke les theta pour chaque Fe

    run_simulations(Fe_vals, t_max, dt, t_vec, resultats);

    std::vector<std::vector<double>> data_to_save;
    data_to_save.push_back(t_vec);
    for(auto& v : resultats) data_to_save.push_back(v);

    save_csv("resultats/q15_data.csv", 
             {"t", "Fe_1.4", "Fe_1.44", "Fe_1.465", "Fe_1.5"}, 
             data_to_save);
}