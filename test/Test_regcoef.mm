//
//  Test_regcoef.m
//  Test_regcoef
//
//  Created by 邓浩 on 2021/11/6.
//

#import <XCTest/XCTest.h>
#include "regcoef.h"

@interface Test_regcoef : XCTestCase

@end

@implementation Test_regcoef

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_regcoef {
    double x[] = {1190.,1455.,1550.,-999.0,1730.,1745.,1770., 1900., 1920., 1960., 2295., 2335., 2490., 2720.,2710.,2530.,2900.,2760.,3010.};
    double y[] = {1115.,1425.,1515.,-999.0,1795.,1715.,1710., 1830., 1920., 1970., 2300., 2280.,2520.,2630.,2740.,2390.,2800.,2630.,2970.};
    
    auto [rCoef, tVal, rStd, yInt, nPtUsed, ier] = NCL_cxx::regcoef<double>(x, y, 19, -999, -999);
    XCTAssertEqualWithAccuracy(rCoef, 0.9745615, 1e-6);
    XCTAssertEqualWithAccuracy(tVal, 38.74285954, 1e-6);
    XCTAssertEqualWithAccuracy(rStd, 0.02515461, 1e-6);
    XCTAssertEqualWithAccuracy(yInt, 15.35228249, 1e-6); // use double!
    XCTAssertEqual(nPtUsed, 18);
    XCTAssertEqual(ier, 0);
    
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
//        [self test_regcoef];
    }];
}

@end
