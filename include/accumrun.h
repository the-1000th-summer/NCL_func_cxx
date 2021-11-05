//
//  accumrun.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/4.
//

#ifndef accumrun_h
#define accumrun_h

#include <vector>
    
namespace NCL_cxx {

template <typename T>
std::vector<T> acumrun(const T* const x, int xSize, T msgValue, int nRun, int iopt);

template <typename T>
void acumrun(const T* const x, int xSize, T msgValue, int nRun, int iopt, T* const xAcc);

}

#endif /* accumrun_h */
