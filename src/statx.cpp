//
//  statx.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/1.
//

#include <iostream>
#include <cmath>
#include "statx.h"

namespace NCL_cxx {

std::tuple<float, float, float, int, int> stat2(const float* const x, int xSize, float msgValue) {
    float xMean, xVar, xStd;
    int nPtUsed, ier;
    stat2(x, xSize, msgValue, xMean, xVar, xStd, nPtUsed, ier);
    return {xMean, xVar, xStd, nPtUsed, ier};
}
void stat2(const float* const x, int xSize, float msgValue, float &xMean, float &xVar, float &xStd, int &nPtUsed, int &ier) {
    xMean = msgValue; xVar = msgValue; xStd = msgValue;
    nPtUsed = 0;
    if (xSize < 1) {
        ier = 1;
        return;
    }
    ier = 0;
    double xSum = 0, xSquaredSum = 0;
    for (int i = 0; i < xSize; ++i) {
        if (x[i] != msgValue) {
            ++nPtUsed;
            xSum += x[i];
            xSquaredSum += pow(x[i], 2);
        }
    }
    
    if (nPtUsed > 1) {
        double x3 = pow(xSum, 2) / nPtUsed;
        double temp = (xSquaredSum - x3) / (nPtUsed - 1);
        xVar = std::max(temp, 0.0);
        xStd = std::sqrt(xVar);
        xMean = xSum / nPtUsed;
    } else if (nPtUsed == 1) {
        xMean = xSum;
        xVar = 0; xStd = 0;
    } else {
        ier = 2;
    }
}


}
