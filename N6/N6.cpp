#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

int n = 1001;
double h = 1.0 / (n-1);
double hConst = h * h + 2;
double w = 0.49999974622;
double omega = 1.4668141587557216444478862823487451300526012325942420035388686470;
int max_itr = 10000000;
double epsilon = 1e-10;
bool precision;
double const0 = 1/hConst;

int Jacobi(double *x_jacobi, double *x_new_jacobi){
    int iteration_count = 0;

    // Jacobi
    do {
        precision = true;
        
        // przyblizona wartosc x_jacobi[0]
        x_new_jacobi[0] = const0 + const0 * x_jacobi[1];

        // przyblizona wartosc dla x_jacobi[1] -> x_jacobi[n-2]
        for(int i = 1; i < n-1; i++) {
            x_new_jacobi[i] = const0 * x_jacobi[i-1] + const0 * x_jacobi[i+1];
        }

        // przyblizona wartosc x_jacobi[n-1]
        x_new_jacobi[n-1] = const0 + const0 * x_jacobi[n-2];

        // x_jacobi_new_jacobi staje sie wskaznikiem na tablice 'starszych' przyblizen, a x_jacobi wskaznikiem na nowe przyblizenia
        double* temp;
        temp = x_jacobi;
        x_jacobi = x_new_jacobi;
        x_new_jacobi = temp;

        // sprawdzenie, czy pozadana dokladnosc zostala osiagnieta
        for(int i = 0; i < n; i++) {
            if(abs(x_new_jacobi[i] - x_jacobi[i]) > epsilon) {
                precision = false;
                break;
            }
        }

        iteration_count++;

    } while(precision != true && iteration_count < max_itr);
    return iteration_count;
}

int Gauss_Seidel(double* x){
    int iteration_count = 0;
    double temp;
    do {
        precision = true;
        
        // przyblizona wartosc x[0]
        temp = const0 + const0 * x[1];
        if(abs(temp - x[0]) > epsilon) {
            precision = false;
        }
        x[0] = temp;

        // przyblizona wartosc dla x[1] -> x[n-2]
        for(int i = 1; i < n-1; i++) {
            temp = const0 * x[i-1] + const0 * x[i+1];
            if(abs(temp - x[i]) > epsilon) {
                precision = false;
            }
            x[i] = temp;
        }

        // przyblizona wartosc x[n-1]
        temp = const0 + const0 * x[n-2];
        if(abs(temp - x[n-1]) > epsilon) {
            precision = false;
        }
        x[n-1] = temp;

        // limit iteracji
        iteration_count++;

    } while(precision != true && iteration_count < max_itr);
    return iteration_count;
}

int Relax(double* x, double* x_new){
    int iteration_count = 0;
    do {
        precision = true;
        
        // przyblizona wartosc x[0]
        x_new[0] = x[0] + w * (1 - hConst * x[0] + x[1]);

        // przyblizona wartosc dla x[1] -> x[n-2]
        for(int i = 1; i < n-1; i++) {
            x_new[i] = x[i] + w * (x[i-1] + x[i+1] - hConst * x[i]);
        }

        // przyblizona wartosc x[n-1]
        x_new[n-1] = x[n-1] + w * (1 - hConst * x[n-1] + x[n-2]);

        // x_new staje sie wskaznikiem na tablice 'starszych' przyblizen, a x wskaznikiem na nowe przyblizenia
        double* temp;
        temp = x;
        x = x_new;
        x_new = temp;

        // sprawdzenie dokladnosci
        for(int i = 0; i < n; i++) {
            if(abs(x_new[i] - x[i]) > epsilon) {
                precision = false;
                break;
            }
        }

        iteration_count++;

    } while(precision != true && iteration_count < max_itr);
    return iteration_count;
}

int SOR(double* x){
    int iteration_count = 0;
    double temp;
    do {
        precision = true;
        
        // przyblizona wartosc x[0]
        temp = (1 - omega) * x[0] + omega * (const0 + const0 * x[1]);
        if(abs(temp - x[0]) > epsilon) {
            precision = false;
        }
        x[0] = temp;

        // przyblizona wartosc dla x[1] -> x[n-2]
        for(int i = 1; i < n-1; i++) {
            temp = (1 - omega) * x[i] + omega * (const0 * x[i-1] + const0 * x[i+1]);
            if(abs(temp - x[i]) > epsilon) {
                precision = false;
            }
            x[i] = temp;
        }

        // przyblizona wartosc x[n-1]
        temp = (1 - omega) * x[n-1] + omega * (const0 + const0 * x[n-2]);
        if(abs(temp - x[n-1]) > epsilon) {
            precision = false;
        }
        x[n-1] = temp;

        // limit iteracji
        iteration_count++;

    } while(precision != true && iteration_count < max_itr);
    return iteration_count;
}

int main() {
    
    double* x_jacobi = new double[n] {};
    double* x_new_jacobi = new double[n];

    double* x_gauss = new double[n] {};

    double* x_relax = new double[n] {};
    double* x_new_relax = new double[n];

    double* x_sor = new double[n] {};

    auto start_jacobi = std::chrono::high_resolution_clock::now();
    int itr_jacobi = Jacobi(x_jacobi, x_new_jacobi);
    auto end_jacobi = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_jacobi = end_jacobi - start_jacobi;

    auto start_gauss = std::chrono::high_resolution_clock::now();
    int itr_gauss = Gauss_Seidel(x_gauss);
    auto end_gauss = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_gauss = end_gauss - start_gauss;

    auto start_relax = std::chrono::high_resolution_clock::now();
    int itr_relax = Relax(x_relax, x_new_relax);
    auto end_relax = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_relax = end_relax - start_relax;

    auto start_sor = std::chrono::high_resolution_clock::now();
    int itr_sor = SOR(x_sor);
    auto end_sor = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_sor = end_sor - start_sor;

    // wypisanie wynikow
    for(int i = 0; i < n; i++) {
        cout<<1-i*0.001<<", "<<x_jacobi[i] << ", " << x_gauss[i] << ", " << x_relax[i] << ", " << x_sor[i] <<endl;
    }

    
    cerr << "Liczba iteracji: \n1. Jacobi = " << itr_jacobi << "\n2. Gauss-Seidel = " << itr_gauss;
    cerr << "\n3. SOR = " << itr_sor << "\n4. Relaksacyjna = " << itr_relax << endl << endl;

    cerr << "Czas wykonania metod [s]: \n";
    cerr << "1. Jacobi = " << elapsed_jacobi.count() << "\n2. Gauss_Seidel = " << elapsed_gauss.count();
    cerr << "\n3. SOR = " << elapsed_sor.count() << "\n4. Relaksacyjna = " << elapsed_relax.count() << endl;

    delete[] x_jacobi;
    delete[] x_new_jacobi;
    delete[] x_gauss;
    delete[] x_relax;
    delete[] x_new_relax;
    delete[] x_sor;

    return 0;
}