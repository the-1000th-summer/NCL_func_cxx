//
//  rcm2rgrid.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//

#ifndef rcm2rgrid_h
#define rcm2rgrid_h

namespace NCL_cxx {

template <typename T>
void rcm2rgrid(const T* const xi, const T* const yi, int xiSize, int yiSize, const T* const xo, const T* const yo, int xoSize, int yoSize, const T* const fi, T* const fo, T msgValue, int &ier);

void rgrid2rcm(const double* const xi, const double* const yi, int xiSize, int yiSize, const double* const xo, const double* const yo, int xoSize, int yoSize, const double* const fi, double* const fo, double msgValue, int &ier);

}
#endif /* rcm2rgrid_h */
