// q10_q11_maxtries.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "tp3.hpp"


int remplissage_convergence(int max_tries) {
    
    std::vector<double> x_vec, y_vec;
    x_vec.reserve(static_cast<int>(L * L / (PI * R * R)));
    y_vec.reserve(static_cast<int>(L * L / (PI * R * R)));

    int echecs = 0;
    while (echecs < max_tries) {
        double x_n = coord(), y_n = coord();
        if (!check_overlap(x_n, y_n, x_vec, y_vec)) {
            x_vec.push_back(x_n); y_vec.push_back(y_n);
            echecs = 0;
        } else { echecs++; }
    }
    return x_vec.size();
}

void run_and_save_stats(int mt, int M, std::ofstream& file) {
    std::vector<double> eta_vals;
    double sum = 0, var_sum = 0;
    for (int i = 0; i < M; ++i) {
        double eta = (remplissage_convergence(mt) * PI * R * R) / (L * L);
        eta_vals.push_back(eta);
        sum += eta;
    }
    double avg = sum / M;
    for (double e : eta_vals) var_sum += (e - avg) * (e - avg);
    file << mt << " " << avg << " " << std::sqrt(var_sum / M) << std::endl;
}

void exercice_q10_q11() {
    int M = 100;
    std::ofstream file("resultats/q10_q11_maxtries.res");
    file << "# M=" << M << "\n# MAX_TRIES Eta_moyenne Ecart_type" << std::endl;

    for (int mt = 1000; mt <= 32000; mt *= 2) run_and_save_stats(mt, M, file);
    for (int mt = 64000; mt <= 512000; mt *= 2) run_and_save_stats(mt, M, file);
    
    file.close();
}