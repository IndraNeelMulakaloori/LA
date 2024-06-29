
#include "lalib.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>


// Constructors, Getters and Setters
Matrix::Matrix(int rows, int cols){
    __rows = rows;
    __cols = cols;
    this->data.resize(__rows,std::vector<double>(__cols));
   

}

Matrix::Matrix(VVF data){
               this->setData(data);
}

std::pair<std::pair<int,int>,VVF> Matrix::getData(){
    return {{this->__rows,this->__cols},this->data};
}
void Matrix::setData(const VVF data){
    this->data = data;
    this->setDim(this->data.size(), this->data[0].size()) ;
}
void Matrix::setDim(const int row, const int col){
                __rows = row;
                __cols = col;
}
void Matrix::setType(std::string type){
    __type = type;
}

//Info Regarding the Matrix
void Matrix::info(){
    std::cout<<this->__type<<"  Matrix   \n";
    for(int i = 0 ; i < __rows ; i++){
        for(int j =0 ; j < __cols ; j++){
            std::cout<<this->data[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Rows : "<<__rows<<"\n";
    std::cout<<"Cols : "<<__cols<<"\n";

    
}
void Matrix::vstack(const VVF data){
    if(__cols != (int) data[0].size())
        throw invalid_argument("Matrices must have the same number of columns for horizontal stacking.");
    std::copy(data.begin(),data.end(),std::back_inserter(this->data));
    this->setDim(this->data.size(), this->data[0].size());
    this->setType("Vertical Stacked");
}
void Matrix::hstack(const VVF data){
    if (__rows != (int) data[0].size()) {
        throw invalid_argument("Matrices must have the same number of rows for horizontal stacking.");
    }

    for(size_t i = 0 ; i < data.size() ; i++)
    this->data[i].insert(this->data[i].end(), data[i].begin(),data[i].end());

    this->setDim(this->data.size(), this->data[0].size());
    this->setType("Horizontal Stacked");

}
Matrix Matrix::transpose(){
    //For Square Matrices
    Matrix A_transpose(__cols,__rows);
    for(int i = 0 ; i < __cols ; i++){
        for(int j = 0 ; j < __rows ; j++){
           A_transpose.data[i][j] = this->data[j][i];
        //    A_transpose.data[j][i] = this->data[i][j];
        }
    }
    A_transpose.setType("Transposed");
    return A_transpose;
}

// Matrix Multiplication 
// Dot Product of rows and columns
// Args : Requires one Matrix
// Returns : Muliplication Matrix
Matrix Matrix::mat_mult(Matrix B){
    Matrix result(this->getData().first.first,B.getData().first.second);
    try{
        //if A.cols != B.rows 
         if ((*this).getData().first.second != B.getData().first.second)
        throw "Matrix dimensions doesn't fit in matrix Multiplication \n A.cols != B.rows" ;

    else{
         for(int row = 0 ; row < this->getData().first.first ; row++){
        for(int col =  0 ; col < B.getData().first.second ; col++){
            for(int op = 0 ; op < B.getData().first.second ; op++){
                result.data[row][col] += this->data[row][op] * B.data[op][col];
            }
        }
    }
    }
    }
    catch(const std::string error ){
        std::cout<<error<<"\n";
    }
        result.setType("Dot Product");
    return result;
   

}
Matrix identity(const int &row, const int &col){

VVF IdenMat(row,std::vector<double>(col));
for(int diagonal = 0 ;  diagonal < std::min(row,col) ; diagonal++)
    IdenMat[diagonal][diagonal]  = 1.0;

Matrix I(IdenMat);
I.setType("Identity");
return I;

}

// LU Decompostion
// Breaks a matrix into Upper triangular and Lower Triangular Matrix
// Args : 
// Returns : Pair of LU Matrices

std::pair<Matrix,Matrix> Matrix::L_U(){

    //Without Permutation

    
    
    int rows = this->getData().first.first, cols = this->getData().first.second;
    Matrix L(identity(rows,cols).data),U(this->data);
    L.setType("Lower Triangular");
    U.setType("Upper Triangular");
    
    for(int prev_row = 0 ; prev_row < rows ; prev_row++){
        for(int curr_row = prev_row + 1 ; curr_row < rows ; curr_row++){
            //         if (this->getData().second[prev_row][prev_row] == 0.0) {
            //     std::cerr << "LU decomposition failed: Zero pivot encountered." << "\n";
            //     return {{}, {}};
            // }
                    L.data[curr_row][prev_row] = U.data[curr_row][prev_row]/U.data[prev_row][prev_row];
                    for(int curr_col = prev_row; curr_col < cols ; curr_col++){
                        U.data[curr_row][curr_col] = U.data[curr_row][curr_col] - (L.data[curr_row][prev_row] * U.data[prev_row][curr_col]);
                    }
        }
    }

    return {L,U};

}
Matrix Matrix::rref(){
          std::pair<Matrix, Matrix> row_reduction = this->L_U();

          int __r = row_reduction.second.getData().first.first;
          int __c = row_reduction.second.getData().first.second;
          VVF data = row_reduction.second.getData().second;

          for(int diag = std::min(__r,__c) - 1 ; diag > 0 ; diag--){
            if(data[diag][diag] != 0){
                for(int col = diag + 1 ; __c < col ; col++){
                    data[diag][col] /= data[diag][diag];
                }
                data[diag][diag] = 1.0;

                for(int row = diag - 1 ; row >= 0 ; row--){
                    double factor = data[row][diag];
                    data[row][diag] -=  (factor * data[diag][diag]);
                }
            }
          }

          Matrix rr = Matrix(data);
          rr.setType("Reduced Row Echleon");

    
    return rr;

}
Matrix::~Matrix(){
    
}