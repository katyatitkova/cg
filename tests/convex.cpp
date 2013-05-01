#include <gtest/gtest.h>

#include <cg/operations/convex.h>

#include <CGAL/Polygon_2.h>

#include <misc/random_utils.h>

#include "test.h"
#include "random_utils.h"

namespace tests_convex_convex
{
   void test()
   {
      util::uniform_random_int<int, std::random_device> size_distr(3, 50);
      for (size_t k = 0; k < 10; ++k)
      {
         CGAL::Polygon_2<CGAL::Exact_predicates_exact_constructions_kernel> cgal_pol = generate_simple_polygon(size_distr());
         if (cgal_pol.orientation() == CGAL::CLOCKWISE)
         {
            std::reverse(cgal_pol.vertices_begin(), cgal_pol.vertices_end());
         }
         std::vector<cg::point_2> pts;
         for (size_t i = 0; i < cgal_pol.size(); ++i)
         {
            pts.push_back(cg::point_2(CGAL::to_double(cgal_pol[i].x()), CGAL::to_double(cgal_pol[i].y())));
         }
         cg::contour_2 pol(pts);
         EXPECT_EQ(cg::convex(pol), cgal_pol.is_convex());
      }
   }
}

TEST(convex, DISABLED_convex)
{
   void (*test_case)() = tests_convex_convex::test;
   test(test_case);
}
