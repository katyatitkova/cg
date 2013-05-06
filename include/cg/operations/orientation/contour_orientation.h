#pragma once

#include <algorithm>

#include <cg/primitives/point.h>
#include <cg/primitives/contour.h>
#include <cg/operations/orientation/points_orientation.h>

#include <boost/optional.hpp>

namespace cg
{
   template<class Scalar>
   inline orientation_contour_t orientation(contour_2t<Scalar> & c)
   {
       if (c.get_orientation() != CG_NULL)
       {
           return c.get_orientation();
       }
       auto circulator = c.circulator(std::min_element(c.begin(), c.end()));
       point_2t<Scalar> const & point = *circulator;
       point_2t<Scalar> const & prev = *(--circulator);
       ++circulator;
       point_2t<Scalar> const & next = *(++circulator);
       if (orientation(point, prev, next) == CG_RIGHT)
       {
           c.set_orientation(CG_COUNTERCLOCKWISE);
           return CG_COUNTERCLOCKWISE;
       }
       c.set_orientation(CG_CLOCKWISE);
       return CG_CLOCKWISE;
   }
}
