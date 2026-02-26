#include <iostream>
#include <fstream>
#include "tp2.hpp"

double g_q = 0.0;
double g_Fe = 0.0;
bool g_non_lineaire = false;

void deriv(int n, double t, double y[], double dy[]) {
    dy[0] = y[1];
    double rappel = g_non_lineaire ? std::sin(y[0]) : y[0];
    dy[1] = -g_q * y[1] - OMEGA * OMEGA * rappel + g_Fe * std::sin(OMEGA_E * t);
}

void save_csv(const std::string& filename, const std::vector<std::string>& headers, 
              const std::vector<std::vector<double>>& data) {
    std::ofstream f(filename);
    for(size_t i=0; i<headers.size(); ++i) {
        f << headers[i] << (i < headers.size()-1 ? "," : "");
    }
    f << std::endl;
    size_t rows = data[0].size();
    size_t cols = data.size();
    for(size_t i=0; i<rows; ++i) {
        for(size_t j=0; j<cols; ++j) {
            f << data[j][i] << (j < cols-1 ? "," : "");
        }
        f << std::endl;
    }
}

int main() {
    std::cout << "Lancement des simulations" << std::endl;
    solve_q13();
    solve_q14();
    solve_q15();
    solve_q16();
    solve_q17();
    
    std::cout << "Terminé" << std::endl;
    return 0;
}