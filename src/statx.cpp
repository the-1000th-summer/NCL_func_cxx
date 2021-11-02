//
//  statx.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/1.
//

#include <iostream>
#include <cmath>
#include <numeric>
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
    int msgSize = std::count(x, x+xSize, msgValue);
    nPtUsed = xSize - msgSize;
    double xSum = std::accumulate(x, x+xSize, 0.0) - msgSize*msgValue;
    double xSquaredSum = std::inner_product(x, x+xSize, x, 0.0) - msgSize*pow(msgValue, 2);
    
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

std::tuple<float, float, float, float, float, int, int> stat4(const float* const x, int xSize, float msgValue) {
    float xMean, xVar, xStd, xSkew, xKurt;
    int nPtUsed, ier;
    stat4(x, xSize, msgValue, xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier);
    return {xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier};;
}
void stat4(const float* const x, int xSize, float msgValue, float &xMean, float &xVar, float &xStd, float &xSkew, float &xKurt, int &nPtUsed, int &ier) {
    xMean = msgValue; xVar = msgValue; xStd = msgValue;
    xSkew = msgValue; xKurt = msgValue; nPtUsed = 0;
    
    if (xSize < 1) {
        ier = 1;
        return;
    }
    ier = 0;
    int msgSize = std::count(x, x+xSize, msgValue);
    nPtUsed = xSize - msgSize;
    double xSum = std::accumulate(x, x+xSize, 0.0) - msgSize*msgValue;
    double xSquaredSum = std::inner_product(x, x+xSize, x, 0.0) - msgSize*pow(msgValue, 2);
    
    if (nPtUsed > 1) {
        double x3 = pow(xSum, 2) / nPtUsed;
        xVar = std::max((xSquaredSum - x3) / (nPtUsed - 1), 0.0);
        xStd = std::sqrt(xVar);
        xMean = xSum / nPtUsed;
        if (xVar > 0.0) {
            double x2 = 0, x3 = 0;
            for (int i = 0; i < xSize; ++i) {
                if (x[i] != msgValue) {
                    double x4 = x[i] - xMean;
                    double x1 = pow(x4, 3);
                    x2 += x1;
                    x3 += x1 * x4;
                }
            }
            xSkew = (x2/pow(std::sqrt(xVar), 3)) / nPtUsed;
            xKurt = (x3/pow(xVar, 2)) / nPtUsed - 3;
        }
    } else if (nPtUsed == 1) {
        xMean = xSum;
        xVar = 0; xStd = 0;
    } else {
        ier = 2;
    }
}

}
