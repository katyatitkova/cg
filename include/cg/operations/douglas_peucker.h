#pragma once

#include <iterator>
#include <limits>
#include <cg/primitives/point.h>
#include <iostream>

namespace cg
{
   double distance_point_point_sq(point_2 a, point_2 b)
   {
      return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
   }

   double distance_point_segment_sq(point_2 a, point_2 b, point_2 p)
   {
      double area = std::abs((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
      double ab_length_sq = distance_point_point_sq(a, b);
      double h_sq = area * area / ab_length_sq;
      double ap_length_sq = distance_point_point_sq(a, p);
      double bp_length_sq = distance_point_point_sq(b, p);
      if (ap_length_sq + ab_length_sq < bp_length_sq ||
          bp_length_sq + ab_length_sq < ap_length_sq)
         return std::min(ap_length_sq, bp_length_sq);
      return h_sq;
   }

   template<class BidIter, class OutIter>
   OutIter simplify(BidIter p, BidIter q, double eps, OutIter out)
   {
      BidIter begin = p;
      BidIter end = q;
      --end;
      if (begin == end)
      {
         *out++ = *begin;
         return out;
      }
      BidIter worst = begin;
      ++worst;
      if (worst == end)
      {
         *out++ = *begin;
         *out++ = *end;
         return out;
      }
      double worst_distance_sq = distance_point_segment_sq(*begin, *end, *worst);
      BidIter t = worst;
      ++t;
      for (; t != end; ++t)
      {
         double d = distance_point_segment_sq(*begin, *end, *t);
         if (d  > worst_distance_sq)
         {
            worst = t;
            worst_distance_sq = d;
         }
      }
      if (worst_distance_sq > eps * eps)
         return simplify(worst, q, eps, simplify(begin, worst, eps, out));
      *out++ = *begin;
      *out++ = *end;
      return out;
   }
}
