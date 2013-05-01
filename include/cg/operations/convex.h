#pragma once

#include <cg/primitives/contour.h>
#include <cg/operations/orientation/points_orientation.h>

namespace cg
{
   // c is ccw contour
   inline bool convex(contour_2 const & c)
   {
      for (size_t i = 1; i < c.size() - 1; ++i)
      {
         if (cg::orientation(c[i - 1], c[i], c[i + 1]) != cg::CG_LEFT)
         {
            return false;
         }
      }
      if (cg::orientation(c[c.size() - 1], c[0], c[1]) != cg::CG_LEFT ||
          cg::orientation(c[c.size() - 2], c[c.size() - 1], c[0]) != cg::CG_LEFT)
      {
         return false;
      }
      return true;
   }
}
