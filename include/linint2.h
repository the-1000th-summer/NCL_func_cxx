//
//  linint2.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//

#ifndef linint2_h
#define linint2_h

namespace NCL_cxx {

template <typename T>
bool monoInc(const T* const x, int xSize);

template <typename T>
void linint2(const T* const i_x, int i_xSize, const T* const i_y, int i_ySize, const T* const o_x, int o_xSize, const T* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);
template <typename T>
void linint2(int threadNum, int timeSize, const T* const i_x, int i_xSize, const T* const i_y, int i_ySize, const T* const o_x, int o_xSize, const T* const o_y, int o_ySize, const float* const fi, float* const fo, bool isCyclic, double msgValue);

template <typename T>
int checkMono(const T* const data, int dataSize);
template <typename T>
int checkMono(const T* const data1, int data1Size, const T* const data2, int data2Size);

template <typename T>
void lin2int1(const T* const i_data, const float* const fi, int i_dataSize, const T* const o_data, float* const fo, int o_dataSize, double msgValue, int isMono);
template <typename T>
void handleCyclic(const T* const i_data, const float* const fi, int i_dataSize, int isMono, T* const i_data_w, float* const fxiw);

}

#endif /* linint2_h */
