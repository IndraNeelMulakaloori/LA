#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <utility>

#define VVF std::vector<std::vector<double>>
#define IP std::pair<int,int>
class Matrix{

int __rows, __cols, __rank = -1, __nullity = -1;
std::string __type = "Normal";
VVF data;


public:
Matrix(){
    
}
Matrix(int rows, int cols);
Matrix(VVF data);
std::pair<IP,VVF> getData();
void setData(const VVF data);
void setDim(const int a, const int b);
void setType(std::string type);
IP getRank();
void info();
Matrix hstack(const Matrix A);
Matrix vstack(const Matrix A);
Matrix transpose();
Matrix arthimetic_operation(Matrix &B, char op);
Matrix scalar_operation(const double scalar, char op);
// Matrix operator-(Matrix &B);
Matrix mat_mult(Matrix B);
std::pair<Matrix,Matrix> L_U();
Matrix rref();
Matrix inverse();
Matrix A_b(Matrix b, const bool rref);

friend double sanitize(double value);
~ Matrix();

};
Matrix identity(const int &row,const int &col);
Matrix zero_ones(const int row,const int col, char dig);

#endif