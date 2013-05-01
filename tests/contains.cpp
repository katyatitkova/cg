#include <gtest/gtest.h>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/contour_point.h>
#include <cg/operations/contains/rectangle_point.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/enum.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>

#include <random>
#include <array>
#include <limits>

#include <misc/random_utils.h>

#include "random_utils.h"
#include "test.h"

namespace tests_contains_triangle_point
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 6> tr;
      std::array<double, 2> p;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < p.size(); ++i)
         {
            p[i] = distr();
            tr[i] = distr();
         }
         for (size_t i = p.size(); i < tr.size(); ++i)
         {
            tr[i] = distr();
         }
         if (cg::orientation(cg::point_2(tr[0], tr[1]), cg::point_2(tr[2], tr[3]), cg::point_2(tr[4], tr[5])) == cg::CG_COLLINEAR)
         {
            tr[0] += std::numeric_limits<double>::epsilon();
         }
         CGAL::Triangle_2<CGAL::Exact_predicates_exact_constructions_kernel> triangle(
                  CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[0], tr[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[2], tr[3]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[4], tr[5]));
         for (int i = 0; i < 2; ++i)
         {
            bool cgal_res;
            if (triangle.orientation() == CGAL::CLOCKWISE)
            {
               cgal_res = triangle.has_on_negative_side(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(p[0], p[1]));
            }
            else
            {
               cgal_res = triangle.has_on_positive_side(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(p[0], p[1]));
            }
            EXPECT_EQ(cg::contains(cg::triangle_2(cg::point_2(tr[0], tr[1]), cg::point_2(tr[2], tr[3]), cg::point_2(tr[4], tr[5])),
                  cg::point_2(p[0], p[1])), cgal_res);
            p[0] = tr[0] * (1 + std::numeric_limits<double>::epsilon());
            p[1] = tr[1] * (1 + std::numeric_limits<double>::epsilon());
         }
      }
   }
}

namespace tests_contains_rectangle_point
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 4> rect;
      std::array<double, 2> p;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < p.size(); ++i)
         {
            rect[i] = distr();
            p[i] = distr();
         }
         for (size_t i = p.size(); i < rect.size(); ++i)
         {
            rect[i] = distr();
         }
         if (rect[1] < rect[0])
         {
            std::swap(rect[1], rect[0]);
         }
         if (rect[1] == rect[0])
         {
            rect[1] += std::numeric_limits<double>::epsilon();
         }
         if (rect[3] < rect[2])
         {
            std::swap(rect[3], rect[2]);
         }
         if (rect[3] == rect[2])
         {
            rect[3] += std::numeric_limits<double>::epsilon();
         }
         CGAL::Iso_rectangle_2<CGAL::Exact_predicates_exact_constructions_kernel> cgal_rect(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(rect[0], rect[2]),
                        CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(rect[1], rect[3]));
         for (int j = 0; j < 2; ++j)
         {
            EXPECT_EQ(cg::contains(cg::rectangle_2(cg::range(rect[0], rect[1]), cg::range(rect[2], rect[3])), cg::point_2(p[0], p[1])),
                  cgal_rect.has_on_bounded_side(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(p[0], p[1])) ||
                  cgal_rect.has_on_boundary(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(p[0], p[1])));
            for (size_t i = 0; i < p.size(); ++i)
            {
               p[i] = rect[i];
            }
         }
      }
   }
}

namespace tests_contains_segment_point
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 4> seg;
      std::array<double, 2> p;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < p.size(); ++i)
         {
            p[i] = distr();
            seg[i] = distr();
         }
         for (size_t i = p.size(); i < seg.size(); ++i)
         {
            seg[i] = distr();
         }
         CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel> segment(
                  CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[0], seg[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[2], seg[3]));
         for (int i = 0; i < 2; ++i)
         {
            EXPECT_EQ(cg::contains(cg::segment_2(cg::point_2(seg[0], seg[1]), cg::point_2(seg[2], seg[3])),
                  cg::point_2(p[0], p[1])), segment.has_on(CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(p[0], p[1])));
            p[0] = seg[0] * (1 + std::numeric_limits<double>::epsilon());
            p[1] = seg[1] * (1 + std::numeric_limits<double>::epsilon());
         }
      }
   }
}

namespace tests_contains_convex_contour_point
{
   void test()
   {
      util::uniform_random_int<int, std::random_device> size_distr(1000, 100000);
      util::uniform_random_real<double, std::random_device> distr(-100.0, 100.0);
      for (int k = 0; k < 250; ++k)
      {
         CGAL::Polygon_2<CGAL::Exact_predicates_exact_constructions_kernel> cgal_pol = generate_convex_polygon(size_distr());
         std::vector<cg::point_2> pts;
         for (size_t i = 0; i < cgal_pol.size(); ++i)
         {
            pts.push_back(cg::point_2(CGAL::to_double(cgal_pol[i].x()), CGAL::to_double(cgal_pol[i].y())));
         }
         cg::contour_2 pol(pts);
         for (int q = 0; q < 10; ++q)
         {
            double x = distr();
            double y = distr();
            bool cgal_res = false;
            if (CGAL::bounded_side_2(cgal_pol.vertices_begin(), cgal_pol.vertices_end(),
                                     CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(x, y)) == CGAL::ON_BOUNDED_SIDE)
            {
               cgal_res = true;
            }
            EXPECT_EQ(cg::convex_contains(pol, cg::point_2(x, y)), cgal_res);
         }
      }
   }
}

TEST(contains, DISABLED_triangle_point)
{
   void (*test_case)() = tests_contains_triangle_point::test;
   test(test_case);
}

TEST(contains, DISABLED_segment_point)
{
   void (*test_case)() = tests_contains_segment_point::test;
   test(test_case);
}

TEST(contains, DISABLED_rectangle_point)
{
   void (*test_case)() = tests_contains_rectangle_point::test;
   test(test_case);
}

TEST(contains, DISABLED_convex_contour_point)
{
   void (*test_case)() = tests_contains_convex_contour_point::test;
   test(test_case);
}
