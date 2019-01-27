#include "learnsomething.h"

#ifdef LEARN_EIGEN
#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;

void LearnEigen()
{
    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << "matrix m: \n" << m << std::endl;


    std::cout << "learn eigen" << std::endl;
}

#endif