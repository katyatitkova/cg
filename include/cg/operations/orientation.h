#pragma once

#include <algorithm>

#include <cg/primitives/point.h>
#include <cg/primitives/contour.h>
#include <boost/numeric/interval.hpp>
#include <gmpxx.h>

#include <boost/optional.hpp>

namespace cg
{
   enum orientation_t
   {
      CG_RIGHT = -1,
      CG_COLLINEAR = 0,
      CG_LEFT = 1,
      CG_CLOCKWISE = 2,
      CG_COUNTERCLOCKWISE = 3
   };

   inline bool opposite(orientation_t a, orientation_t b)
   {
      if (a == CG_COLLINEAR || b == CG_COLLINEAR)
         return false;

      return a == -b;
   }

   struct orientation_d
   {
      boost::optional<orientation_t> operator() (point_2 const & a, point_2 const & b, point_2 const & c) const
      {
         double l = (b.x - a.x) * (c.y - a.y);
         double r = (b.y - a.y) * (c.x - a.x);
         double res = l - r;
         double eps = (fabs(l) + fabs(r)) * 8 * std::numeric_limits<double>::epsilon();

         if (res > eps)
            return CG_LEFT;

         if (res < -eps)
            return CG_RIGHT;

         return boost::none;
      }
   };

   struct orientation_i
   {
      boost::optional<orientation_t> operator() (point_2 const & a, point_2 const & b, point_2 const & c) const
      {
         typedef boost::numeric::interval_lib::unprotect<boost::numeric::interval<double> >::type interval;

         boost::numeric::interval<double>::traits_type::rounding _;
         interval res =   (interval(b.x) - a.x) * (interval(c.y) - a.y)
                        - (interval(b.y) - a.y) * (interval(c.x) - a.x);

         if (res.lower() > 0)
            return CG_LEFT;

         if (res.upper() < 0)
            return CG_RIGHT;

         if (res.upper() == res.lower())
            return CG_COLLINEAR;

         return boost::none;
      }
   };

   struct orientation_r
   {
      boost::optional<orientation_t> operator() (point_2 const & a, point_2 const & b, point_2 const & c) const
      {
         mpq_class res =   (mpq_class(b.x) - a.x) * (mpq_class(c.y) - a.y)
                         - (mpq_class(b.y) - a.y) * (mpq_class(c.x) - a.x);

         int cres = cmp(res, 0);

         if (cres > 0)
            return CG_LEFT;

         if (cres < 0)
            return CG_RIGHT;

         return CG_COLLINEAR;
      }
   };

   inline orientation_t orientation(point_2 const & a, point_2 const & b, point_2 const & c)
   {
      if (boost::optional<orientation_t> v = orientation_d()(a, b, c))
         return *v;

      if (boost::optional<orientation_t> v = orientation_i()(a, b, c))
         return *v;

      return *orientation_r()(a, b, c);
   }

   template<class Scalar>
   inline orientation_t orientation(cg::contour_2t<Scalar> const & contour)
   {
       auto circulator = contour.circulator(std::min_element(contour.begin(), contour.end()));
       point_2t<Scalar> const & point = *circulator;
       point_2t<Scalar> const & prev = *(--circulator);
       ++circulator;
       point_2t<Scalar> const & next = *(++circulator);
       if (orientation(point, prev, next) == CG_RIGHT)
       {
           return CG_COUNTERCLOCKWISE;
       }
       return CG_CLOCKWISE;
   }
}
