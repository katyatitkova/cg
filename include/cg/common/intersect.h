#pragma once

#include <algorithm>
#include <boost/range.hpp>
#include <boost/range/value_type.hpp>

namespace cg
{
	namespace common
	{
		template<class Range, class OutIter>
		OutIter intersect(Range r, typename boost::range_value<Range>::type s,
		                  typename boost::range_value<Range>::type f, OutIter out)
		{
		    return std::copy(lower_bound(boost::begin(r), boost::end(r), s), 
		    				 lower_bound(boost::begin(r), boost::end(r), f), out);
		}
	}
}

