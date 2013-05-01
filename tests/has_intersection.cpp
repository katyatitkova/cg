#include <gtest/gtest.h>

#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/has_intersection/triangle_segment.h>
#include <cg/operations/has_intersection/rectangle_segment.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

#include <random>
#include <array>
#include <limits>

#include "test.h"
#include <misc/random_utils.h>

namespace tests_has_intersection_segment_segment
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 4> seg1;
      std::array<double, 4> seg2;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < seg1.size(); ++i)
         {
            seg1[i] = distr();
            seg2[i] = distr();
         }
         EXPECT_EQ(cg::has_intersection(cg::segment_2(cg::point_2(seg1[0], seg1[1]), cg::point_2(seg1[2], seg1[3])),
               cg::segment_2(cg::point_2(seg2[0], seg2[1]), cg::point_2(seg2[2], seg2[3]))),
               CGAL::do_intersect(CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                  (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[0], seg1[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[2], seg1[3])),
               CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
               (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[0], seg2[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[2], seg2[3]))));
         for (size_t j = 0; j < seg1.size(); ++j)
         {
            for (size_t i = 0; i < seg2.size(); ++i)
            {
               seg2[i] = seg1[i];
            }
            seg2[j] *= (1 + std::numeric_limits<double>::epsilon());
            EXPECT_EQ(cg::has_intersection(cg::segment_2(cg::point_2(seg1[0], seg1[1]), cg::point_2(seg1[2], seg1[3])),
                  cg::segment_2(cg::point_2(seg2[0], seg2[1]), cg::point_2(seg2[2], seg2[3]))),
                  CGAL::do_intersect(CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                     (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[0], seg1[1]),
                  CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[2], seg1[3])),
                  CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
                  (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[0], seg2[1]),
                  CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[2], seg2[3]))));
         }
      }
   }
}

namespace tests_has_intersection_triangle_segment
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 6> tr;
      std::array<double, 4> seg;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < seg.size(); ++i)
         {
            tr[i] = distr();
            seg[i] = distr();
         }
         for (size_t i = seg.size(); i < tr.size(); ++i)
         {
            tr[i] = distr();
         }
         if (cg::orientation(cg::point_2(tr[0], tr[1]), cg::point_2(tr[2], tr[3]), cg::point_2(tr[4], tr[5])) == cg::CG_COLLINEAR)
         {
            tr[0] += std::numeric_limits<double>::epsilon();
         }
         EXPECT_EQ(cg::has_intersection(cg::triangle_2(cg::point_2(tr[0], tr[1]), cg::point_2(tr[2], tr[3]), cg::point_2(tr[4], tr[5])),
               cg::segment_2(cg::point_2(seg[0], seg[1]), cg::point_2(seg[2], seg[3]))),
               CGAL::do_intersect(CGAL::Triangle_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                  (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[0], tr[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[2], tr[3]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(tr[4], tr[5])),
               CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
               (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[0], seg[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[2], seg[3]))));
      }
   }
}

namespace tests_has_intersection_rectangle_segment
{
   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-5.0, 5.0);
      std::array<double, 4> rect;
      std::array<double, 4> seg;
      for (int k = 0; k < 2500; ++k)
      {
         for (size_t i = 0; i < rect.size(); ++i)
         {
            rect[i] = distr();
            seg[i] = distr();
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
         EXPECT_EQ(cg::has_intersection(cg::rectangle_2(cg::range(rect[0], rect[1]), cg::range(rect[2], rect[3])),
               cg::segment_2(cg::point_2(seg[0], seg[1]), cg::point_2(seg[2], seg[3]))),
               CGAL::do_intersect(CGAL::Iso_rectangle_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                  (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(rect[0], rect[2]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(rect[1], rect[3])),
               CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
               (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[0], seg[1]),
               CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg[2], seg[3]))));
      }
   }
}

TEST(has_intersection, segment_segment)
{
   void (*test_case)() = tests_has_intersection_segment_segment::test;
   test(test_case);
}

TEST(has_intersection, triangle_segment)
{
   void (*test_case)() = tests_has_intersection_triangle_segment::test;
   test(test_case);
}

TEST(has_intersection, rectangle_segment)
{
   void (*test_case)() = tests_has_intersection_rectangle_segment::test;
   test(test_case);
}
