//
//  rcm2rgrid.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//

#include "rcm2rgrid.h"
#include "dmapgci.h"

namespace NCL_cxx {

void rgrid2rcm(const double* const xi, const double* const yi, int xiSize, int yiSize, const double* const xo, const double* const yo, int xoSize, int yoSize, const double* const fi, float* const fo, double msgValue, int &ier) {
    
    ier = 0;
    if (xiSize <= 1 || yiSize <= 1 || xoSize <= 1 || yoSize <= 1) {
        ier = 1; return;
    }
    
    
    
}

}

