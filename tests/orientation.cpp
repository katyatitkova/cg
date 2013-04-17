#include <gtest/gtest.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/enum.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>

#include <cg/operations/orientation.h>
#include <misc/random_utils.h>

#include "random_utils.h"
#include <cg/primitives/contour.h>

using namespace util;

TEST(orientation, DISABLED_uniform_line)
{
   uniform_random_real<double, std::mt19937> distr(-(1LL << 53), (1LL << 53));

   std::vector<cg::point_2> pts = uniform_points(1000);
   for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
   {
      cg::point_2 a = pts[l];
      cg::point_2 b = pts[ln];

      CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> a_cgal(a.x, a.y);
      CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> b_cgal(b.x, b.y);

      for (size_t k = 0; k != 1000; ++k)
      {
         double t = distr();
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

TEST(orientation, DISABLED_contour)
{
    uniform_random_int<int, std::mt19937> size_distr(5, 1000);
    for (int k = 0; k < 10000; ++k)
    {
        std::vector<cg::point_2> pts = uniform_points(size_distr());
        cg::contour_2 con(pts);
        int res = 0;
        if (cg::orientation(con) == cg::CG_CLOCKWISE)
        {
            res = 1;
        }
        std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_pts;
        for (size_t i = 0; i < pts.size(); ++i)
        {
            cgal_pts.push_back(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(pts[i].x, pts[i].y));
        }
        CGAL::Polygon_2<CGAL::Exact_predicates_exact_constructions_kernel> pol(cgal_pts.begin(), cgal_pts.end());
        int cgal_res = 0;
        if (CGAL::orientation_2(pol.vertices_begin(), pol.vertices_end()) == CGAL::CLOCKWISE)
        {
            cgal_res = 1;
        }
        EXPECT_EQ(res, cgal_res);
    }
}
