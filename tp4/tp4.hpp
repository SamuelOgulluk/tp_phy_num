// tp4.hpp
#ifndef TP4_HPP
#define TP4_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include ".eigen-5.0.0/Eigen/Dense"

using namespace std;
using namespace Eigen;

// Fonction de résolution des valeurs propres
void solve(MatrixXd &z, VectorXd &d, MatrixXd &v);

// Potentiels
double V_puits(double x);
double V_harmonique(double x);
double V_double(double x, double a, double r1, double r2, double r3, double r4);

// Fonctions de résolution par question
void solve_q1_q2_potentiels();
void solve_q6_puits();
void solve_q9_harmonique();
void solve_q12_double_puits();

#endif
