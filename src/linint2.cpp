//
//  linint2.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//
#include <iostream>
#include <algorithm>
#include <cassert>
#include <memory>

#include "linint2.h"

namespace NCL_cxx {

/// 检测一维序列是否单调上升
/// @param x 一维序列
/// @param xSize x的元素个数
template <typename T>
bool monoInc(const T* const x, int xSize) {
    for (int i = 0; i < xSize-1; ++i) {
        if (x[i+1] <= x[i])
            return false;
    }
    return true;
}

template bool monoInc(const float* const x, int xSize);
template bool monoInc(const double* const x, int xSize);

/// 对2d array进行双线性插值
/// @param[in] i_x 输入的1d array (x方向坐标)
/// @param[in] i_xSize i_x元素个数
/// @param[in] i_y 输入的1d array (y方向坐标)
/// @param[in] i_ySize i_y元素个数
/// @param[in] o_x 1d array (regrid后的x方向坐标)
/// @param[in] o_xSize o_x元素个数
/// @param[in] o_y 1d array (regrid后的y方向坐标)
/// @param[in] o_ySize o_y元素个数
/// @param[in] fi 原始数据 (2d array) (i_ySize, i_xSize)
/// @param[out] fo regrid后的数据 (2d array) (o_ySize, o_xSize)
/// @param[in] isCyclic 坐标的单调性
/// @param[in] msgValue 缺测值
template <typename T>
void linint2(const T* const i_x, int i_xSize, const T* const i_y, int i_ySize, const T* const o_x, int o_xSize, const T* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue) {
    assert(o_xSize >= 1 && o_ySize >= 1);      // 确保输出数组各维度至少有一个点
    assert(i_xSize >= 2 && i_ySize >= 2);         // 确保输入数组各维度至少有2个点
    std::fill_n(fo, o_xSize*o_ySize, msgValue);  // 将输出的数组所有值设为缺测值
    int isMono = checkMono(i_x, i_xSize, o_x, o_xSize);
    assert(isMono != 0);          // 确保i_x和o_x有相同的单调性
    isMono = checkMono(i_y, i_ySize, o_y, o_ySize);
    assert(isMono != 0);          // 确保i_y和o_y有相同的单调性
    
    auto xiw = std::make_unique<T[]>(i_xSize + 2);
    auto fxiw = std::make_unique<float[]>(i_xSize + 2);
    auto fyiw = std::make_unique<float[]>(i_ySize);
    auto foyw = std::make_unique<float[]>(o_ySize);
    auto ftmp = std::make_unique<float[]>(i_ySize*o_xSize);    // 2d array
    
    if (!isCyclic) {            // 数据非循环
        // interpolate in the x direction
        for (int yIndex = 0; yIndex < i_ySize; ++yIndex) {
            lin2int1(i_x, fi+yIndex*i_xSize, i_xSize, o_x, ftmp.get()+yIndex*o_xSize, o_xSize, msgValue, isMono);
        }
        // interpolate in the y direction
        for (int xIndex = 0; xIndex < o_xSize; ++xIndex) {
            for (int yIndex = 0; yIndex < i_ySize; ++yIndex) {
                fyiw[yIndex] = ftmp[yIndex*o_xSize+xIndex];
            }
            lin2int1(i_y, fyiw.get(), i_ySize, o_y, foyw.get(), o_ySize, msgValue, isMono);
            for (int yIndex = 0; yIndex < o_ySize; ++yIndex) {
                fo[yIndex*o_xSize+xIndex] = foyw[yIndex];
            }
        }
    } else {
        for (int yIndex = 0; yIndex < i_ySize; ++yIndex) {
            for (int xIndex = 0; xIndex < i_xSize; ++xIndex) {
                xiw[xIndex+1] = i_x[xIndex];
                fxiw[xIndex+1] = fi[yIndex*i_xSize+xIndex];
            }
            handleCyclic(i_x, fi+yIndex*i_xSize, i_xSize, isMono, xiw.get(), fxiw.get());
            lin2int1(xiw.get(), fxiw.get(), i_xSize+2, o_x, ftmp.get()+yIndex*o_xSize, o_xSize, msgValue, isMono);
        }
        // interpolate in the y direction
        for (int xIndex = 0; xIndex < o_xSize; ++xIndex) {
            for (int yIndex = 0; yIndex < i_ySize; ++yIndex) {
                fyiw[yIndex] = ftmp[yIndex*o_xSize+xIndex];
            }
            lin2int1(i_y, fyiw.get(), i_ySize, o_y, foyw.get(), o_ySize, msgValue, isMono);
            for (int yIndex = 0; yIndex < o_ySize; ++yIndex) {
                fo[yIndex*o_xSize+xIndex] = foyw[yIndex];
            }
        }
    }
}
template void linint2(const float* const i_x, int i_xSize, const float* const i_y, int i_ySize, const float* const o_x, int o_xSize, const float* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);
template void linint2(const double* const i_x, int i_xSize, const double* const i_y, int i_ySize, const double* const o_x, int o_xSize, const double* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);

/// 对3d array进行双线性插值
/// @param[in] timeSize 时间维度长度
/// @param[in] i_x 输入的1d array (x方向坐标)
/// @param[in] i_xSize i_x元素个数
/// @param[in] i_y 输入的1d array (y方向坐标)
/// @param[in] i_ySize i_y元素个数
/// @param[in] o_x 1d array (regrid后的x方向坐标)
/// @param[in] o_xSize o_x元素个数
/// @param[in] o_y 1d array (regrid后的y方向坐标)
/// @param[in] o_ySize o_y元素个数
/// @param[in] fi 原始数据 (3d array) (timeSize, i_ySize, i_xSize)
/// @param[out] fo regrid后的数据 (3d array) (timeSize, o_ySize, o_xSize)
/// @param[in] isCyclic 坐标的单调性
/// @param[in] msgValue 缺测值
template <typename T>
void linint2(int threadNum, int timeSize, const T* const i_x, int i_xSize, const T* const i_y, int i_ySize, const T* const o_x, int o_xSize, const T* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue) {
    std::cout << "thread num: " << threadNum << std::endl;
#   pragma omp parallel for num_threads(threadNum)
    for (int timeIndex = 0; timeIndex < timeSize; ++timeIndex) {
//        if (timeIndex % 1000 == 0) { std::cout << timeIndex << '\r'; }
        linint2(i_x, i_xSize, i_y, i_ySize, o_x, o_xSize, o_y, o_ySize, fi+timeIndex*i_xSize*i_ySize, fo+timeIndex*o_xSize*o_ySize, isCyclic, msgValue);
    }
}
template void linint2(int threadNum, int timeSize, const float* const i_x, int i_xSize, const float* const i_y, int i_ySize, const float* const o_x, int o_xSize, const float* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);
template void linint2(int threadNum, int timeSize, const double* const i_x, int i_xSize, const double* const i_y, int i_ySize, const double* const o_x, int o_xSize, const double* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);


/// 检查data是否单调上升/下降
/// @param[in] data 1d array
/// @param[in] dataSize data元素个数
/// @returns 1: 单调上升; -1: 单调下降; 0: 无单调性
template <typename T>
int checkMono(const T* const data, int dataSize) {
    if (dataSize < 2)
        return 1;
    if (data[1] > data[0]) {               // 是否单调上升?
        for (int i = 1; i < dataSize - 1; ++i) {   // 已经确定了data[1]>data[0],所以i从2开始
            if (data[i+1] <= data[i])          // 非 mono
                return 0;
        }
        return 1;          // 单调上升
    } else {                              // 是否单调下降?
        for (int i = 0; i < dataSize - 1; ++i) {
            if (data[i+1] >= data[i])          // 非 mono
                return 0;
        }
        return -1;         // 单调下降
    }
}
template int checkMono(const float* const data, int dataSize);
template int checkMono(const double* const data, int dataSize);

/// 检查data1和data2是否单调上升/下降
/// @param[in] data1 1d array
/// @param[in] data1Size data1的元素个数
/// @param[in] data2 1d array
/// @param[in] data2Size data2的元素个数
/// @returns 1: data1和data2都单调上升; -1: data1和data2都单调下降; 0: data1或/和data2不具单调性或两者单调性不同
template <typename T>
int checkMono(const T* const data1, int data1Size, const T* const data2, int data2Size) {
    int isData1Mono = checkMono(data1, data1Size);
    if (isData1Mono == 0) {
        return 0;
    } else {           // isData1Mono != 0
        int isData2Mono = checkMono(data2, data2Size);
        if (isData1Mono != isData2Mono)     // isData2Mono == 0的情况也包含在这里边
            return 0;
        return isData1Mono;
    }
}
template int checkMono(const float* const data1, int data1Size, const float* const data2, int data2Size);
template int checkMono(const double* const data1, int data1Size, const double* const data2, int data2Size);

/// 对1d array进行线性插值
/// @param[in] i_data 输入的1d array (原始数据坐标)
/// @param[in] fi 输入的1d array (实际变量值)
/// @param[in] i_dataSize i_data的元素个数
/// @param[in] o_data 输出的1d array (regrid后的坐标)
/// @param[out] fo 输出的1d array (实际变量值)
/// @param[in] o_dataSize o_data的元素个数
/// @param[in] msgValue 缺测值
/// @param[in] isMono 坐标的单调性
template <typename T>
void lin2int1(const T* const i_data, const float* const fi, int i_dataSize, const T* const o_data, float* const fo, int o_dataSize, double msgValue, int isMono) {
    std::fill_n(fo, o_dataSize, msgValue);   // 输出array先初始化为缺测值
    
    int startIndex = 0;
    int nis = startIndex;
    // main loop [exact matches], nistrt minimizes extra checks
    for (int oIndex = 0; oIndex < o_dataSize; ++oIndex) {
        for (int iIndex = startIndex; iIndex < i_dataSize; ++iIndex) {
            if (o_data[oIndex] == i_data[iIndex]) {
                fo[oIndex] = fi[iIndex];
                nis = iIndex + 1;          // 算得下一次循环的开始的index
                break;
            }
        }
        startIndex = nis;
    }
    // main loop [interpolation]
    if (isMono == 1) {              // 单调递增
        for (int oIndex = 0; oIndex < o_dataSize; ++oIndex) {
            for (int iIndex = 0; iIndex < i_dataSize - 1; ++iIndex) {
                if (o_data[oIndex] > i_data[iIndex] && o_data[oIndex] < i_data[iIndex+1]) {
                    if (fi[iIndex] != msgValue && fi[iIndex+1] != msgValue) {
                        double slope = (fi[iIndex+1] - fi[iIndex]) / (i_data[iIndex+1] - i_data[iIndex]);
                        fo[oIndex] = fi[iIndex] + slope * (o_data[oIndex] - i_data[iIndex]);
                    }
                }
            }
        }
    } else if (isMono == -1) {             // 单调递减
        for (int oIndex = 0; oIndex < o_dataSize; ++oIndex) {
            for (int iIndex = 0; iIndex < i_dataSize - 1; ++iIndex) {
                if (o_data[oIndex] < i_data[iIndex] && o_data[oIndex] > i_data[iIndex+1]) {
                    if (fi[iIndex] != msgValue && fi[iIndex+1] != msgValue) {
                        double slope = (fi[iIndex+1] - fi[iIndex]) / (i_data[iIndex+1] - i_data[iIndex]);
                        fo[oIndex] = fi[iIndex] + slope * (o_data[oIndex] - i_data[iIndex]);
                    }
                }
            }
        }
    }
}
template void lin2int1(const float* const i_data, const float* const fi, int i_dataSize, const float* const o_data, float* const fo, int o_dataSize, double msgValue, int isMono);
template void lin2int1(const double* const i_data, const float* const fi, int i_dataSize, const double* const o_data, float* const fo, int o_dataSize, double msgValue, int isMono);


/// 当原始数据x方向为cyclic时, 使用此函数补齐数据, 为接下来的运算做准备
/// @param[in] i_data 输入的1d array (原始数据坐标)
/// @param[in] fi 输入的1d array (实际变量值)
/// @param[in] i_dataSize i_data元素个数
/// @param[in] isMono 坐标的单调性
/// @param[out] i_data_w 输出的1d array (坐标的扩展数组, 元素个数应比i_data的多2)
/// @param[out] fxiw 输出的1d array（实际变量的扩展数组, 元素个数应比fi的多2）
template <typename T>
void handleCyclic(const T* const i_data, const float* const fi, int i_dataSize, int isMono, T* const i_data_w, float* const fxiw) {
    double dx = std::abs(i_data[1] - i_data[0]);
    i_data_w[0] = i_data[0] - isMono * dx;
    fxiw[0] = fi[i_dataSize-1];
    dx = std::abs(i_data[i_dataSize-1] - i_data[i_dataSize-2]);
    i_data_w[i_dataSize+1] = i_data[i_dataSize-1] + isMono * dx;
    fxiw[i_dataSize+1] = fi[0];
}
template void handleCyclic(const float* const i_data, const float* const fi, int i_dataSize, int isMono, float* const i_data_w, float* const fxiw);
template void handleCyclic(const double* const i_data, const float* const fi, int i_dataSize, int isMono, double* const i_data_w, float* const fxiw);

}

