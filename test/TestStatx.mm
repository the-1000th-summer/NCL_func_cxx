//
//  TestStatx.m
//  TestStatx
//
//  Created by 邓浩 on 2021/11/2.
//

#import <XCTest/XCTest.h>
#include <string>
#include "statx.h"

@interface TestStatx : XCTestCase

@end

@implementation TestStatx

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_stat2 {
    float x[] = {1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999};
    auto [xMean, xVar, xStd, nPtUsed, ier] = NCL_cxx::stat2(x, 12, -999);
    XCTAssertEqualWithAccuracy(xMean, 5.9, 1e-6);
    XCTAssertEqualWithAccuracy(xVar, 12.1, 1e-6);
    XCTAssertEqual(nPtUsed, 10);
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
//        [self testExample];
    }];
    
}

@end
