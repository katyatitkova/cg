#include <gtest/gtest.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/enum.h>

#include <cg/operations/orientation.h>
#include "random_utils.h"
#include <cg/primitives/contour.h>

TEST(orientation, uniform_line)
{
   std::mt19937 gen;
   std::uniform_real_distribution<> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(1000);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> a_cgal(a.x, a.y);
      CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> b_cgal(b.x, b.y);

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr(gen);
         cg::point_2 c = a + t * (b - a);
         CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> c_cgal(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));

         CGAL::Orientation orient = CGAL::orientation(a_cgal, b_cgal, c_cgal);
         int cgal_res = 0;
         if (orient == CGAL::LEFT_TURN)
         {
             cgal_res = 1;
         }
         else
         {
             if (orient == CGAL::RIGHT_TURN)
             {
                 cgal_res = -1;
             }
         }

         EXPECT_EQ(cg::orientation(a, b, c), *cg::orientation_r()(a, b, c));
         EXPECT_EQ(cg::orientation(a, b, c), cgal_res);
      }
   }
}
