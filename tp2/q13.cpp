#include "tp2.hpp"
#include <vector>

void solve_q13() {
    g_non_lineaire = false;
    g_Fe = 0.0;
    double q_vals[] = {1.0, 2.0, 5.0};
    double t_max = 20.0;
    double dt = 0.05;
    
    std::vector<double> t_vec, th1, th2, th3;
    std::vector<double>* theta_vecs[] = {&th1, &th2, &th3};

    for(int i = 0; i < 3; ++i) { // on itère sur q
        g_q = q_vals[i];
        double y[2] = {10.0 * M_PI / 180.0, 0.0};
        
        for(double t = 0.0; t <= t_max; t += dt) { // on itèse sur le temps
            if(i == 0) t_vec.push_back(t);
            theta_vecs[i]->push_back(y[0]);
            rk4(2, t, y, dt, deriv);
        }
    }
    save_csv("resultats/q13_data.csv", {"t", "th_pseudo", "th_crit", "th_aper"}, 
            {t_vec, th1, th2, th3});
}