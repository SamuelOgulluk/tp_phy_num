#ifndef TP2_HPP
#define TP2_HPP

#include <vector>
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double OMEGA = 1.0;         // Pulsation propre
const double OMEGA_E = 2.0 / 3.0; // Pulsation d'excitation

extern double g_q;           
extern double g_Fe;          
extern bool g_non_lineaire;  

void deriv(int n, double t, double y[], double dy[]);

void rk4(int n, double t, double y[], double dt, void (*f)(int, double, double[], double[]));

void save_csv(const std::string& filename, const std::vector<std::string>& headers, 
              const std::vector<std::vector<double>>& data);

void solve_q13();
void solve_q14();
void solve_q15();
void solve_q16();
void solve_q17();

#endif