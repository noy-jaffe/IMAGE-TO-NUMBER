#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef Matrix (*ActivationFunction) (Matrix &vec);

namespace activation
{
    Matrix softmax(Matrix &vec);
    Matrix relu(Matrix &vec);
//    ActivationFunction get_activation_name();
}

#endif //ACTIVATION_H