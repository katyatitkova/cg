#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/operations/contains/segment_point.h>

#include <cg/io/point.h>

#include <misc/random_utils.h>

#include <iterator>
#include <iostream>

#include "random_utils.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Point_2.h>

template <class FwdIter>
bool is_convex_hull(FwdIter p, FwdIter c, FwdIter q)
{
   for (FwdIter t = boost::prior(c), s = p; s != c; t = s++)
   {
      for (FwdIter b = p; b != q; ++b)
      {
         switch (orientation(*t, *s, *b))
         {
         case cg::CG_RIGHT: return false;
         case cg::CG_COLLINEAR: return collinear_are_ordered_along_line(*t, *b, *s);
         case cg::CG_LEFT: continue;
         }
      }
   }

   return true;
}

TEST(convex_hull, DISABLED_simple)
{
   using cg::point_2;

   std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                    (point_2(1, 0))
                                                    (point_2(0, 1))
                                                    (point_2(2, 0))
                                                    (point_2(0, 2))
                                                    (point_2(3, 0));

   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::graham_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, DISABLED_uniform)
{
   using cg::point_2;

   std::vector<point_2> pts = uniform_points(10000000);
   EXPECT_TRUE(is_convex_hull(pts.begin(), cg::graham_hull(pts.begin(), pts.end()), pts.end()));
}

TEST(convex_hull, cgal)
{
   util::uniform_random_int<int, std::mt19937> size_distr(10, 100000);
   for (int q = 0; q < 1000; ++q)
   {
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_pts = uniform_cgal_points(size_distr());
      std::vector<cg::point_2> pts;
      for (size_t i = 0; i < cgal_pts.size(); ++i)
      {
         pts.push_back(cg::point_2(CGAL::to_double(cgal_pts[i].x()), CGAL::to_double(cgal_pts[i].y())));
      }
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_res;
      CGAL::convex_hull_2(cgal_pts.begin(), cgal_pts.end(), std::back_inserter(cgal_res));
      auto it_end = cg::graham_hull(pts.begin(), pts.end());
      EXPECT_EQ(cgal_res.size(), it_end - pts.begin());
      for (int i = 0; pts.begin() + i != it_end; ++i)
      {
         EXPECT_EQ(CGAL::to_double(cgal_res[i].x()), pts[i].x);
         EXPECT_EQ(CGAL::to_double(cgal_res[i].y()), pts[i].y);
      }
   }
}

TEST(convex_hull, andrew_cgal)
{
   util::uniform_random_int<int, std::mt19937> size_distr(10, 10000);
   for (int q = 0; q < 10000; ++q)
   {
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_pts = uniform_cgal_points(size_distr());
      std::vector<cg::point_2> pts;
      for (size_t i = 0; i < cgal_pts.size(); ++i)
      {
         pts.push_back(cg::point_2(CGAL::to_double(cgal_pts[i].x()), CGAL::to_double(cgal_pts[i].y())));
      }
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_res;
      CGAL::convex_hull_2(cgal_pts.begin(), cgal_pts.end(), std::back_inserter(cgal_res));
      auto it_end = cg::andrew_hull(pts.begin(), pts.end());
      EXPECT_EQ(cgal_res.size(), it_end - pts.begin());
      for (int i = 0; pts.begin() + i != it_end; ++i)
      {
         EXPECT_EQ(CGAL::to_double(cgal_res[i].x()), pts[i].x);
         EXPECT_EQ(CGAL::to_double(cgal_res[i].y()), pts[i].y);
      }
   }
}

TEST(convex_hull, DISABLED_andrew)
{
   std::vector<cg::point_2> pts;
   pts.push_back(cg::point_2(-210, 49));
   pts.push_back(cg::point_2(178, 50));
   pts.push_back(cg::point_2(-79, 153));
   pts.push_back(cg::point_2(-135, 56));
   auto it = cg::andrew_hull(pts.begin(), pts.end());
   EXPECT_TRUE(true);
}
