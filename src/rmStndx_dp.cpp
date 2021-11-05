//
//  rmStndx_dp.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/5.
//

#include "rmStndx_dp.h"
#include "statx.h"
#include <cmath>

namespace NCL_cxx {

template <typename T>
int rmvmean(T* const x, int xSize, T msgValue) {
    int ier;
    rmvmean(x, xSize, msgValue, ier);
    return ier;
}
template int rmvmean<float>(float* const x, int xSize, float msgValue);
template int rmvmean<double>(double* const x, int xSize, double msgValue);

template <typename T>
void rmvmean(T* const x, int xSize, T msgValue, int &ier) {
    auto [xMean, xVar, xStd, nPtUsed, ier_2] = stat2(x, xSize, msgValue);
    ier = ier_2;
    
    if (ier != 0) { return; }
    for (int i = 0; i < xSize; ++i) {
        if (x[i] != msgValue) { x[i] -= xMean; }
    }
}

template <typename T>
int rmvmed(T* const x, int xSize, T msgValue) {
    int ier;
    rmvmed(x, xSize, msgValue, ier);
    return ier;
}
template int rmvmed<float>(float* const x, int xSize, float msgValue);
template int rmvmed<double>(double* const x, int xSize, double msgValue);

template <typename T>
void rmvmed(T* const x, int xSize, T msgValue, int &ier) {
    auto [xMedian, xMidRange, xRange, nPtUsed, ier_2] = medmrng(x, xSize, msgValue);
    ier = ier_2;
    
    if (ier != 0) { return; }
    for (int i = 0; i < xSize; ++i) {
        if (x[i] != msgValue) { x[i] -= xMedian; }
    }
}

template <typename T>
int xstnd(T* const x, int xSize, T msgValue, int iopt) {
    int ier;
    xstnd(x, xSize, msgValue, iopt, ier);
    return ier;
}
template int xstnd<float>(float* const x, int xSize, float msgValue, int iopt);
template int xstnd<double>(double* const x, int xSize, double msgValue, int iopt);

template <typename T>
void xstnd(T* const x, int xSize, T msgValue, int iopt, int &ier) {
    auto [xMean, xVar, xStd, nPtUsed, ier_2] = stat2(x, xSize, msgValue);
    ier = ier_2;
    
    if (iopt == 1 && nPtUsed > 1) {
        xStd = std::sqrt((nPtUsed-1.0) * xVar / nPtUsed);
    }
    
    if (ier != 0 || xStd <= 0) { return; }
    for (int i = 0; i < xSize; ++i) {
        if (x[i] != msgValue) {
            x[i] = (x[i] - xMean) / xStd;
        }
    }
}

}
