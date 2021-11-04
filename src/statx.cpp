//
//  statx.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/1.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "statx.h"

namespace NCL_cxx {

template <typename T>
std::tuple<T, T, T, int, int> stat2(const T* const x, int xSize, T msgValue) {
    T xMean, xVar, xStd;
    int nPtUsed, ier;
    stat2(x, xSize, msgValue, xMean, xVar, xStd, nPtUsed, ier);
    return {xMean, xVar, xStd, nPtUsed, ier};
}
template std::tuple<float, float, float, int, int> stat2(const float* const x, int xSize, float msgValue);
template std::tuple<double, double, double, int, int> stat2(const double* const x, int xSize, double msgValue);

template <typename T>
void stat2(const T* const x, int xSize, T msgValue, T &xMean, T &xVar, T &xStd, int &nPtUsed, int &ier) {
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
//template void stat2<float>(const float* const x, int xSize, float msgValue, float &xMean, float &xVar, float &xStd, int &nPtUsed, int &ier);

template <typename T>
std::tuple<T, T, T, T, T, int, int> stat4(const T* const x, int xSize, T msgValue) {
    T xMean, xVar, xStd, xSkew, xKurt;
    int nPtUsed, ier;
    stat4(x, xSize, msgValue, xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier);
    return {xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier};;
}
template std::tuple<float, float, float, float, float, int, int> stat4<float>(const float* const x, int xSize, float msgValue);
template std::tuple<double, double, double, double, double, int, int> stat4<double>(const double* const x, int xSize, double msgValue);

template <typename T>
void stat4(const T* const x, int xSize, T msgValue, T &xMean, T &xVar, T &xStd, T &xSkew, T &xKurt, int &nPtUsed, int &ier) {
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

template <typename T>
std::tuple<T, T, T, int, int> medmrng(const T* const x, int xSize, T msgValue) {
    T xMedian, xMidRange, xRange;
    int nPtUsed, ier;
    medmrng(x, xSize, msgValue, xMedian, xMidRange, xRange, nPtUsed, ier);
    return {xMedian, xMidRange, xRange, nPtUsed, ier};
}
template std::tuple<float, float, float, int, int> medmrng<float>(const float* const x, int xSize, float msgValue);
template std::tuple<double, double, double, int, int> medmrng<double>(const double* const x, int xSize, double msgValue);

template <typename T>
void medmrng(const T* const x, int xSize, T msgValue, T &xMedian, T &xMidRange, T &xRange, int &nPtUsed, int &ier) {
    xMedian = msgValue; xMidRange = msgValue; xRange = msgValue;
    nPtUsed = 0;

    if (xSize < 1) {
        ier = 1; return;
    }
    ier = 0;

    std::vector<T> xWithNoMsg{};
    std::copy_if(x, x+xSize, std::back_inserter(xWithNoMsg), [msgValue](const T i){ return i != msgValue; });
    nPtUsed = xWithNoMsg.size();
    if (nPtUsed < 1) {
        ier = 2; return;
    }
    std::sort(xWithNoMsg.begin(), xWithNoMsg.end());

    xMidRange = 0.5 * (xWithNoMsg.back() + xWithNoMsg.front());
    xRange = xWithNoMsg.back() - xWithNoMsg.front();

    if (nPtUsed % 2 == 0) {
        xMedian = 0.5 * (xWithNoMsg[nPtUsed/2-1] + xWithNoMsg[nPtUsed/2]);
    } else {
        xMedian = xWithNoMsg[(nPtUsed+1)/2-1];
    }
}

template <typename T>
std::tuple<T, T, T, int, int> stat2t(const T* const x, int xSize, T msgValue, T pTrim) {
    T xMeanT, xVarT, xStdT;
    int nPtUsed, ier;
    stat2t(x, xSize, msgValue, pTrim, xMeanT, xVarT, xStdT, nPtUsed, ier);
    return {xMeanT, xVarT, xStdT, nPtUsed, ier};
}
template std::tuple<float, float, float, int, int> stat2t<float>(const float* const x, int xSize, float msgValue, float pTrim);
template std::tuple<double, double, double, int, int> stat2t<double>(const double* const x, int xSize, double msgValue, double pTrim);

template <typename T>
void stat2t(const T* const x, int xSize, T msgValue, T pTrim, T &xMeanT, T &xVarT, T &xStdT, int &nPtUsed, int &ier) {
    xMeanT = msgValue; xVarT = msgValue; xStdT = msgValue;
    ier = 0; nPtUsed = 0;
    
    if (xSize < 1) {
        ier = 1; return;
    }
    
    if (pTrim == 0) {
        stat2(x, xSize, msgValue, xMeanT, xVarT, xStdT, nPtUsed, ier);
        return;
    } else if (pTrim == 1) {
        ier = 2; return;
    }
    
    std::vector<T> xWithNoMsg{};
    std::copy_if(x, x+xSize, std::back_inserter(xWithNoMsg), [msgValue](const T i){ return i != msgValue; });
    nPtUsed = xWithNoMsg.size();
    if (nPtUsed < 1) {       // series contains all msg values
        ier = 3; return;
    }
    // sort series in ascending order
    std::sort(xWithNoMsg.begin(), xWithNoMsg.end());
    
    /// number of values trimmed from one side
    int trimNum = std::max(static_cast<int>(nPtUsed*0.5*pTrim), 1);
    
    if (nPtUsed-2*trimNum > 0) {
        stat2(xWithNoMsg.data()+trimNum, nPtUsed-2*trimNum, msgValue, xMeanT, xVarT, xStdT, nPtUsed, ier);
    } else {                 // not enough trimmed values
        ier = 4;
    }
}

template <typename T>
void esauto(const T* const x, int xSize, T msgValue, int maxLag, T* const acv, T* const acr, int &ier) {
    ier = (xSize < 2) ? 1 : 0;
    if (maxLag < 0 || maxLag > xSize) { ier = 2; }
    
    auto [xMean, xVar, xStd, nPtUsed, jer] = stat2(x, xSize, msgValue);
    if (xVar <= 0 && xVar != msgValue) { ier = 3; }
    if (ier != 0) {
        int fillSize = std::max(0, std::min(maxLag, xSize));
        std::fill_n(acv, fillSize, msgValue);
        std::fill_n(acr, fillSize, msgValue);
        return;
    }

    if (jer != 0) {
        ier = -jer; return;
    } else if (xVar == 0) {
        ier = -5; return;
    }
    
    acv[0] = xVar;
    acr[0] = 1.0;
    
    if (maxLag == 0) { return; }
    
    for (int lagIndex = 1; lagIndex < maxLag+1; ++lagIndex) {
        double x1 = 0.0, xn = 0.0;
        for (int i = 0; i < xSize-lagIndex; ++i) {
            if (x[i] != msgValue && x[i+lagIndex] != msgValue) {
                x1 += (x[i+lagIndex] - xMean) * (x[i] - xMean);
                xn += 1;
            }
        }
        if (xn >= 2) {
            acv[lagIndex] = x1 / (xn-1);
            acr[lagIndex] = acv[lagIndex] / xVar;
        } else {
            acv[lagIndex] = msgValue;
            acr[lagIndex] = msgValue;
        }
    }
}
template void esauto<float>(const float* const x, int xSize, float msgValue, int maxLag, float* const acv, float* const acr, int &ier);
template void esauto<double>(const double* const x, int xSize, double msgValue, int maxLag, double* const acv, double* const acr, int &ier);

template <typename T>
void escros(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, int maxLag, T* const ccv, T* const ccr, int &ier) {
    ier = (arrSize < 2) ? 1 : 0;
    if (maxLag < 0 || maxLag > arrSize) { ier = 2; }
    if (ier != 0) { return; }
    
    int fillSize = std::max(0, std::min(maxLag, arrSize));
    std::fill_n(ccv, fillSize, xMsgValue);
    std::fill_n(ccr, fillSize, xMsgValue);
    
    auto [xMean, xVar, xStd, nPtUsed, jer] = stat2(x, arrSize, xMsgValue);
    if (jer != 0) {
        ier = -jer;
    } else if (xStd == 0) {       // x must be a series of constant values
        ier = -5;
    } else if (nPtUsed == 0) {    // x must be a series of missing values
        ier = -6;
    }
    if (ier != 0) { return; }
    
    auto [yMean, yVar, yStd, y_nPtUsed, y_jer] = stat2(y, arrSize, yMsgValue);
    if (y_jer != 0) {
        ier = -(y_jer + 100);
    } else if (yStd == 0) {     // y must be a series of constant values
        ier = -105;
    } else if (y_nPtUsed == 0) {   // y must be a series of missing values
        ier = -106;
    }
    if (ier != 0) { return; }
    
    double xStdyStd = 1.0 / (xStd * yStd);
    
    for (int lagIndex = 0; lagIndex < maxLag + 1; ++lagIndex) {
        double xy1 = 0, xyn = 0.0;
        for (int i = 0; i < arrSize - lagIndex; ++i) {
            if (x[i] != xMsgValue && y[i+lagIndex] != yMsgValue) {
                xy1 += (y[i+lagIndex] - yMean) * (x[i] - xMean);
                xyn += 1;
            }
        }
        if (xyn >= 2) {
            ccv[lagIndex] = xy1 / (xyn - 1);
            ccr[lagIndex] = ccv[lagIndex] * xStdyStd;
        } else {
            ccv[lagIndex] = xMsgValue;
            ccr[lagIndex] = yMsgValue;
        }
    }
}
template void escros<float>(const float* const x, const float* const y, int arrSize, float xMsgValue, float yMsgValue, int maxLag, float* const ccv, float* const ccr, int &ier);
template void escros<double>(const double* const x, const double* const y, int arrSize, double xMsgValue, double yMsgValue, int maxLag, double* const ccv, double* const ccr, int &ier);

}
