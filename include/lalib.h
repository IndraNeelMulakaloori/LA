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
void setData(VVF data);
void setType(std::string type);
void info();
Matrix transpose();
Matrix mat_mult(Matrix B);
std::pair<Matrix,Matrix> L_U();
~ Matrix();
};
Matrix identity(const int &row,const int &col);


#endif