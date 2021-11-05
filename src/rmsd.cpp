//
//  rmsd.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/5.
//

#include "rmsd.h"
#include <cmath>

namespace NCL_cxx {

template <typename T>
std::tuple<T, int, int> rmsd(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue) {
    T xyRmsd;
    int nPtUsed, ier;
    rmsd(x, y, arrSize, xMsgValue, yMsgValue, xyRmsd, nPtUsed, ier);
    return {xyRmsd, nPtUsed, ier};
}
template std::tuple<float, int, int> rmsd(const float* const x, const float* const y, int arrSize, float xMsgValue, float yMsgValue);
template std::tuple<double, int, int> rmsd(const double* const x, const double* const y, int arrSize, double xMsgValue, double yMsgValue);

template <typename T>
void rmsd(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, T &xyRmsd, int &nPtUsed, int &ier) {
    nPtUsed = 0; xyRmsd = xMsgValue;
    
    if (arrSize < 1) {
        ier = 1; return;
    }
    
    ier = 0; xyRmsd = 0;
    for (int i = 1; i < arrSize; ++i) {
        if (x[i] != xMsgValue && y[i] != yMsgValue) {
            nPtUsed += 1;
            xyRmsd += pow(x[i] - y[i], 2);
        }
    }
    
    if (nPtUsed > 0) {
        xyRmsd = std::sqrt(xyRmsd / nPtUsed);
    } else {
        xyRmsd = xMsgValue;
        ier = 2;
    }
}

}
