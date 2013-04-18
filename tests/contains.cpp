#include <gtest/gtest.h>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/enum.h>

#include <random>
#include <array>
#include <limits>

TEST(contains, DISABLED_triangle_point)
{
   std::mt19937 gen;
   std::uniform_real_distribution<> distr(-5.0, 5.0);
   std::array<double, 6> tr;
   std::array<double, 2> p;
   for (int k = 0; k < 10000; ++k)
   {
      for (size_t i = 0; i < p.size(); ++i)
      {
         p[i] = distr(gen);
         tr[i] = distr(gen);
      }
      for (size_t i = p.size(); i < tr.size(); ++i)
      {
         tr[i] = distr(gen);
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

TEST(contains, DISABLED_segment_point)
{
   std::mt19937 gen;
   std::uniform_real_distribution<> distr(-5.0, 5.0);
   std::array<double, 4> seg;
   std::array<double, 2> p;
   for (int k = 0; k < 10000; ++k)
   {
      for (size_t i = 0; i < p.size(); ++i)
      {
         p[i] = distr(gen);
         seg[i] = distr(gen);
      }
      for (size_t i = p.size(); i < seg.size(); ++i)
      {
         seg[i] = distr(gen);
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
