//
//  regcoef.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/6.
//

#include "regcoef.h"
#include <cmath>

namespace NCL_cxx {

template <typename T>
std::tuple<T,T,T,T,int,int> regcoef(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue) {
    T rCoef, tVal, rStd, yInt;
    int nPtUsed, ier;
    regcoef(x, y, arrSize, xMsgValue, yMsgValue, rCoef, tVal, nPtUsed, rStd, yInt, ier);
    return {rCoef, tVal, rStd, yInt, nPtUsed, ier};
}
template std::tuple<float,float,float,float,int,int> regcoef(const float* const x, const float* const y, int arrSize, float xMsgValue, float yMsgValue);
template std::tuple<double,double,double,double,int,int> regcoef(const double* const x, const double* const y, int arrSize, double xMsgValue, double yMsgValue);

template <typename T>
void regcoef(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, T &rCoef, T &tVal, int &nPtUsed, T &rStd, T &yInt, int &ier) {
    
    ier = 0;
    tVal = yMsgValue; rCoef = yMsgValue; rStd = yMsgValue;
    
    if (arrSize < 2) { ier = 1; return; }
    
    double rNull = 0.0;
    double xSum = 0, ySum = 0, x2Sum = 0, y2Sum = 0, xySum = 0;
    nPtUsed = 0;
    
    for (int i = 0; i < arrSize; ++i) {
        if (x[i] != xMsgValue && y[i] != xMsgValue) {
            xSum += x[i]; ySum += y[i];
            x2Sum += pow(x[i], 2);
            y2Sum += pow(y[i], 2);
            xySum += x[i] * y[i];
            nPtUsed += 1;
        }
    }
    
    if (nPtUsed < 1) {           // all msg values
        ier = 5; return;
    } else if (nPtUsed < 3) {    // not enough data
        ier = 6; return;
    }
    
    double xAve = xSum / nPtUsed;
    double yAve = ySum / nPtUsed;
    
    double xVar = x2Sum - pow(xSum, 2) / nPtUsed;
    double yVar = y2Sum - pow(ySum, 2) / nPtUsed;
    double xyVar = xySum - xSum * ySum / nPtUsed;
    
    if (xVar > 0) {
        /// regression coef (b in book)
        rCoef = xyVar / xVar;
        double ssqreg = pow(xyVar, 2) / xVar;
        double ssq = (yVar - ssqreg) / (nPtUsed - 2);
        /// v[b] in book {variance of B}
        double sqrtVb = std::sqrt(ssq / xVar);
        if (sqrtVb > 0) {
            tVal = (rCoef - rNull) / sqrtVb;
            rStd = sqrtVb;
        } else {
            tVal = yMsgValue;
        }
        /// degrees of freedom
        int df = nPtUsed - 2;
        yInt = yAve - rCoef * xAve;
    } else {
        ier = 7;
        tVal = yMsgValue; rCoef = yMsgValue; yInt = yMsgValue;
    }
    
}

}
