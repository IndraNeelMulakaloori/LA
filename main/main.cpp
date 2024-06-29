#include <iostream>
#include <vector>

#include "lalib.h"

int main(){
    #ifndef DEBUG
        freopen("IO/input.txt", "r", stdin);
        freopen("IO/output.txt", "w", stdout);
    #endif
    
    int n,m;
    std::cin>>n>>m;

    VVF data(n,std::vector<double>(m,0));
    for(int i = 0 ; i < n ; i++){

            for(int j = 0 ;  j < m ;j++){
                std::cin>>data[i][j];
            }
    }
    // clock_t start, end;
    Matrix A;
    
    A.setData(data);
    A.info();

    Matrix A_t = A.transpose();
    A_t.info();

    
    Matrix mult = A.mat_mult(A_t);
    mult.info();

    // start = clock();
    std::pair<Matrix,Matrix> LU = A.L_U();
    // end = clock();

    LU.first.info();
    LU.second.info();

    // double cpu_time = (double) (end - start) / CLOCKS_PER_SEC * 1000;
    // std::cout<<"Performance time : "<<cpu_time<<"\n";
    return 0;
}