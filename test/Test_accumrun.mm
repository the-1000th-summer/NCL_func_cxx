//
//  Test_accumrun.m
//  Test_accumrun
//
//  Created by 邓浩 on 2021/11/4.
//

#import <XCTest/XCTest.h>
#include "accumrun.h"

@interface Test_accumrun : XCTestCase

@end

@implementation Test_accumrun

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_dacumrun {
    float x[] = {1,2,3,4,5,7,-23};
    auto xAcc = NCL_cxx::dacumrun<float>(x, 7, -999, 3, 0);
    float correct_xAcc[] = {-999,-999, 6, 9, 12, 16, -11};
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc[i], correct_xAcc[i]);
    }
    
    NCL_cxx::dacumrun<float>(x, 7, -999, 3, 1, xAcc.data());
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc[i], correct_xAcc[i]);
    }
    
    float x_2[] = {1,2,-999,4,5,7,-999, 2, -9, 5};
    auto xAcc_2 = NCL_cxx::dacumrun<float>(x_2, 10, -999, 3, 0);
    float correct_xAcc_2_1[] = {-999,-999,-999,-999,-999, 16,-999,-999,-999, -2};
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc_2[i], correct_xAcc_2_1[i]);
    }
    
    float correct_xAcc_2_2[] = {-999,-999, 3, 6, 9, 16, 12, 9, -7, -2};
    NCL_cxx::dacumrun<float>(x_2, 10, -999, 3, 1, xAcc_2.data());
    for (int i = 0; i < 7; ++i) {
        XCTAssertEqual(xAcc_2[i], correct_xAcc_2_2[i]);
    }
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
