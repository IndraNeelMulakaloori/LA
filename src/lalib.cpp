
#include "lalib.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cmath>

double sanitize(double value) {
    if (std::isnan(value)) {
        return 0.0;
    }
    if (value == -0.0) {
        return 0.0;
    }
    return value;
}

// Constructors, Getters and Setters
Matrix::Matrix(int rows, int cols){
    __rows = rows;
    __cols = cols;
    __rank = rows;
    __nullity = 0;
    this->data.resize(__rows,std::vector<double>(__cols));
   

}

Matrix::Matrix(VVF data){
               this->setData(data);
}

std::pair<IP,VVF> Matrix::getData(){
    return {{this->__rows,this->__cols},this->data};
}
void Matrix::setData(const VVF data){
    this->data = data;
    this->setDim(this->data.size(), this->data[0].size()) ;
}
void Matrix::setDim(const int row, const int col){
                __rows = row;
                __cols = col;
                __rank = __rows;
                __nullity = 0;
}
void Matrix::setType(std::string type){
    __type = type;
}
IP Matrix::getRank(){

        VVF reduced_row_data = this->rref().data;
        int rows = this->__rows , cols = this->__cols;

        std::vector<double> zero_row(cols,0.0);
        this->__rank = rows , this->__nullity = 0;

        for(int row = 0 ; row < rows ; row++)
            if (reduced_row_data[row] == zero_row){
                this->__rank = row ;
                this->__nullity = rows - this->__rank;
                break;
            }

    return {this->__rank,this ->__nullity};

}
//Info Regarding the Matrix
void Matrix::info(){
    std::cout<<this->__type<<"  Matrix   \n";
    for(int i = 0 ; i < __rows ; i++){
        for(int j =0 ; j < __cols ; j++){
            std::cout<<this->data[i][j]<<"   ";
        }
        std::cout<<"\n";
    }
    std::cout<<"Rows : "<<__rows<<"\n";
    std::cout<<"Cols : "<<__cols<<"\n";

    IP rank = getRank();

    std::cout<<"Rank : "<<rank.first<<"\n";
    std::cout<<"Nullity: "<<rank.second<<"\n";



    
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
// Matrix Arthimetic Operation
// Use +, - or * to perform arthimetic operations on Matrices;
Matrix Matrix::arthimetic_operation(Matrix &B, char op){
    if(this->getData().first != B.getData().first)
    throw std::invalid_argument ("shape aren't sufficent for operation " + op);

    auto __shape = this->getData().first;
    Matrix result(__shape.first,__shape.second);

    for(int row = 0 ; row < __shape.first ; row++){
        for(int col = 0 ; col < __shape.second ; col++){
            // result.data[row][col] = this->data[row][col] + B.data[row][col];
            switch (op){
                case '+':
                    result.data[row][col] = this->data[row][col] + B.data[row][col];
                    break;
                case '-':
                    result.data[row][col] = this->data[row][col] - B.data[row][col];
                    break;
                case '*':
                    result.data[row][col] = this->data[row][col] * B.data[row][col];
                    break;
                default:
                    std::cout<<"Invalid arthimetic operation use +, - or * \n";
                    exit(1);
            }

        }
    }
    return result;

}
// Scalar Operation
// Use * or / for scalar operations on Matrices;
Matrix Matrix::scalar_operation(const double scalar , char op){

        auto __shape = this->getData().first;
        Matrix result(__shape.first,__shape.second);

         for(int row = 0 ; row < __shape.first ; row++){
        for(int col = 0 ; col < __shape.second ; col++){
            // result.data[row][col] = this->data[row][col] + B.data[row][col];
            switch (op){
                case '*':
                    result.data[row][col] = this->data[row][col] * scalar;
                    break;
                case '/':
                if (scalar == 0) {
                        throw std::invalid_argument("Division by zero error.");
                    }
                    result.data[row][col] = this->data[row][col] / scalar;
                    break;
                default:
                    std::cout<<"Invalid arthimetic operation use * or / \n";
                    exit(1);
            }

        }
    }
return result;

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
        throw "Matrix shape doesn't fit in matrix Multiplication \n A.cols != B.rows" ;

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

Matrix I = zero_ones(row,col,'0');
VVF IdenMat = I.getData().second;
for(int diagonal = 0 ;  diagonal < std::min(row,col) ; diagonal++)
    IdenMat[diagonal][diagonal]  = 1.0;

I.setData(IdenMat);
I.setType("Identity");
return I;

}
// Zero/One MAtrix
// Creates complete zero matrix else one matrix
Matrix zero_ones(const int row,const int col, char dig){
    VVF result(row,std::vector<double>(col,(dig == '0' ? 0.0 : 1.0)));
    Matrix A(result);
    A.setType("Zero/One");
    return A;
    
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
            for (auto& row : data) {
        for (auto& element : row) {
            element = sanitize(element);
        }
    }
    return {L,U};

}

Matrix Matrix::vstack(Matrix B){
    if(__cols != B.getData().first.second){
        throw std::invalid_argument("Matrices must have the same number of columns for vertical stacking.");
    }

    VVF data_1 = this->getData().second;
    VVF data_2 = B.getData().second;

    std::copy(data_2.begin(),data_2.end(),std::back_inserter(data_1));
    
    Matrix result(data_1);
    result.setType("Vertical Stacked");

    return result;
}
/// Change Hstack to retun Matrix
Matrix Matrix::hstack(Matrix B){
    if (__rows != B.getData().first.first) {
        throw std::invalid_argument("Matrices must have the same number of rows for horizontal stacking.");
    }

    VVF data_1 = this->getData().second;
    VVF data_2 = B.getData().second;

    for(size_t i = 0 ; i < data.size() ; i++)
    data_1[i].insert(data_1[i].end(), data_2[i].begin(),data_2[i].end());

    Matrix result(data_1);
    result.setType("Horizonatal stacked");

    return result;
    

}

// Reduced Row Echeleon form:
// Returns a Matrix
// computes the row reduced form of a Matrix
Matrix Matrix::rref(){
          std::pair<Matrix, Matrix> row_reduction = this->L_U();

          int __r = row_reduction.second.getData().first.first;
          int __c = row_reduction.second.getData().first.second;
          VVF data = row_reduction.second.getData().second;


          // Min of row, col for a diagonal
          for(int diag = std::min(__r,__c) - 1 ; diag >= 0 ; diag--){
            // non-zero row reduction
            if(data[diag][diag] != 0){
                // factor out rows
                for(int col = diag + 1 ; col < __c  ; col++){
                    data[diag][col] /= data[diag][diag];
                }
                data[diag][diag] = 1.0;

                // Perform row operations above the diagonal
                for(int row = diag - 1 ; row >= 0 ; row--){
                    double factor = data[row][diag];

                    for(int col = diag ; col < __c ; col++){
                        data[row][col] = data[row][col] -  (factor * data[diag][col]);
                    }
                        
                }
            }
          }
            for (auto& row : data) {
                for (auto& element : row) {
                  element = sanitize(element);
                      }
                }



            Matrix rr = Matrix(data);
            rr.setType("Reduced Row Echleon");

    return rr;

}
Matrix Matrix::inverse(){
    IP __shape = this->getData().first;

    this->hstack(identity(__shape.first,__shape.second));

    VVF row_reduction_data = this->rref().getData().second;
    __shape = this->getData().first;
    VVF inverse_data(__shape.first,std::vector<double>(__shape.second/2));

    
    for(int row = 0 ; row < __shape.first ; row++)
        std::copy(row_reduction_data[row].begin() + __shape.second/2, row_reduction_data[row].end(), inverse_data[row].begin());
    
    // Create the inverse matrix object
    Matrix inverse_matrix(inverse_data);
    inverse_matrix.setType("Inverse");  // Set the type here

    return inverse_matrix;
}
Matrix Matrix::A_b(Matrix b, const bool rref){

    
    Matrix soln = this->hstack(b);
    soln.setType("Solution");
    if(rref){
        soln = soln.rref();
    }  else{

        soln = soln.L_U().second;
    }
    return soln;

}

Matrix::~Matrix(){
    
}

