//
//  dmapgci.cpp
//  NCL_func_cxx
//
//  Created by 邓浩 on 2021/12/18.
//
#include <algorithm>
#include <cmath>
#include "dmapgci.h"

namespace NCL_cxx {

/// 计算两点的大圆距离
/// @param lat1 第一个点的纬度
/// @param lon1 第一个点的经度
/// @param lat2 第二个点的纬度
/// @param lon2 第二个点的经度
/// @param unitsIndex 输出的单位的index. 1: radians, 2: degrees, 3: meters, 4: kilometers, 5: *not used*
double dgcdist(double lat1, double lon1, double lat2, double lon2, int unitsIndex) {
    const double units[5] = {1.0, 57.29577995691645, 6371220.0, 6371.2200, 0.0};
    const double rad = 0.01745329238474369;
    
    if (lat1 == lat2 && lon1 == lon2)
        return 0.0;
    
    double lat1R = lat1 * rad;
    double lat2R = lat2 * rad;
    double lonR = std::min({abs(lon1-lon2), abs(360.0-lon1+lon2), abs(360.0-lon2+lon1)}) * rad;
    
    double ret = atan2(sqrt(pow(cos(lat2R)*sin(lonR), 2) +
                            pow(cos(lat1R)*sin(lat2R)-sin(lat1R)*cos(lat2R)*cos(lonR), 2)
                            ),sin(lat1R)*sin(lat2R) + cos(lat1R)*cos(lat2R)*cos(lonR)
                       ) * units[unitsIndex];
    return ret;
}

}
