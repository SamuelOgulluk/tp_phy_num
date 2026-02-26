#include "tp2.hpp"
#include <fstream>

void run_transient(int p_transitoire, int steps, double dt, double& t, double y[2]) {
    for(int p = 0; p < p_transitoire; ++p) {
        for(int s = 0; s < steps; ++s) {
            rk4(2, t, y, dt, deriv);
            if (y[0] > M_PI) y[0] -= 2.0 * M_PI;
            if (y[0] < -M_PI) y[0] += 2.0 * M_PI;
            t += dt;
        }
    }
}

void run_capture(int p_capture, int steps, double dt, double& t, double y[2], 
                 double Fe, std::ofstream& f) {
    for(int p = 0; p < p_capture; ++p) {
        for(int s = 0; s < steps; ++s) {
            rk4(2, t, y, dt, deriv);
            if (y[0] > M_PI) y[0] -= 2.0 * M_PI;
            if (y[0] < -M_PI) y[0] += 2.0 * M_PI;
            t += dt;
        }
        f << Fe << "," << (y[0] * 180.0 / M_PI) << std::endl;
    }
}

void run_bifurcation_scan(double Fe_start, double Fe_end, double dFe, 
                          int p_transitoire, int p_capture, int steps, double dt, 
                          std::ofstream& f) {
    for (double Fe = Fe_start; Fe <= Fe_end; Fe += dFe) {
        g_Fe = Fe;
        double t = 0.0;
        double y[2] = {10.0 * M_PI / 180.0, 0.0};

        run_transient(p_transitoire, steps, dt, t, y);
        run_capture(p_capture, steps, dt, t, y, Fe, f);
    }
}


void solve_q17() {
    g_non_lineaire = true;
    g_q = 0.5;

    // Paramètres de scan
    double Fe_start = 1.35;
    double Fe_end = 1.52;
    double dFe = 0.001;

    // Paramètres stroboscopiques
    double Te = 2.0 * M_PI / OMEGA_E; 
    int steps = 200; 
    double dt = Te / (double)steps;
    
    int p_transitoire = 300; // Périodes ignorées
    int p_capture = 100;     // Périodes gardées

    std::ofstream f("resultats/q17_bifurcation.csv");
    f << "Fe,theta_deg" << std::endl;

    run_bifurcation_scan(Fe_start, Fe_end, dFe, p_transitoire, p_capture, steps, dt, f);
}