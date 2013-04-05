#pragma once

#include <iterator>
#include <algorithm>

namespace cg
{
	namespace common
	{
		template<class RanIter, class OutIter>
		OutIter intersect(RanIter p, RanIter q, typename std::iterator_traits<RanIter>::value_type s,
		                  typename std::iterator_traits<RanIter>::value_type f, OutIter out)
		{
		    return std::copy(lower_bound(p, q, s), lower_bound(p, q, f), out);
		}
	}
}
