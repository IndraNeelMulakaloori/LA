#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<filesystem>
#include<utility>
#include<stdexcept>
// using namespace std;

class Matrix{

int __rows, __cols;
std::vector<std::vector<int>> data;

public:
Matrix(){
    
}
Matrix(int rows, int cols);
Matrix(std::vector<std::vector<int>> data);
std::pair<std::pair<int,int>,std::vector<std::vector<int>>> getData();
void info();
Matrix transpose();
Matrix mat_mult(Matrix B);
void L_U();
};
Matrix identity(const int &row,const int &col);
int main(){
    #ifndef DEBUG
        freopen("IO/input.txt", "r", stdin);
        freopen("IO/output.txt", "w", stdout);
    #endif
    
    int n,m;
    std::cin>>n>>m;

    std::cout<<n<<m;

    std::vector<std::vector<int>> data(n,std::vector<int>(m,0));
    for(int i = 0 ; i < n ; i++){

            for(int j = 0 ;  j < m ;j++){
                std::cin>>data[i][j];
            }
    }
    
    Matrix A(data);
    A.info();
    Matrix A_t = A.transpose();
    A_t.info();
    // Matrix mult = A.mat_mult(Matrix({{1,2},{3,4}}));
    // mult.info();
    // A.L_U();
    return 0;
}


Matrix::Matrix(int rows, int cols){
    __rows = rows;
    __cols = cols;
    this->data.resize(__rows,std::vector<int>(__cols));
}

Matrix::Matrix(std::vector<std::vector<int>> data){
               std::copy(data.begin(),data.end(),std::back_inserter(this->data));
               __rows = this->data.size();
               __cols = this->data[0].size();
}

std::pair<std::pair<int,int>,std::vector<std::vector<int>>> Matrix::getData(){
    return {{this->__rows,this->__cols},this->data};
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
    Matrix A_transpose(__cols,__rows);
    for(int i = 0 ; i < __cols ; i++){
        for(int j = 0 ; j < __rows ; j++){
           A_transpose.data[i][j] = this->data[j][i];
        //    A_transpose.data[j][i] = this->data[i][j];
        }
    }
    return A_transpose;
}

Matrix Matrix::mat_mult(Matrix B){
    Matrix result(this->getData().first.first,B.getData().first.second);
    try{
        //if A.cols != B.rows 
         if ((*this).getData().first.second != B.getData().first.second)
     throw "Matrix dimensions doesn't fit in matrix Multiplication \n A.cols != B.rows" ;

      
    for(int row = 0 ; row < this->getData().first.first ; row++){
        for(int col =  0 ; col < B.getData().first.second ; col++){
            for(int op = 0 ; op < B.getData().first.second ; op++){
                result.data[row][col] += this->data[row][op] * B.data[op][col];
            }
        }
    }
    }
    catch(const char* error ){
        std::cout<<error<<"\n";
    }
   
    return result;
   

}
Matrix identity(const int &row, const int &col){

Matrix I(row,col);

for(int diagonal = 0 ;  diagonal < std::min(row,col) ; diagonal++)
        I.getData().second[diagonal][diagonal] = 1;
    
return I;

}
 void Matrix::L_U(){
    int row = this->getData().first.first, col = this->getData().first.second;
    Matrix L(identity(row,col).data);

    L.info();
    

}