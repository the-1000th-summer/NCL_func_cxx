//
//  zregr.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/11/6.
//

#include "zregr.h"
#include <algorithm>

namespace NCL_cxx {

void zregr(const float* const x, const float* const y, int n, int m, float xMsgValue, float yMsgValue, float* const c, float* const yy) {
    
    for (int i = 0; i < n; ++i) {
        yy[i] = y[i];
        for (int j = 0; j < m; ++j) {
            if (x[i*m+j] == xMsgValue) {  // need fix
                yy[i] = yMsgValue;
                break;
            }
        }
    }
    
}

void zregr2(int n, int m, int m2, const float* const t, float tMsgValue, const float* const f, float* const c, float* const A, float* const s) {
    int nGood = n - std::count(t, t+n, tMsgValue);
    
    std::fill_n(s, m, 0.0);
    for (int i = 0; i < n; ++i) {
        float t_i = t[i];
        if (t_i == tMsgValue) { continue; }
        for (int j = 0; j < m; ++j) {
            s[j] += t_i * f[i*m+j];      // S=F'T
        }
    }
    
    // Construct matrix A:
    std::fill_n(A, A+m*m, 0.0);
    for (int i = 0; i < n; ++i) {
        float t_i = t[i];
        if (t_i != tMsgValue) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < m; ++k) {
                    A[j*m+k] += f[i*m+j] * f[i*m+k];  // A=F'F
                }
            }
        }
    }
    
    // Solve for coef vector C:
    auto work = std::make_unique<float[]>(m*2*m);
    for (int i = 0; i < m; ++i) {
        std::copy_n(A+i*m, m, work.get()+i*2*m);
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = m; j < 2*m; ++j) {
            work[i*2*m+j] = (m+i == j) ? 1.0 : 0.0;
        }
    }
    
    // TODO: not finished
    
    
}

}
