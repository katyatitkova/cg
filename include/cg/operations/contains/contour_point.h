#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/point.h>
#include <cg/primitives/triangle.h>
#include <cg/operations/orientation/points_orientation.h>
#include <cg/operations/contains/triangle_point.h>

#include <algorithm>

namespace cg
{

   // c is convex contour ccw orientation
   inline bool convex_contains(contour_2 const & c, point_2 const & p)
   {
      auto it = std::lower_bound(c.begin() + 2, c.end(), p,
                                 [&c] (point_2 const & left, point_2 const & right)
      { return orientation(c[0], left, right) == CG_LEFT; });
      if (it == c.end())
      {
         return false;
      }
      return contains(triangle_2(*it, *(it - 1), c[0]), p);
   }

/*
   // c is ordinary contour
   inline bool contains(contour_2 const & c, point_2 const & q);
   */
}
