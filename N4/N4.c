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
    double u[N];
    double v[N];

    double y[N];
    double q[N];
    int gamma = 1;

    for(int i = 0; i < N; i++){
        a[i] = 1.0;
        b[i] = 4.0;
        c[i] = 1.0;
        d[i] = 0.0;
        f[i] = 0.0;
        u[i] = 0.0;
        v[i] = 0.0;
        y[i] = 0.0;
        q[i] = 0.0;
    }

    b[0] = 4.0 - gamma; //b1  - gamma
    b[N] = 4.0 - 1.0 / gamma; //bn - (cn * a1)/gamma

    u[0] = gamma;
    v[0] = 1;
    v[N] = 1.0 / gamma;

    double coeff = 3*N*N; // 6/h^2
    for(int i = 0; i < N-3; i++){
        d[i] = coeff*(fun(i) - 2*fun(i+1) + fun(i+2));
    }

    double c_prime1[N];
    double d_prime1[N];
    double c_prime2[N];
    double d_prime2[N];    
    

    for(int i = 0; i < N; i++){
        c_prime1[i] = 0.0;
        d_prime1[i] = 0.0;
        c_prime2[i] = 0.0;
        d_prime2[i] = 0.0;
    }

    c_prime1[0] = c[0] / b[0];
    d_prime1[0] = d[0] / b[0];
    c_prime2[0] = c[0] / b[0];
    d_prime2[0] = d[0] / b[0];

    //Thomas algorithm for By=d

    for(int i = 0; i < N; i++){
        double m = 1.0 / (b[i] - (a[i] * c_prime1[i-1]));
        c_prime1[i] = c[i] * m;
        d_prime1[i] = (d[i] - (a[i] * d_prime1[i-1])) * m;
    }
    y[N] = d_prime1[N];
    for(int i = N - 1; i > 0; i--){
        y[i] = d_prime1[i] - (c_prime1[i] * y[i+1]);
    }

    //Thomas algorithm for Bq=u
    for(int i = 0; i < N; i++){
        double m = 1.0 / (b[i] - (a[i] * c_prime2[i-1]));
        c_prime2[i] = c[i] * m;
        d_prime2[i] = (d[i] - (a[i] * d_prime2[i-1])) * m;
    }
    q[N] = d_prime2[N];
    for(int i = N - 1; i > 0; i--){
        q[i] = d_prime2[i] - (c_prime2[i] * q[i+1]);
    }
    double vTq = 0.0;
    double vTy = 0.0;

    //liczymy v^ty
    for(int i = 0; i < N; i++){
        vTy += v[i]*y[i];
    }
    //liczymy v^Tq
    for(int i=0; i < N; i++){
        vTq += v[i]*q[i];
    }

    for(int i = 0; i < N; i++){
        f[i] = y[i] - ((q[i]*vTy) / (1 + vTq));
    }
    

    FILE *fptr;
    fptr = fopen("data2.txt", "w");
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