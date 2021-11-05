//
//  rmsd.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/5.
//

#ifndef rmsd_h
#define rmsd_h

#include <tuple>

namespace NCL_cxx {

template <typename T>
std::tuple<T, int, int> rmsd(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue);

template <typename T>
void rmsd(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, T &xyRmsd, int &nPtUsed, int &ier);


}

#endif /* rmsd_h */
