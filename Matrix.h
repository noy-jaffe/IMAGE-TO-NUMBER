// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#define ERROR_INVALID_DIM "Error: invalid Matrix dimensions: "


/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix{
 public:
  Matrix(int rows, int cols);
  Matrix(): Matrix(1, 1) {};
  Matrix(const Matrix& m); //copy constructor
  ~Matrix();

  int get_rows() const;
  int get_cols() const;
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& m) const;
  float norm() const;

  //operators
  Matrix operator + (const Matrix &m) const;
  Matrix& operator = (const Matrix &m);
  Matrix operator * (const Matrix &m) const;
  Matrix operator * (float c) const;
  friend Matrix operator * (float c, const Matrix &m);
  Matrix& operator += (const Matrix &m);
  float& operator() (int row, int col);
  float& operator() (int row, int col) const;
  float& operator [] (int row) const;


  friend std::istream& operator >> (std::istream &stream, Matrix &m);
  friend std::ostream& operator<< (std::ostream &stream, const Matrix &m);   //todo check


 private:
  int _rows;
  int _cols;
  float* _matrix_data;

};

#endif //MATRIX_H