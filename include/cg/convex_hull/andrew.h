#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation/points_orientation.h>
#include <cg/convex_hull/graham.h>

#include <algorithm>
#include <iostream>
#include <iterator>

namespace cg
{
   template <class BidIter>
   BidIter andrew_hull(BidIter p, BidIter q)
   {
      if (q - p == 1)
      {
         return q;
      }

      std::iter_swap(p, std::min_element(p, q));
      std::iter_swap(p + 1, std::max_element(p, q));

      if (*p > *(p + 1))
      {
         return p;
      }

      BidIter it = std::partition(p + 2, q, [p] (point_2 const & a)
      {
                   return (orientation(*p, *(p + 1), a) != CG_LEFT);
   });

      std::iter_swap(p + 1, it - 1);

      std::sort(p + 1, it);

      std::sort(it, q, std::greater<point_2>());

      return contour_graham_hull(p, q);
   }
}
