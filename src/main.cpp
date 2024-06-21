#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
// using namespace std;

class Matrix{

int __rows, __cols;
std::vector<std::vector<int>> data;

public:
Matrix(){
    
}
// Matrix(int rows, int cols){
//     __rows = rows;
//     __cols = cols;
// }
void readData(std::vector<std::vector<int>> data);
void info();
Matrix transpose();
};

int main(){
    Matrix A;
    A.readData({{1,2,3},{4,5,6}});
    A.info();
    Matrix A_t = A.transpose();
    A_t.info();
    return 0;
}

void Matrix::readData(std::vector<std::vector<int>> data){
               std::copy(data.begin(),data.end(),std::back_inserter(this->data));
               __rows = this->data.size();
               __cols = this->data[0].size();
}

void Matrix::info(){
    std::cout<<"Matrix \n";
    for(int i = 0 ; i < __rows ; i++){
        for(int j =0 ; j < __cols ; j++){
            std::cout<<this->data[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Rows : "<<__rows<<"\n";
    std::cout<<"Cols : "<<__cols<<"\n";

    
}

Matrix Matrix::transpose(){
    //For Square Matrices
    Matrix A_transpose;
    A_transpose.__cols = __rows;
    A_transpose.__rows = __cols;
    A_transpose.data.resize(A_transpose.__rows,std::vector<int>(A_transpose.__cols));
    for(int i = 0 ; i < __cols ; i++){
        for(int j = 0 ; j < __rows ; j++){
           A_transpose.data[i][j] = this->data[j][i];
           A_transpose.data[j][i] = this->data[i][j];
        }
    }
    return A_transpose;
}