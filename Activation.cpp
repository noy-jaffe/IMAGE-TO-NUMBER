
#include "Activation.h"
#include <cmath>

Matrix activation::softmax(Matrix &vec){
    Matrix new_matrix = Matrix(vec.get_rows(), vec.get_cols());
    float sum = 0;
    for (int i = 0; i <vec.get_rows()*vec.get_cols() ; ++i) {
        sum +=std::exp(vec[i]);

    }
    for (int i = 0; i <vec.get_rows()*vec.get_cols() ; ++i) {
        new_matrix[i] = std::exp(vec[i]) / sum;
    }
    return new_matrix;
}

Matrix activation::relu(Matrix &vec) {
    Matrix new_matrix = Matrix(vec.get_rows(), vec.get_cols());
    for (int i = 0; i <vec.get_rows()*vec.get_cols() ; ++i) {
        if(vec[i]>0){
            new_matrix[i] = vec[i];
        }
        else{
            new_matrix[i] = 0;
        }
    }
    return new_matrix;
}

