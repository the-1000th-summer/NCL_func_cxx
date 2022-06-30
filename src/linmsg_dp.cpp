//
//  linmsg_dp.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2022/6/30.
//

#include <algorithm>

#include "linmsg_dp.h"

namespace NCL_cxx {

void linmsg(double* const x, int npts, double msgValue, int mflag, int mptcrt) {
    if (!std::any_of(x, x+npts, [msgValue](double x_ele) {return x_ele != msgValue;})) { return; }
    
    /// 连续missing values的起始index和末尾index
    int nStart = -1, nEnd = -1;    // -1 means nil.
    int nPtcrt = abs(mptcrt);
    
    for (int n = 0; n < npts; ++n) {
        if (x[n] == msgValue) {
            if (nStart == -1)      // there are no missing prior values
                nStart = n;
            nEnd = n;
        } else if (nStart != -1) {  // meet non-missing value, has missing values in prior values
            if ((nEnd-nStart+1) > nPtcrt) {  // too many missing value here, give up interpolation.
                nStart = -1;
                nEnd = -1;
                continue;
            }
            if (nStart == 0) {   // initial series values are msg : set to first non-msg value
                double msgOrFirstVal = (mflag < 0) ? x[n] : msgValue;
                for (int nn = nStart; nn < nEnd + 1; ++nn) {
                    x[nn] = msgOrFirstVal;
                }
            } else {
                int nBase = nStart - 1;
                double slope = (x[n] - x[nBase]) / (n - nBase);
                for (int nn = nStart; nn < nEnd + 1; ++nn) {
                    x[nn] = x[nBase] + slope * (nn - nBase);
                }
            }
            
            nStart = -1;
            nEnd = -1;
        }
    }
    
    // check the end points
    if (nEnd == npts - 1) {  // last value is missing
        double msgOrLastVal = (mflag < 0) ? x[nStart - 1] : msgValue;
        for (int nn = nStart; nn < npts; ++nn)
            x[nn] = msgOrLastVal;
    }
    
}

}

