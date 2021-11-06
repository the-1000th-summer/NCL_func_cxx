//
//  regcoef.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/6.
//

#ifndef regcoef_h
#define regcoef_h
#include <tuple>

namespace NCL_cxx {

template <typename T>
std::tuple<T,T,T,T,int,int> regcoef(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue);
template <typename T>
void regcoef(const T* const x, const T* const y, int arrSize, T xMsgValue, T yMsgValue, T &rCoef, T &tVal, int &nPtUsed, T &rStd, T &yInt, int &ier);

}


#endif /* regcoef_h */
