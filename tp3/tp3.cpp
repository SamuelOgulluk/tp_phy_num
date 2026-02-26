#include <iostream>
#include "tp3.hpp"

// Définitions des variables globales
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

int main(int argc, char* argv[]) {
std::cout << "Lancement des simulations" << std::endl;
    exercice_q1_q3();
    exercice_q6_q8();
    exercice_q10_q11();

    std::cout << "Terminé" << std::endl;
    return 0;
}

    