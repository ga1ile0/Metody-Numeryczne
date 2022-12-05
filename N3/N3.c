#include <stdio.h>
#include <stdlib.h>

int N = 1000;
double h = 0.002;

double fun(int k){
    double x = -1.0 + k*h;
    return 1.0 / (1.0 + 25.0*x*x);
}

int main(){

    double a[N]; //przekątna pod diagonalą
    double b[N]; //diagonala
    double c[N]; //przekątna nad diagonalą
    double d[N]; //wektor prawostronny
    double f[N]; //wektor szukany

    for(int i = 0; i < N; i++){
        a[i] = 1.0;
        b[i] = 4.0;
        c[i] = 1.0;
        d[i] = 0.0;
        f[i] = 0.0;
    }

    double coeff = 3*N*N; // 6/h^2
    for(int i = 0; i < N-3; i++){
        d[i] = coeff*(fun(i) - 2*fun(i+1) + fun(i+2));
    }


    double c_prime[N];
    double d_prime[N];

    for(int i = 0; i < N; i++){
        c_prime[i] = 0.0;
        d_prime[i] = 0.0;
    }

    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for(int i = 0; i < N; i++){
        double m = 1.0 / (b[i] - (a[i] * c_prime[i-1]));
        c_prime[i] = c[i] * m;
        d_prime[i] = (d[i] - (a[i] * d_prime[i-1])) * m;
    }
    f[N] = d_prime[N];
    for(int i = N - 1; i > 0; i--){
        f[i] = d_prime[i] - (c_prime[i] * f[i+1]);
    }

    FILE *fptr;
    fptr = fopen("data.txt", "w");
    if(fptr == NULL){
        printf("File error!\n");
        return -1;
    }
    char s = ' ';
    for(int i = 0; i < N; i++){
        double xk = 0.0;
        xk = (-1.0) + i*(2.0/N);
        fprintf(fptr, "%f", xk);
        fprintf(fptr, "%c", s);
        fprintf(fptr, "%f\n", f[i]);


    }


}