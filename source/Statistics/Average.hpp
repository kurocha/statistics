//
//  Average.hpp
//  This file is part of the "Numerics" project and released under the MIT License.
//
//  Created by Samuel Williams on 31/10/08.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Numerics/Number.hpp>

namespace Statistics
{
	/// This class can assist in the calculation of mathematical averages.
	template <typename NumericT>
	class Average
	{
	protected:
		/// The number of samples taken so far.
		std::size_t _count = 0;
		
		/// The current total. Might overflow.
		NumericT _total = 0;

		/// Add one or more measurements to the average.
		void add(const NumericT & value, const std::size_t & count)
		{
			_count += count;
			_total += value;
		}

	public:
		Average() {}
		
		Average(std::size_t count, NumericT total) : _count(count), _total(total) {}

		/// Add a single sample to the average.
		void add(const NumericT & measurement)
		{
			add(measurement, 1);
		}

		/// Add samples from another instance of Average.
		void add(const Average<NumericT> & other)
		{
			add(other._total, other._count);
		}

		/// Calculate the average value.
		/// @returns The average value.
		NumericT value() const
		{
			if (_count == 0) return 0;

			return _total / static_cast<NumericT>(_count);
		}

		/// The number of samples taken.
		std::size_t count() const
		{
			return _count;
		}

		/// Helper for adding a sample. Same as add_sample.
		void operator+=(const NumericT & measurement)
		{
			add(measurement);
		}

		/// Helper for adding a samples. Same as add_samples.
		void operator+=(const Average<NumericT> & other)
		{
			add(other);
		}
	};
}
