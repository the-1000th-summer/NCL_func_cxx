//
//  linint2.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//

#include "linint2.h"

namespace NCL_cxx {

/// 检测一维序列是否单调上升
/// @param x 一维序列
/// @param xSize x的元素个数
bool monoInc(const double* const x, int xSize) {
    for (int i = 0; i < xSize-1; ++i) {
        if (x[i+1] <= x[i])
            return false;
    }
    return true;
}

}

