//
// Created by noija on 5/15/2022.
//

#include "MlpNetwork.h"


MlpNetwork::MlpNetwork(const Matrix *weights, const Matrix *biases) {
    _layer_1 = Dense(weights[0], biases[0], activation::relu);
    _layer_2 = Dense(weights[1], biases[2], activation::relu);
    _layer_3 = Dense(weights[2], biases[2], activation::relu);
    _layer_4 = Dense(weights[3], biases[3], activation::softmax);

}

digit MlpNetwork::operator()(const Matrix &img) const {
    Matrix r_1 = _layer_1(img);
    Matrix r_2 = _layer_2(r_1);
    Matrix r_3 = _layer_3(r_2);
    Matrix r_4 = _layer_4(r_3);

    digit output = {0, r_4[0]};
    for (int i = 0; i <r_4.get_cols()*r_4.get_rows() ; ++i) {
        if (r_4[i]>= output.probability){
            if( r_4[i] == output.probability && i < output.value)
            {
                output.probability = r_4[i];
                output.value = i;
            }
        }
    }
    return output;
}


