// tp4.cpp
#include "tp4.hpp"

void solve(MatrixXd &z, VectorXd &d, MatrixXd &v){
    SelfAdjointEigenSolver<MatrixXd> eigensolver(z);
    if (eigensolver.info() != Success){
        cout << "ERROR in SelfAdjointEigenSolver" << endl;
        abort();
    }
    d = eigensolver.eigenvalues();
    v = eigensolver.eigenvectors();
}

int main() {
    std::cout << "Lancement des simulations" << std::endl;
    solve_q1_q2_potentiels();
    solve_q6_puits();
    solve_q9_harmonique();
    solve_q12_double_puits();

    std::cout << "Terminé" << std::endl;
    return 0;
}
