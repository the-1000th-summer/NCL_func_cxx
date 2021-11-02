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


std::tuple<float, float, float, int, int> stat2(const float* const x, int xSize, float msgValue);
void stat2(const float* const x, int xSize, float msgValue, float &xMean, float &xVar, float &xStd, int &nPtUsed, int &ier);

}

#endif /* statx_h */
