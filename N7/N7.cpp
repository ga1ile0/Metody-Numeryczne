#include <iostream>
#include <vector>
#include <fstream>

double dotProduct(std::vector<double> a, std::vector<double> b, int size){
    double sum = 0.0;
    for(int i = 0; i < size; ++i){
        sum += (a[i] * b[i]);
    }

    return sum;
}

std::vector<double> addVectors(std::vector<double> a, std::vector<double> b, int size){
    std::vector<double> dest(size);
    for(int i = 0; i < size; ++i){
        dest[i] = a[i] + b[i];
    }
    return dest;
}

std::vector<double> subVectors(std::vector<double> a, std::vector<double> b, int size){
    std::vector<double> dest(size);
    for(int i = 0; i < size; ++i){
        dest[i] = a[i] - b[i];
    }
    return dest;
}

std::vector<double> scalarMulti(std::vector<double> vec, double s, int size){
    std::vector<double> dest(size);
    for(int i = 0; i < size; ++i){
        dest[i] = s * vec[i];
    }
    return dest;
}

std::vector<double> crossProduct(std::vector<std::vector<double>> A, std::vector<double> vec, int size){
    std::vector<double> dest(size);
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; j++){
            dest[i] += A[i][j] * vec[j];
        }
    }
    return dest;
}

int main(){
    int i, j, k = 0, max_itr = 1000;
    double tolerance = 0.000001;
    const int N = 1001;
    const double h = 0.001;
    const double val = 2.0 + h*h;
    
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<double> B(N);

    for(i = 0; i < N ; i++){
        B[i] = 0.0;
    }

    B[N-1] = 1.0;
    B[0] = 1.0;
  
    for( i = 0; i < N; ++i){
        for( j = 0; j < N; ++j){
            if(i == j){
                A[i][j] = val;
            }
            else if(i == (j - 1)){
                A[i][j] = -1.0;
            }
            else if(i == (j + 1)){
                A[i][j] = -1.0;
            }
            else{
                A[i][j] = 0.0;
            }
        }
    }
    /*
    //pod diagonalą:
    A[N-1][N-2] = 0.0;
    //diagonala:
    A[1][1] = 1.0;
    A[N-1][N-1] = 1.0;
    //nad diagonalą:
    A[0][1] = 0.0;

    */
    double alpha;
    double beta;
    std::vector<double> x(N);
    std::vector<double> s(N);
    std::vector<double> x_prev(N);
    std::vector<double> p(N);
    std::vector<double> p_prev(N);
    std::vector<double> r(N);
    std::vector<double> r_prev(N);
    std::vector<double> r_prev_prev(N);
    std::vector<double> temp_vec(N);

    for(int i = 0; i < N; i++){
        x[i] = 0.0;
        r[i] = B[i];
        r_prev[i] = B[i];
        r_prev_prev[i] = B[i];
    }

    while((k < max_itr) && (dotProduct(r, r, N) > tolerance)){
        //std::cout << "DotProduct: " << dotProduct(r, r, N) << std::endl;
        r_prev_prev = r_prev;
        r_prev = r;
        p_prev = p;
        x_prev = x;
        k++;
        if(k == 1){
            p = r_prev;
            p_prev = p;
        } else{
            beta = dotProduct(r_prev, r_prev, N) / dotProduct(r_prev_prev, r_prev_prev, N);
            temp_vec = scalarMulti(p_prev, beta, N);
            p = addVectors(r, temp_vec, N);
        }

        s = crossProduct(A, p, N);
        alpha = dotProduct(r_prev, r_prev, N) / dotProduct(p, s, N);

        temp_vec = scalarMulti(p, alpha, N);
        x = addVectors(x_prev, temp_vec, N);

        temp_vec = scalarMulti(s, alpha, N);
        r = subVectors(r_prev, temp_vec, N);
    }
    /*
    for(i = 0; i < N; i++){
        std::cout << x[i] << std::endl;
    }
    */
    std::cout << "Liczba iteracji: " << k << std::endl;

    std::ofstream myfile;
    myfile.open("data.txt");
    for(int i = 0; i < N; i++){
        double xn = i * h;
        myfile << xn << " " << x[i] << std::endl;
    }
}