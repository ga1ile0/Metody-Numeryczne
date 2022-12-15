#include <stdio.h>
#include <stdlib.h>


void thomas_algorithm(double *a, double *b, double *c, double *d, int N){

    c[0] = c[0] / b[0];
    d[0] = d[0] / b[0];

    for(int i = 1; i < N; i++){
        double m = 1.0 / (b[i] - (a[i] * c[i-1]));
        c[i] = c[i] * m;
        d[i] = (d[i] - (a[i] * d[i-1])) * m;
    }

    for(int i = N - 1; i > 0; i--){
        d[i] = d[i] - (c[i] * d[i+1]);
    }
    d[0] = d[0] - (c[0] * d[1]);
}

int main(){
    int N = 1001;
    double h = 0.001; // 1.0/(N-1)
    const double val = 2.0 + h*h;

    double a[N]; //przekątna pod diagonalą
    double b[N]; //diagonala
    double c[N-1]; //przekątna nad diagonalą
    double d[N]; //wektor prawostronny

    for(int i = 0; i <= N - 2; i++){
        a[i] = -1.0;
        b[i] = val;
        c[i] =-1.0;
        d[i] = 0.0;
    }

    //uwzględnie równań 2 i 3
    a[N-1] = 0.0;
    c[0] = 0.0;
    b[N-1] = 1.0;
    b[0] = 1.0;
    d[N-1] = 1.0;
    d[0] = 1.0;

    thomas_algorithm(a,b,c,d,N);


    //Podpunkt b)

    double u[N];
    u[0] = 1.0;
    u[1] = 2.0 / (2.0 - h*h); //wyliczone z 1 i 3 równania

    for(int i = 2; i <= N - 1; i++){
        u[i] = (h*h + 2.0)*u[i-1] - u[i-2]; // 1 równanie
    }
    u[N-1] = 1.0;

    
    for(int i = 0; i <= N - 1; i++){
        double xn = i*h; //zaczynamy od i = 0, dlatego jest i*h a nie (i-1)*h
        printf("%.16f, %.16f, %.16f\n", xn, d[i], u[i]);
    }
}