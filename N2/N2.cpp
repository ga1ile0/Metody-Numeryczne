#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

#define X1 1
#define X2 3.14159265358979323846/2


double diffQuotientA(double x, double h){
    return (sin(x+h) - sin(x))/h;
}

double diffQuotientB(double x, double h){
    return (sin(x+h) - sin(x-h))/(2*h);
}

double diffQuotientC(double x, double h){
    return (-sin(x+2*h) + 8*sin(x+h) - 8*sin(x-h) + sin(x-2*h)) / (12*h);
}

double error(double diff, double x){
    return fabs(diff - cos(x));
}

auto main() -> int{

    ofstream myfile;
    myfile.open("data.dat");
    double A1, A2, B1, B2, C1, C2;
    double h = pow(10, -16);
    while(h <= 1.0){
        A1 = diffQuotientA(X1, h);
        B1 = diffQuotientB(X1, h);
        C1 = diffQuotientC(X1, h);

        A2 = diffQuotientA(X2, h);
        B2 = diffQuotientB(X2, h);
        C2 = diffQuotientC(X2, h);
        myfile << setprecision(16) << fixed;
        myfile << h << " ";
        myfile << error(A1, X1) << " ";
        myfile << error(B1, X1) << " ";
        myfile << error(C1, X1) << " ";
        myfile << error(A2, X2) << " ";
        myfile << error(B2, X2) << " ";
        myfile << error(C2, X2) << " ";
        myfile << endl;
        h *=1.001;
    }
}