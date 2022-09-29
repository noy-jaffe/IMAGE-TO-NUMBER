#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
class Dense{
private:
    Matrix _weights;
    Matrix _bias;
    ActivationFunction _act_func;

public:
    Dense();
    Dense(const Matrix &weights, const Matrix &bias, ActivationFunction act_func);
    Matrix get_weights() const;
    Matrix get_bias() const;
    ActivationFunction get_activation() const;
    Matrix operator() (const Matrix& input) const;
};



#endif //DENSE_H
