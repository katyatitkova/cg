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


   // c is ordinary contour
   template<typename Scalar>
   inline bool contains(contour_2t<Scalar> const & a, point_2t<Scalar> const & b)
   {
      int num_intersections = 0;
      for (size_t pr = a.vertices_num() - 1, cur = 0; cur != a.vertices_num(); pr = cur++) {
         point_2t<Scalar> min_point = a[pr];
         point_2t<Scalar> max_point = a[cur];
         if (min_point.y > max_point.y)
            std::swap(min_point, max_point);
         orientation_t orient = orientation(min_point, max_point, b);
         if (orient == CG_COLLINEAR && std::min(min_point, max_point) <= b && b <= std::max(min_point, max_point))
            return true;
         if (max_point.y <= b.y || min_point.y > b.y)
            continue;
         if (orient == CG_LEFT)
            num_intersections++;
      }
      return num_intersections % 2;
   }
}
