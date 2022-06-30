//
//  wrf_user.h
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/25.
//

#ifndef wrf_user_h
#define wrf_user_h

namespace NCL_cxx {

void wrf_interp_3d_z(const double* const data3d, double* const out2d, const double* const zdata, const int* const levels, int nx, int ny, int nz, int nlev, double missingVal);

}

#endif /* wrf_user_h */
