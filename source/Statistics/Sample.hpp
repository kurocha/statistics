//
//  Sample.hpp
//  This file is part of the "Statistics" project and released under the MIT License.
//
//  Created by Samuel Williams on 1/10/2013.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Average.hpp"

#include <vector>

namespace Statistics
{
	using namespace Numerics;
	
	template <typename NumericT = RealT>
	class Sample : protected Average<NumericT>
	{
	protected:
		NumericT _minimum = 0, _maximum = 0;
		std::vector<NumericT> _measurements;

	public:
		Sample() {}

		const std::vector<NumericT> & measurements() const
		{
			return _measurements;
		}

		void add(const NumericT & measurement)
		{
			if (this->count() == 0 || measurement < _minimum)
				_minimum = measurement;

			if (this->count() == 0 || measurement > _maximum)
				_maximum = measurement;

			Average<NumericT>::add(measurement);

			_measurements.push_back(measurement);
		}

		void add(const Sample & other)
		{
			for (const auto & measurement : other._measurements)
				add(measurement);
		}

		using Average<NumericT>::count;

		NumericT average() { return this->value(); }

		const NumericT & minimum() { return _minimum; }
		const NumericT & maximum() { return _maximum; }

		// Computes Sample Variance, s^2.
		Number<NumericT> variance()
		{
			if (this->count() < 2) return 0;
			
			Average<NumericT> squared_difference;
			auto mean = this->value();
			
			NumericT total = 0;
			
			for (auto & measurement : _measurements) {
				auto difference = (measurement - mean);
				
				total += difference*difference;
			}

			return total / (_measurements.size() - 1);
		}

		// Computes Population Standard Deviation, σ
		auto standard_deviation()
		{
			return this->variance().square_root();
		}

		auto standard_error()
		{
			return standard_deviation() / number(this->count()).square_root();
		}
	};
	
	extern template class Sample<float>;
	extern template class Sample<double>;
}
