//
//  zregr.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/6.
//

#ifndef zregr_h
#define zregr_h

namespace NCL_cxx {

void zregr(const float* const x, const float* const y, int n, int m, float xMsgValue, float yMsgValue, float* const c, float* const yy);

void zregr2(int n, int m, int m2, const float* const t, float tMsgValue, const float* const f, float* const c, float* const A, float* const s);

}

#endif /* zregr_h */
