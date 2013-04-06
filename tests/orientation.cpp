#include <gtest/gtest.h>

#include <cg/operations/orientation.h>
#include "random_utils.h"
#include <cg/primitives/contour.h>

TEST(orientation, DISABLED_uniform_line)
{
   boost::random::mt19937 gen;
   boost::random::uniform_real_distribution<> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(1000);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr(gen);
         cg::point_2 c = a + t * (b - a);

         EXPECT_EQ(cg::orientation(a, b, c), *cg::orientation_r()(a, b, c));
      }
   }
}

TEST(orientation, contour_orientation)
{
    std::vector<cg::point_2> v = {cg::point_2(0, 0), cg::point_2(0, 4), cg::point_2(4, 4), cg::point_2(4, 0)};
    EXPECT_EQ(cg::contour_orientation(cg::contour_2t<double>(v)), cg::CG_RIGHT);
    v = {cg::point_2(4, 0), cg::point_2(4, 4), cg::point_2(0, 4), cg::point_2(0, 0)};
    EXPECT_EQ(cg::contour_orientation(cg::contour_2t<double>(v)), cg::CG_LEFT);
}
