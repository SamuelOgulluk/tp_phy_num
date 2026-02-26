// tp1.hpp
#ifndef TP1_HPP
#define TP1_HPP

#include <vector>
#include <functional>
#include <fstream>
#include <cmath>
#include <iostream>

using DerivFunc = std::function<void(int, double, const std::vector<double>&, std::vector<double>&)>;

extern double w0_global;  // Pulsation propre pour deriv3

void deriv3(int n, double t, double y[], double dy[]);

void euler(int n, double t, double y[], double dt, 
           void deriv(int, double, double[], double[]));

void solve_q1();
void solve_q2();
void solve_q3();
void solve_q4();
void solve_q5();
void solve_q6();
void solve_q7();
void solve_q8();
void solve_q9();
void solve_q10();
void solve_q11();

#endif