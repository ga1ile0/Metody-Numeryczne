#include <iostream>
#include <vector>
#include <cmath>
#include "N3.hpp"

int main(){

    double diagonal_value = 4.0;
    double off_diagonal_value = 1.0;
    std::vector<double> a(N2 - 1, off_diagonal_value); //przekątna pod diagonalą
    std::vector<double> b(N2, diagonal_value); //diagonala
    std::vector<double> c(N2-1, off_diagonal_value); //przekątna nad diagonalą
    std::vector<double> d; fill_d(d);
    std::vector<double> f;
    thomas_algorithm(a, b, c, d, f);

    for(auto & i : f){
        std::cout << i << std::endl;
    }
   
}
