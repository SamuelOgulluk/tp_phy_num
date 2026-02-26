// q1_q3_homogene.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include "tp3.hpp"

// Fonction de remplissage
int remplissage_homogene(int max_tries, std::vector<double>& x_out, std::vector<double>& y_out) {
    x_out.clear();
    y_out.clear();
    x_out.reserve(static_cast<int>(L * L / (PI * R * R)));
    y_out.reserve(static_cast<int>(L * L / (PI * R * R)));

    int echecs = 0;
    while (echecs < max_tries) {
        double x_new = coord();
        double y_new = coord();
        if (!check_overlap(x_new, y_new, x_out, y_out)) {
            x_out.push_back(x_new);
            y_out.push_back(y_new);
            echecs = 0;
        } else {
            echecs++;
        }
    }
    return x_out.size();
}

void save_results_q1_q3(double avg, double eta, int M, const std::vector<double>& x_final, const std::vector<double>& y_final) {
    std::ofstream file("resultats/q1_q3_homogene.res");
    file << "# MAX_TRIES=" << MAX_TRIES_DEFAULT << " M=" << M << std::endl;
    file << "# Moyenne_particules Eta" << std::endl;
    file << avg << " " << eta << std::endl;
    file.close();

    std::ofstream config_file("resultats/q1_q3_config.res");
    config_file << "# x y R" << std::endl;
    for (size_t i = 0; i < x_final.size(); ++i) {
        config_file << x_final[i] << " " << y_final[i] << " " << R << std::endl;
    }
    config_file.close();
}

void exercice_q1_q3() {
    int M = 1;
    double total_particles = 0;
    std::vector<double> x_final, y_final;

    for (int i = 0; i < M; ++i) {
        std::vector<double> x_temp, y_temp;
        remplissage_homogene(MAX_TRIES_DEFAULT, x_temp, y_temp);
        total_particles += x_temp.size();
        if (i == M - 1) { x_final = x_temp; y_final = y_temp; }
    }

    double avg_particles = total_particles / M;
    double eta = (avg_particles * PI * R * R) / (L * L);

    save_results_q1_q3(avg_particles, eta, M, x_final, y_final);

    std::cout << "Nombre de cercles: " << x_final.size() << std::endl;
    std::cout << "pourcentage de surface couverte (eta): " << eta << std::endl;
}