// tp3.hpp
#ifndef TP3_HPP
#define TP3_HPP

#include <random>
#include <cmath>


const double L = 20.0;
const double R = 0.4;
const double PI = 3.14159265358979323846;
const int MAX_TRIES_DEFAULT = 1000;
const double R_SURF = 0.05;
const double U = 10.0;

// Generateur aleatoire global
extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<> dis;
inline double coord() {
    return R + (L - 2.0 * R) * dis(gen);
}

inline double dist_sq(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}


inline double dist_latt(double x, double y) {
    // Distance au point le plus proche du réseau
    double x_closest = std::round(x);
    double y_closest = std::round(y);
    return std::sqrt(std::pow(x - x_closest, 2) + std::pow(y - y_closest, 2));
}


inline bool check_overlap(double x, double y, const std::vector<double>& x_out, const std::vector<double>& y_out) {
    // Vérification du chevauchement avec les cercles déjà placés
    for (size_t i = 0; i < x_out.size(); ++i) {
        if (dist_sq(x, y, x_out[i], y_out[i]) < 4.0 * R * R) return true;
    }
    return false;
}


void exercice_q1_q3();
void exercice_q6_q8();
void exercice_q10_q11();

#endif // TP3_HPP
