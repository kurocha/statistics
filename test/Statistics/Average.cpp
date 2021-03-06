//
//  Average.cpp
//  This file is part of the "Numerics" project and released under the MIT License.
//
//  Created by Samuel Williams on 4/11/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Statistics/Average.hpp>

namespace Statistics
{
	UnitTest::Suite AverageTestSuite {
		"Statistics::Average",
		
		{"it can compute average of multiple samples",
			[](UnitTest::Examiner & examiner) {
				Average<int> s;
				s.add(5);
				s.add(15);

				examiner.check_equal(s.value(), 10);

				Average<int> q;
				q.add(20);
				q.add(20);
				q.add(s);

				examiner.check_equal(q.value(), 15);
			}
		},
	};
}
