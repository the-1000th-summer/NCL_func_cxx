//
//  wrf_user.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/25.
//

#include "wrf_user.h"

namespace NCL_cxx {

void wrf_interp_3d_z(const double* const data3d, double* const out2d, const double* const zdata, const int* const levels, int nx, int ny, int nz, int nlev, double missingVal) {
    // does vertical coordinate increase or decrease with increasing k?
    // set offset appropriately
    
    int ip = 0, im = 1;
    if (zdata[0] > zdata[(nz-1)*nx*ny]) {
        ip = 1;
        im = 0;
    }
    
    for (int lev = 0; lev < nlev; ++lev) {
        for (int j = 0; j < ny; ++j) {
            for (int i = 0; i < nx; ++i) {
                out2d[lev*nx*ny+j*nx+i] = missingVal;
                bool doInterp = false;
                int kp = nz;
                int desiredLoc = levels[lev];
                while (!doInterp && (kp >= 2)) {
//                    if (zdata[) {
//                        
//                    }
                }
            }
        }
    }
    
}

}
