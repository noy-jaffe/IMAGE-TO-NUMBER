#include "Dense.h"

Dense::Dense(const Matrix &weights, const Matrix &bias, ActivationFunction act_func) {
    this->_weights = weights;
    this->_bias= bias;
    this->_act_func =act_func;
}

Matrix Dense::get_weights() const {
    return _weights;
}

Matrix Dense::get_bias() const {
    return _bias;
}

ActivationFunction Dense::get_activation() const { //todo check
    return _act_func;
}

Matrix Dense::operator()(const Matrix &input) const {
    Matrix new_mat = this->get_weights()*input + this->get_bias();
    return _act_func(new_mat);
}

Dense::Dense() {
    this->_act_func = nullptr;

}

