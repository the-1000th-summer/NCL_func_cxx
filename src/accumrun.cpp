//
//  accumrun.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/4.
//

#include "accumrun.h"
#include <vector>
#include <algorithm>

namespace NCL_cxx {

template <typename T>
std::vector<T> acumrun(const T* const x, int xSize, T msgValue, int nRun, int iopt) {
    std::vector<T> xAcc(xSize);
    acumrun(x, xSize, msgValue, nRun, iopt, xAcc.data());
    return xAcc;
}
template std::vector<int> acumrun(const int* const x, int xSize, int msgValue, int nRun, int iopt);
template std::vector<float> acumrun(const float* const x, int xSize, float msgValue, int nRun, int iopt);
template std::vector<double> acumrun(const double* const x, int xSize, double msgValue, int nRun, int iopt);

template <typename T>
void acumrun(const T* const x, int xSize, T msgValue, int nRun, int iopt, T* const xAcc) {
    std::fill_n(xAcc, nRun-1, msgValue);      // 1st (nrun-1) are msg
    
    for (int i = nRun-1; i < xSize; ++i) {
        xAcc[i] = 0;
        for (int j = 0; j < nRun; ++j) {
            if (x[i-j] != msgValue) {
                xAcc[i] += x[i-j];
            } else {
                if (iopt == 0) {
                    xAcc[i] = msgValue;
                    break;
                }
            }
        }
    }
}

}
