#include <gtest/gtest.h>

#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/has_intersection/triangle_segment.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

#include <random>
#include <array>
#include <limits>

TEST(has_intersection, segment_segment)
{
    std::mt19937 gen;
    std::uniform_real_distribution<> distr(-5.0, 5.0);
    std::array<double, 4> seg1;
    std::array<double, 4> seg2;
    for (int k = 0; k < 1000; ++k)
    {
        for (size_t i = 0; i < seg1.size(); ++i)
        {
            seg1[i] = distr(gen);
            seg2[i] = distr(gen);
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

TEST(has_intersection, triangle_segment)
{
   using cg::point_2;
   using cg::segment_2;

   cg::triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 0), point_2(-1, -1))));

   EXPECT_TRUE(cg::has_intersection(t, segment_2(point_2(0, 1), point_2(2, 1))));
   EXPECT_FALSE(cg::has_intersection(t, segment_2(point_2(0, 2), point_2(2, 2))));
}
