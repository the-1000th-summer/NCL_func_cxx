//
//  Test_linmsg_dp.m
//  TestStatx
//
//  Created by 邓浩 on 2022/6/30.
//

#import <XCTest/XCTest.h>

#include <iostream>
#include "linmsg_dp.h"

@interface Test_linmsg_dp : XCTestCase

@end

@implementation Test_linmsg_dp

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_linmsg1 {
    double x[] = {190.,1455.,1550.,-999.,1745.,1770.,1900.,-999.,-999.,-999.,2335.,2490.,2720.,2710.,2530.,2900.,2760.,-999. };
    NCL_cxx::linmsg(x, 18, -999, 0, 18);
    XCTAssertEqual(x[3], 1647.5);
    XCTAssertEqual(x[7], 2008.75);
    XCTAssertEqual(x[8], 2117.5);
    XCTAssertEqual(x[9], 2226.25);
    XCTAssertEqual(x[17], -999);
}

- (void)test_linmsg2 {
    double ymsg = 1.e10;
    double x[] = {1115.,ymsg ,1515.,1794.,ymsg ,1710.,1830.,ymsg,ymsg,ymsg,2280.,2520.,2630.,ymsg ,ymsg ,2800.,ymsg ,ymsg};
    NCL_cxx::linmsg(x, 18, ymsg, -1, 2);
    XCTAssertEqual(x[1], 1315);
    XCTAssertEqual(x[4], 1752);
    XCTAssertEqual(x[7], ymsg);
    XCTAssertEqual(x[8], ymsg);
    XCTAssertEqual(x[9], ymsg);
    XCTAssertEqualWithAccuracy(x[13], 2686.67, 1e-2);
    XCTAssertEqualWithAccuracy(x[14], 2743.33, 1e-2);
    XCTAssertEqual(x[16], 2800);
    XCTAssertEqual(x[17], 2800);
}


- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
