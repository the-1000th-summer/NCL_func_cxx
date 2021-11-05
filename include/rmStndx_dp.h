//
//  rmStndx_dp.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/5.
//

#ifndef rmStndx_dp_h
#define rmStndx_dp_h

namespace NCL_cxx {

template <typename T>
int rmvmean(T* const x, int xSize, T msgValue);

template <typename T>
void rmvmean(T* const x, int xSize, T msgValue, int &ier);

template <typename T>
int rmvmed(T* const x, int xSize, T msgValue);
template <typename T>
void rmvmed(T* const x, int xSize, T msgValue, int &ier);

}


#endif /* rmStndx_dp_h */
