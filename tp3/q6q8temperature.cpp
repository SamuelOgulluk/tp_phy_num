// q6_q8_temperature.cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "tp3.hpp"


bool check_metropolis(double x, double y, double T) {
    // Test interaction surface
    double d = dist_latt(x, y);
    if (d <= R_SURF) return true;
    if (T == 0.0) return false;
    return dis(gen) <= std::exp(-U / T);
}


int remplissage_temperature(double T, int max_tries, std::vector<double>& x_out, std::vector<double>& y_out) {
    x_out.clear(); y_out.clear();
    x_out.reserve(2500); y_out.reserve(2500);
    int echecs = 0;
    while (echecs < max_tries) {
        double x_new = coord(); double y_new = coord();
        if (!check_overlap(x_new, y_new, x_out, y_out) && check_metropolis(x_new, y_new, T)) {
            x_out.push_back(x_new); y_out.push_back(y_new);
            echecs = 0;
        } else { echecs++; }
    }
    return x_out.size();
}

void save_temp_config(double T, const std::vector<double>& x, const std::vector<double>& y) {
    std::string filename = "resultats/q6_q8_config_T" + std::to_string(static_cast<int>(T)) + ".res";
    std::ofstream config_file(filename);
    config_file << "# x y R (T = " << T << ")" << std::endl;
    for (size_t i = 0; i < x.size(); ++i) {
        config_file << x[i] << " " << y[i] << " " << R << std::endl;
    }
    config_file.close();
}

void process_temperature(double T, int M, int max_tries, std::ofstream& file, const std::vector<double>& T_save_list) {
    std::vector<double> x_f, y_f;
    double total = 0;
    for (int i = 0; i < M; ++i) {
        std::vector<double> x_t, y_t;
        remplissage_temperature(T, max_tries, x_t, y_t);
        total += x_t.size();
        if (i == M - 1) { x_f = x_t; y_f = y_t; }
    }
    double eta = (total / M * PI * R * R) / (L * L);
    file << std::fixed << std::setprecision(1) << T << " " << std::setprecision(6) << eta << std::endl;
    for (double T_s : T_save_list) {
        if (std::abs(T - T_s) < 0.01) { save_temp_config(T, x_f, y_f); break; }
    }
}

void exercice_q6_q8() {
    int M = 100, max_tries = 10000;
    std::ofstream file("resultats/q6_q8_temperature.res");
    file << "# M=" << M << " max_tries=" << max_tries << "\n# Temperature Eta" << std::endl;
    std::vector<double> T_to_save = {0.0, 1.0, 2.0, 5.0, 10.0};
    for (double T = 0.0; T <= 10.0; T += 0.5) {
        process_temperature(T, M, max_tries, file, T_to_save);
    }
    file.close();
}