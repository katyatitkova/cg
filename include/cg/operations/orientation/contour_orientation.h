#pragma once

#include <algorithm>

#include <cg/primitives/point.h>
#include <cg/primitives/contour.h>

#include <boost/optional.hpp>

namespace cg
{
   template<class Scalar>
   inline orientation_contour_t orientation(cg::contour_2t<Scalar> & contour)
   {
       if (contour.get_orientation() != cg::CG_NULL)
       {
           return contour.get_orientation();
       }
       auto circulator = contour.circulator(std::min_element(contour.begin(), contour.end()));
       cg::point_2t<Scalar> const & point = *circulator;
       cg::point_2t<Scalar> const & prev = *(--circulator);
       ++circulator;
       cg::point_2t<Scalar> const & next = *(++circulator);
       if (orientation(point, prev, next) == cg::CG_RIGHT)
       {
           contour.set_orientation(CG_COUNTERCLOCKWISE);
           return CG_COUNTERCLOCKWISE;
       }
       contour.set_orientation(CG_CLOCKWISE);
       return CG_CLOCKWISE;
   }
}
