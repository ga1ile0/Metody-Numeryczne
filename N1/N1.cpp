#include <iostream>
#include <cmath>
#include <iomanip>

double pts; // licznik obliczeń

using namespace std;

double f(int lim, double x){
    double sin_, cos_, sinus, cosinus, x_4;
    double result = 0; pts += 0.5;
    double expon = (1.0 / 2.71828182845904523536); pts += 1.5;
    x_4 = x*x*x*x; pts += 4.5;
    result += 1; pts += 1;// dodanie dla n=0
    double sin1 = sin(x_4); pts += 30.5;
    double cos1 = cos(x_4); pts += 30.5;
    result += (sin1*sin1*expon) + (cos1 * expon * expon * expon * expon); pts += 7.5; //dodanie dla n=1
    sin_ = sin1; pts += 0.5;
    cos_ = cos1; pts += 0.5;
    for(int n = 2; n < lim ; ++n){
        sinus = (sin_ * cos1) + (sin1 * cos_); pts += (2.5 + 3.5); //ze wzoru na sinus sumy/roznicy
        cosinus = (cos_ * cos1) - (sin_ * sin1); pts += 3.5; //ze wzoru na cosinus sumy/roznicy
        expon = expon / 2.71828182845904523536; pts += 1.5;
        result += (sinus * sinus * expon) + (cosinus * expon * expon * expon * expon); pts += 8;
        sin_ = sinus;
        cos_ = cosinus; pts += 1;
    }
    return result;

}

auto main() -> int{
    double x = 1; pts += 0.5;
    int N = 20; pts += 0.5;
    cout << setprecision(10) << f(N, x) << endl;

}