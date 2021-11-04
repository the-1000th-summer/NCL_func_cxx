//
//  statx.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/1.
//

#ifndef statx_h
#define statx_h

#include <tuple>

namespace NCL_cxx {

template <typename T>
std::tuple<T, T, T, int, int> stat2(const T* const x, int xSize, T msgValue);
template <typename T>
void stat2(const T* const x, int xSize, T msgValue, T &xMean, T &xVar, T &xStd, int &nPtUsed, int &ier);

template <typename T>
std::tuple<T, T, T, T, T, int, int> stat4(const T* const x, int xSize, T msgValue);
template <typename T>
void stat4(const T* const x, int xSize, T msgValue, T &xMean, T &xVar, T &xStd, T &xSkew, T &xKurt, int &nPtUsed, int &ier);

template <typename T>
std::tuple<T, T, T, int, int> medmrng(const T* const x, int xSize, T msgValue);
template <typename T>
void medmrng(const T* const x, int xSize, T msgValue, T &xMedian, T &xMidRange, T &xRange, int &nPtUsed, int &ier);

template <typename T>
std::tuple<T, T, T, int, int> stat2t(const T* const x, int xSize, T msgValue, T pTrim);
template <typename T>
void stat2t(const T* const x, int xSize, T msgValue, T pTrim, T &xMeanT, T &xVarT, T &xStdT, int &nPtUsed, int &ier);

template <typename T>
void esauto(const T* const x, int xSize, T msgValue, int maxLag, T* const acv, T* const acr, int &ier);

template <typename T>
void escros(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, int maxLag, T* const ccv, T* const ccr, int &ier);


}

#endif /* statx_h */
