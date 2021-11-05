//
//  TestStatx.m
//  TestStatx
//
//  Created by 邓浩 on 2021/11/2.
//

#import <XCTest/XCTest.h>
#include <iostream>
#include <string>
#include "statx.h"
#include "accumrun.h"
#include "rmsd.h"
#include "rmStndx_dp.h"

@interface Test_statW : XCTestCase

@end

@implementation Test_statW

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    std::cout << "start!!!" << std::endl;
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_stat2 {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    auto [xMean, xVar, xStd, nPtUsed, ier] = NCL_cxx::stat2<float>(x, 12, -999.0);
    XCTAssertEqualWithAccuracy(xMean, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVar, 12.1, 1e-6);
    XCTAssertEqualWithAccuracy(xStd, 3.478505, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);

    NCL_cxx::stat2<float>(x, 12, -999.0, xMean, xVar, xStd, nPtUsed, ier);
    XCTAssertEqualWithAccuracy(xMean, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVar, 12.1, 1e-6);
    XCTAssertEqualWithAccuracy(xStd, 3.478505, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);
}

- (void)test_stat4 {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    auto [xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier] = NCL_cxx::stat4<float>(x, 12, -999);
    XCTAssertEqualWithAccuracy(xMean, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVar, 12.1, 1e-6);
    XCTAssertEqualWithAccuracy(xStd, 3.478505, 1e-6);
    XCTAssertEqualWithAccuracy(xSkew, 0.075267, 1e-6);
    XCTAssertEqualWithAccuracy(xKurt, -1.659151, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);
    
    NCL_cxx::stat4<float> (x, 12, -999, xMean, xVar, xStd, xSkew, xKurt, nPtUsed, ier);
    XCTAssertEqualWithAccuracy(xMean, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVar, 12.1, 1e-6);
    XCTAssertEqualWithAccuracy(xStd, 3.478505, 1e-6);
    XCTAssertEqualWithAccuracy(xSkew, 0.075267, 1e-6);
    XCTAssertEqualWithAccuracy(xKurt, -1.659151, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);
}

- (void)test_medmrng {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    auto [xMedian, xMidRange, xRange, nPtUsed, ier] = NCL_cxx::medmrng<float>(x, 12, -999);
    XCTAssertEqualWithAccuracy(xMedian, 5.5, 1e-6);
    XCTAssertEqualWithAccuracy(xMidRange, 6, 1e-6);
    XCTAssertEqualWithAccuracy(xRange, 10, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);
    
    x[0] = -999;
    NCL_cxx::medmrng<float>(x, 12, -999, xMedian, xMidRange, xRange, nPtUsed, ier);
    XCTAssertEqualWithAccuracy(xMedian, 6, 1e-6);
    XCTAssertEqualWithAccuracy(xMidRange, 6.5, 1e-6);
    XCTAssertEqualWithAccuracy(xRange, 9, 1e-6);
    XCTAssertEqual(nPtUsed, 9);
    XCTAssertEqual(ier, 0);
}

- (void)test_stat2t {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    auto [xMeanT, xVarT, xStdT, nPtUsed, ier] = NCL_cxx::stat2t<float>(x, 12, -999, 0.0);
    XCTAssertEqualWithAccuracy(xMeanT, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVarT, 12.1, 1e-6);
    XCTAssertEqualWithAccuracy(xStdT, 3.478505, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
    XCTAssertEqual(ier, 0);
    
    NCL_cxx::stat2t<float>(x, 12, -999, 0.5, xMeanT, xVarT, xStdT, nPtUsed, ier);
    XCTAssertEqualWithAccuracy(xMeanT, 5.833333, 1e-6);
    XCTAssertEqualWithAccuracy(xVarT, 5.366667, 1e-6);
    XCTAssertEqualWithAccuracy(xStdT, 2.316607, 1e-6);
    XCTAssertEqual(nPtUsed, 6);
    XCTAssertEqual(ier, 0);
}

- (void)test_esauto {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    int ier;
    auto acv = std::make_unique<float[]>(10);
    auto acr = std::make_unique<float[]>(10);
    NCL_cxx::esauto<float>(x, 12, -999, 9, acv.get(), acr.get(), ier);
    
    XCTAssertEqual(ier, 0);
    float correct_acv[] = {12.1, 11.097143, 8.111667, 4.332, -0.5875, -3.9125, -9.853333, -14.653334, -22.985, -39.98};
    float correct_acr[] = {1, 0.9171193, 0.6703857, 0.3580165, -0.04855372, -0.3233471, -0.8143251, -1.211019, -1.899587, -3.304132};
    for (int i = 0; i < 10; ++i) {
        XCTAssertEqualWithAccuracy(acv[i], correct_acv[i], 1e-6);
        XCTAssertEqualWithAccuracy(acr[i], correct_acr[i], 1e-6);
    }
}

- (void)test_escros {
    double x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    double y[] = {-999,11.,10.,9.,8.,-999,6.,5.,4.,3.,2.,1.};
    int ier;
    auto ccv = std::make_unique<double[]>(10);
    auto ccr = std::make_unique<double[]>(10);
    
    
    NCL_cxx::escros<double>(x, x, 12, -999, -999, 9, ccv.get(), ccr.get(), ier);
    XCTAssertEqual(ier, 0);
    double correct_ccv_1[] = {12.1, 11.09714285714286, 8.111666666666666, 4.332, -0.5875, -3.9125, -9.853333333333333, -14.65333333333333, -22.985, -39.98};
    double correct_ccr_1[] = {1, 0.9171192443919719, 0.6703856749311295, 0.3580165289256199, -0.04855371900826447, -0.3233471074380166, -0.8143250688705236, -1.211019283746557, -1.899586776859504, -3.30413223140496};
    for (int i = 0; i < 10; ++i) {
        XCTAssertEqualWithAccuracy(ccv[i], correct_ccv_1[i], 1e-10);
        XCTAssertEqualWithAccuracy(ccr[i], correct_ccr_1[i], 1e-10);
    }
    
    NCL_cxx::escros<double>(x, y, 12, -999, -999, 9, ccv.get(), ccr.get(), ier);
    XCTAssertEqual(ier, 0);
    double correct_ccv_2[] = {-11.30285714285714, -13.48875, -10.96, -7.721666666666665, -3.548, 2.0125, 3.412, 8.0125, 13.74666666666667, 21.815};
    double correct_ccr_2[] = {-0.9341204250295162, -1.114772727272727, -0.9057851239669422, -0.6381542699724517, -0.2932231404958677, 0.1663223140495869, 0.2819834710743804, 0.6621900826446284, 1.136088154269973, 1.802892561983472};
    for (int i = 0; i < 10; ++i) {
        XCTAssertEqualWithAccuracy(ccv[i], correct_ccv_2[i], 1e-10);
        XCTAssertEqualWithAccuracy(ccr[i], correct_ccr_2[i], 1e-10);
    }
}

- (void)test_dacumrun {
    float x[] = {1,2,3,4,5,7,-23};
    auto xAcc = NCL_cxx::acumrun<float>(x, 7, -999, 3, 0);
    float correct_xAcc[] = {-999,-999, 6, 9, 12, 16, -11};
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc[i], correct_xAcc[i]);
    }
    
    NCL_cxx::acumrun<float>(x, 7, -999, 3, 1, xAcc.data());
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc[i], correct_xAcc[i]);
    }
    
    float x_2[] = {1,2,-999,4,5,7,-999, 2, -9, 5};
    auto xAcc_2 = NCL_cxx::acumrun<float>(x_2, 10, -999, 3, 0);
    float correct_xAcc_2_1[] = {-999,-999,-999,-999,-999, 16,-999,-999,-999,-2};
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc_2[i], correct_xAcc_2_1[i]);
    }
    
    float correct_xAcc_2_2[] = {-999,-999, 3, 6, 9, 16, 12, 9, -7, -2};
    NCL_cxx::acumrun<float>(x_2, 10, -999, 3, 1, xAcc_2.data());
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc_2[i], correct_xAcc_2_2[i]);
    }
}

- (void)test_rmsd {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    float y[] = {-999,11.,10.,9.,8.,-999,6.,5.,4.,3.,2.,1.};
    
    auto [xyRmsd, nPtUsed, ier] = NCL_cxx::rmsd<float>(x, y, 12, -999, -999);
    XCTAssertEqualWithAccuracy(xyRmsd, 6.40312433, 1e-6);
    XCTAssertEqual(nPtUsed, 8);
    XCTAssertEqual(ier, 0);
    
    NCL_cxx::rmsd<float>(x, y, 12, -999, -999, xyRmsd, nPtUsed, ier);
    XCTAssertEqualWithAccuracy(xyRmsd, 6.40312433, 1e-6);
    XCTAssertEqual(nPtUsed, 8);
    XCTAssertEqual(ier, 0);
}

- (void)test_rmvmean {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    
    int ier = NCL_cxx::rmvmean<float>(x, 12, -999);
    float correct_x[] = {-4.9, -3.9, -2.9, -1.9, -0.9, 0.1, -999, 2.1, 3.1, 4.1, 5.1, -999};
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x[i], correct_x[i], 1e-6);
    }
    
    float x_2[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    
    NCL_cxx::rmvmean<float>(x_2, 12, -999, ier);
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x_2[i], correct_x[i], 1e-6);
    }
}

- (void)test_rmvmed {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    int ier = NCL_cxx::rmvmed<float>(x, 12, -999);
    
    float correct_x[] = {-4.5, -3.5, -2.5, -1.5, -0.5, 0.5, -999, 2.5, 3.5, 4.5, 5.5, -999};
    XCTAssertEqual(ier, 0);
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x[i], correct_x[i], 1e-6);
    }
    
    float x_2[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    NCL_cxx::rmvmed<float>(x_2, 12, -999, ier);
    XCTAssertEqual(ier, 0);
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x_2[i], correct_x[i], 1e-6);
    }
}

- (void)test_xstnd {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    int ier = NCL_cxx::xstnd<float>(x, 12, -999, 0);
    
    float correct_x_1[] = {-1.408651, -1.121171, -0.8336914, -0.5462116, -0.2587318, 0.02874798, -999, 0.6037076, 0.8911874, 1.178667, 1.466147, -999};
    XCTAssertEqual(ier, 0);
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x[i], correct_x_1[i], 1e-6);
    }
    
    float x_2[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    NCL_cxx::xstnd<float>(x_2, 12, -999, 1, ier);
    float correct_x_2[] = {-1.484848, -1.181818, -0.8787879, -0.5757576, -0.2727273, 0.03030303, -999, 0.6363636, 0.9393939, 1.242424, 1.545455, -999};
    XCTAssertEqual(ier, 0);
    for (int i = 0; i < 12; ++i) {
        XCTAssertEqualWithAccuracy(x_2[i], correct_x_2[i], 1e-6);
    }
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
//        [self testExample];
    }];
    
}

@end
