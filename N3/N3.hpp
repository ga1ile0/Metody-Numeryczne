#ifndef N3_HPP
#define N3_HPP

#include <iostream>
#include <vector>

int N2 = 1000;

void thomas_algorithm(const std::vector<double>& a, //a,b,c - represent elements int the dridiagonal bands
                      const std::vector<double>& b, // represents diagonal elements so its one element longer than a and c
                      const std::vector<double>& c,
                      const std::vector<double>& d, // d - the right-hand column vector
                      std::vector<double>& f){ //f - solution vector

    int N = d.size();
    std::vector<double> c_prime(N, 0.0);
    std::vector<double> d_prime(N, 0.0);

    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for(int i = 1; i < N ; i++){
        double m = 1.0 / (b[i] - a[i] * c_prime[i-1]);
        c_prime[i] = c[i] * m;
        d_prime[i] = (d[i] - a[i] * d_prime[i-1]) * m;
    }

    for(int i = N - 1; i-- > 0; ){
        f[i] = d_prime[i] - c_prime[i] * d[i+1];
    }
}

double f(int k){
    return 1.0 / (1.0 + 25.0 * (-1 + k * (2.0 / N2)) * (-1 + k * (2.0 / N2)));
}

void fill_d(std::vector<double>& d){
    double coef = 3*N2*N2; // 6/h^2
    for(int i = 0; i < N2-3; i++){
        d[i] = coef*(f(i) - 2*f(i+1) + f(i+2));
    }
}

#endif
