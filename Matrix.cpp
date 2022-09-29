#include "Matrix.h"
#include <iostream>
#include <cmath>
#include<math.h>

Matrix::Matrix (int rows, int cols)
{
    if(rows<=0 || cols<=0){
        throw std::length_error("Invalid number of rows or cols");
    }
        this->_rows = rows;
        this->_cols = cols;
        this->_matrix_data = new float[rows * cols];
        //initialize
        for (int i = 0; i <rows*cols ; ++i) {
            _matrix_data[i] = 0;
        }

}

//copy constructor
Matrix::Matrix (const Matrix &m)
{
  this->_rows = m.get_rows ();
  this->_cols = m.get_cols ();
  this->_matrix_data = new float[_rows*_cols];
    for (int i = 0; i <_cols*_rows ; ++i) {
        _matrix_data[i] = m._matrix_data[i];
    }
}

Matrix::~Matrix ()
{
  delete[] _matrix_data;
}

int Matrix::get_rows () const
{
  return this->_rows;
}

int Matrix::get_cols () const
{
  return this->_cols;
}

Matrix &Matrix::transpose ()
{
  int cols = _cols;
  int rows = _rows;
  _cols = rows;
  _rows = cols;

  int n = rows * cols;
  float * temp;
  temp = new float [n];

  for (int i = 0; i < cols; i++)
  {
      for (int j = 0; j < rows; j++)
      {
          temp[j * cols + i] = _matrix_data[j + i * rows];
      }
  }
  delete[] _matrix_data;
  _matrix_data = temp;
  return *this;
}

Matrix & Matrix::vectorize ()
{
  int old_r = _rows;
  int old_c = _cols;
  _cols = 1;
  _rows = old_c * old_r;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < _rows * _cols; i++)
  {
      int row_counter = 0;
      while (row_counter < _rows)
      {
          std::cout << _matrix_data[i] << " ";
          row_counter++;
      }
      std::cout << "\n";
      row_counter = 0;
  }

}

Matrix Matrix::dot (const Matrix &m) const
{
  if (this->_rows != m._rows || this->_cols != m._cols){
      throw std::length_error("ERROR_INVALID_DIM");
  }

  Matrix new_mat = Matrix (this->_rows, this->_cols);
  int n = this->get_rows()* this->get_rows();
  float * temp;
  temp = new float[n];
  for (int i = 0; i > n; i++)
  {
    temp[i] = this->_matrix_data[i] * m._matrix_data[i];
  }
  new_mat._matrix_data = temp;
  return new_mat;
}

float Matrix::norm () const
{
  float sum = 0;
  int n = this->get_rows()* this->get_rows();
  for (int j = 0; j < n; ++j)
  {
    sum += (float) pow (this->_matrix_data[j], 2);
  }
  return (float) sqrt (sum);
}

Matrix Matrix::operator+(const Matrix &m) const {
    if (_rows != m.get_rows() || _cols != m.get_cols()){
        throw std::length_error("ERROR_INVALID_DIM");
    }

    Matrix new_matrix = Matrix(_rows, _cols);
    int n = this->get_rows()* this->get_rows();
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] += this->_matrix_data[i] + m._matrix_data[i];
    }
    return new_matrix;
}

Matrix& Matrix::operator+= (const Matrix &m)
{
    if (_rows != m.get_rows() || _cols != m.get_cols()){
        throw std::length_error("ERROR_INVALID_DIM");
    }
    for (int i = 0; i < _cols * _rows; ++i) {
        _matrix_data[i] += m._matrix_data[i];
    }
    return *this;
}
Matrix& Matrix::operator= (const Matrix &m)
{
  if (this == &m)
  {
    return *this;
  }

  delete[] _matrix_data;
  Matrix new_matrix = Matrix(m.get_rows(), m.get_cols());
  for (int i = 0; i < _rows*_cols; ++i)
  {
    new_matrix._matrix_data[i] = m._matrix_data[i];
  }
  return *this;
}

float& Matrix::operator() (int row, int col)
{
  return _matrix_data[col + row * _cols];
}

float& Matrix::operator() (int row, int col) const
{
    return _matrix_data[col + row * _cols];
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (_cols != m._rows){
        throw std::length_error("ERROR_INVALID_DIM");
    }

    Matrix new_matrix = Matrix(_rows, m.get_cols());

    int by_order=0;
    for (int row = 0; row < _rows; row++)
    {
        for (int col = 0; col < m._cols; col++)
        {
            float total = 0;
            for (int i = 0; i < _cols; i++)
            {
                total += _matrix_data[row * _cols + i] * m._matrix_data[i * m.get_cols() + col];
            }
            new_matrix._matrix_data[by_order] =total ;
            by_order +=1;
        }
    };
    return new_matrix;
}


Matrix Matrix::operator*(float c) const {

    Matrix new_matrix = Matrix(_rows,_cols);

    for (int i = 0; i <_cols*_rows ; ++i) {
        new_matrix._matrix_data[i] = _matrix_data[i] *c;
    }
    return new_matrix;
}

//friend operator
Matrix operator*(float c, const Matrix &m) {
    Matrix new_matrix = Matrix(m.get_rows(),m.get_cols());

    for (int i = 0; i <m.get_cols()*m.get_rows() ; ++i) {
        new_matrix._matrix_data[i] = m._matrix_data[i] *c;
    }
    return new_matrix;
}

float &Matrix::operator[](const int row) const {
    if (row < 0 || row > _cols*_rows ){
        throw std::length_error("wrong input");
    }
    return _matrix_data[row];
}

//friend operator
std::ostream& operator<<(std::ostream &stream, const Matrix &m) {
    if(!stream)
    {
        throw std::length_error("problem with stream");
    }
    for (int i = 0; i <m.get_rows() ; ++i)
    {
        for (int j = 0; j < m.get_cols(); ++j)
        {
            if (m(i,j) > 0.1){
                std::cout << "**";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
    return stream;


}

std::istream &operator>>(std::istream &stream, Matrix &m)
{
    if (!stream.good()){
        throw std::length_error("problem reading stream");
    }
    unsigned long length = sizeof (float) *m.get_cols() * m.get_rows();
    stream.read((char*) m._matrix_data,(long) length);
    if (!stream.good())
    {
        throw std::length_error("problem reading stream");
    }
    return stream;
}









