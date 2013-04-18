#pragma once

#include <iterator>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>

template<class RanIter, class OutIter>
OutIter intersect_slow(RanIter p, RanIter q, typename std::iterator_traits<RanIter>::value_type s,
                       typename std::iterator_traits<RanIter>::value_type f, OutIter out)
{
   return boost::copy(std::make_pair(p, q) | boost::adaptors::filtered(
                         [&s, &f] (typename std::iterator_traits<RanIter>::value_type x) { return (x > s || x == s) && x < f; }), out);
}
