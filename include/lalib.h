#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <utility>
using namespace std;

#define VVF std::vector<std::vector<double>>
class Matrix{

int __rows, __cols;
std::string __type = "Normal";
VVF data;

public:
Matrix(){
    
}
Matrix(int rows, int cols);
Matrix(VVF data);
std::pair<std::pair<int,int>,VVF> getData();
void setData(const VVF data);
void setDim(const int a, const int b);
void setType(std::string type);
void info();
void hstack(const Matrix A);
void vstack(const Matrix A);
Matrix transpose();
Matrix arthimetic_operation(Matrix &B, char op);
Matrix scalar_operation(const double scalar, char op);
// Matrix operator-(Matrix &B);
Matrix mat_mult(Matrix B);
std::pair<Matrix,Matrix> L_U();
Matrix rref();
~ Matrix();
};
Matrix identity(const int &row,const int &col);
Matrix zero_ones(const int row,const int col, char dig);


#endif