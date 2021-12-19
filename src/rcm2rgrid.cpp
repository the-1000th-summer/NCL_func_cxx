//
//  rcm2rgrid.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//
#include <cmath>
#include <algorithm>
#include "rcm2rgrid.h"
#include "dmapgci.h"
#include "linint2.h"

namespace NCL_cxx {

namespace {

double fli(double z1, double z2, double slope) {
    return z1 + slope * (z2 - z1);
}
double fbli(double z1, double z2, double z3, double z4, double slpx, double slpy) {
    return fli(z1, z2, slpx) + slpy * (fli(z3, z4, slpx) - fli(z1, z2, slpx));
}

}

void rgrid2rcm(const double* const xi, const double* const yi, int xiSize, int yiSize, const double* const xo, const double* const yo, int xoSize, int yoSize, const double* const fi, float* const fo, double msgValue, int &ier) {
    
    ier = 0;
    if (xiSize <= 1 || yiSize <= 1 || xoSize <= 1 || yoSize <= 1) {
        ier = 1; return;
    }
    
    auto isMonoInc_yi = monoInc(yi, yiSize);
    if (!isMonoInc_yi) {
        ier = 1; return;
    }
    auto isMonoInc_xi = monoInc(xi, xiSize);
    if (!isMonoInc_xi) {
        ier = 1; return;
    }
    
    // Init to missing
    std::fill_n(fo, yoSize*xoSize, msgValue);
    
    // main loop [exact matches]
    constexpr double eps = 1e-3;
    int nExact = 0;
    for (int ny = 0; ny < yoSize; ++ny) {
        for (int nx = 0; nx < xoSize; ++nx) {
            [&] {                              // break out of nested loop using lambda
                for (int iy = 0; iy < yiSize; ++iy) {
                    for (int ix = 0; ix < xiSize; ++ix) {
                        if (xo[ny*xoSize+nx] >= (xi[ix]-eps) && xo[ny*xoSize+nx] <= (xi[ix]+eps) &&
                            yo[ny*xoSize+nx] >= (yi[iy]-eps) && yo[ny*xoSize+nx] <= (yi[iy]+eps)) {
                            fo[ny*xoSize+nx] = fi[iy*xiSize+ix];
                            ++nExact;
                            return;
                        }
                    }
                }
            }();
        }
    }
    // main loop [interpolation]
    constexpr int k = 1;
    for (int ny = 0; ny < yoSize; ++ny) {
        for (int nx = 0; nx < xoSize; ++nx) {
            for (int iy = 0; iy < yiSize - k; ++iy) {
                for (int ix = 0; ix < xiSize - k; ++ix) {
                    if (xo[ny*xoSize+nx] >= xi[ix] && xo[ny*xoSize+nx] < xi[ix+k] &&
                        yo[ny*xoSize+nx] >= yi[iy] && yo[ny*xoSize+nx] < yi[iy+k]) {
                        if (fo[ny*xoSize+nx] == msgValue) {   // 不是[exact matches]
                            auto fi_here = fi[iy*xiSize+ix];
                            auto fi_xP1 = fi[iy*xiSize+ix+k], fi_yP1 = fi[(iy+k)*xiSize+ix];
                            auto fi_xyP1 = fi[(iy+k)*xiSize+ix+k];
                            if (fi_here != msgValue && fi_xP1 != msgValue &&
                                fi_yP1 != msgValue && fi_xyP1 != msgValue) {
                                fo[ny*xoSize+nx] = fbli(fi_here, fi_xP1, fi_yP1, fi_xyP1,
                                                        (xo[ny*xoSize+nx]-xi[ix]) / (xi[ix+k]-xi[ix]),
                                                        (yo[ny*xoSize+nx]-yi[iy]) / (yi[iy+k]-yi[iy]));
                            } else {          // overkill
                                double fw[4] = { fi_here, fi_xP1, fi_yP1, fi_xyP1 };
                                double w[4] = {
                                    pow(1.0 / dgcdist(yo[ny*xoSize+nx],xo[ny*xoSize+nx],yi[iy],xi[ix],2), 2),
                                    pow(1.0 / dgcdist(yo[ny*xoSize+nx],xo[ny*xoSize+nx],yi[iy],xi[ix+k],2), 2),
                                    pow(1.0 / dgcdist(yo[ny*xoSize+nx],xo[ny*xoSize+nx],yi[iy+k],xi[ix],2), 2),
                                    pow(1.0 / dgcdist(yo[ny*xoSize+nx],xo[ny*xoSize+nx],yi[iy+k],xi[ix+k],2), 2)
                                };
                                
                                int nw = 0;
                                double sumf = 0.0, sumw = 0.0;
                                for (int i = 0; i < 4; ++i) {
                                    if (fw[i] != msgValue) {
                                        sumf += fw[i] * w[i];
                                        sumw += w[i];
                                        ++nw;
                                    }
                                }
                                
                                if (sumw > 0.0)
                                    fo[ny*xoSize+nx] = sumf / sumw;
                            }
                        }
                        goto interp_notExact_outer;
                    }
                }
            }
            interp_notExact_outer:
            ;
        }
    }
}


}

