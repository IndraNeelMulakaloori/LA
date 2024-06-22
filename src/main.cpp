#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<filesystem>
#include<utility>
#include<stdexcept>
#include<string>
// using namespace std;

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
};
Matrix identity(const int &row,const int &col);
int main(){
    // #ifndef DEBUG
    //     freopen("IO/input.txt", "r", stdin);
        freopen("IO/output.txt", "w", stdout);
    // #endif
    
    // int n,m;
    // std::cin>>n>>m;

    // std::cout<<n<<m;

    // VVF data(n,std::vector<double>(m,0));
    // for(int i = 0 ; i < n ; i++){

    //         for(int j = 0 ;  j < m ;j++){
    //             std::cin>>data[i][j];
    //         }
    // }
    
    Matrix A;
    A.setData({{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}});
    A.info();
    Matrix A_t = A.transpose();
    A_t.info();
    Matrix mult = A.mat_mult(Matrix({{-1.1,2,-3.4},{3,4,5},{7,8,9}}));
    mult.info();
    std::pair<Matrix,Matrix> LU = A.L_U();
    LU.first.info();
    LU.second.info();
    
    return 0;
}

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
void Matrix::setData(VVF data){
    std::copy(data.begin(),data.end(),std::back_inserter(this->data));
               __rows = this->data.size();
               __cols = this->data[0].size();

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
                    L.data[curr_row][prev_row] = U.data[curr_row][prev_row]/U.data[prev_row][prev_row];
                    for(int curr_col = prev_row; curr_col < cols ; curr_col++){
                        U.data[curr_row][curr_col] = U.data[curr_row][curr_col] - (L.data[curr_row][prev_row] * U.data[prev_row][curr_col]);
                    }
        }
    }

    return {L,U};

}