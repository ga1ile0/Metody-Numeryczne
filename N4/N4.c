#include <stdio.h>
#include <stdlib.h>

int N = 1000;
double h = 0.002;

void thomas_algorithm(double a[], double b[], double c[], double d[], double f[]){
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
}


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
 
    thomas_algorithm(a,b,c,d,y);

    thomas_algorithm(a,b,c,u,q);
    
    double vTq = 0.0;
    double vTy = 0.0;

    //liczymy v^Ty
    for(int i = 0; i < N; i++){
        vTy += v[i]*y[i];
    }
    //liczymy v^Tq
    for(int i=0; i < N; i++){
        vTq += v[i]*q[i];
    }

    //szukany wektor
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