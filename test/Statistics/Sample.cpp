//
//  Distribution.cpp
//  This file is part of the "Numerics" project and released under the MIT License.
//
//  Created by Samuel Williams on 4/11/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Statistics/Sample.hpp>

namespace Statistics
{
	using namespace UnitTest::Expectations;
	
	UnitTest::Suite SampleTestSuite {
		"Statistics::Sample",
		
		{"it can calculate standard deviation",
			[](UnitTest::Examiner & examiner) {
				Sample<float> distribution;
				
				for (float s = 10; s <= 50; s += 10)
					distribution.add(s);
				
				examiner.expect(distribution.variance()).to(be == 250);
				examiner.expect(distribution.standard_deviation()).to(be_equivalent(15.8113883008));
				examiner.expect(distribution.standard_error()).to(be_equivalent(7.0710678118));
			}
		},
	};
}
