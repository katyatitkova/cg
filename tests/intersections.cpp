#include <gtest/gtest.h>
#include <cg/operations/intersections.h>

TEST(intersections, segment_intersects_segment)
{
    EXPECT_EQ(cg::segment_intersects_segment(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(1, 1)),
                                            cg::segment_2t<double>(cg::point_2(1, 0), cg::point_2(0, 1))), true);
    EXPECT_EQ(cg::segment_intersects_segment(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(0, 0.5), cg::point_2(0, 1))), true);
    EXPECT_EQ(cg::segment_intersects_segment(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(1, 0), cg::point_2(1, 1))), false);
    EXPECT_EQ(cg::segment_intersects_segment(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(0, 1), cg::point_2(1, 1))), true);
    EXPECT_EQ(cg::segment_intersects_segment(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(2, 2)),
                                            cg::segment_2t<double>(cg::point_2(3, 3), cg::point_2(3, 2))), false);
}

TEST(intersections, segment_intersects_triangle)
{
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(2, 2)),
                                              cg::triangle_2t<double>(cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2))), true);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(5, 5)),
                                              cg::triangle_2t<double>(cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2))), false);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, -1)),
                                              cg::triangle_2t<double>(cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2))), true);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(3, 3)),
                                              cg::triangle_2t<double>(cg::point_2(0, 0), cg::point_2(0, 10), cg::point_2(10, 0))), true);
}

TEST(intersections, segment_intersects_rectangle)
{
    EXPECT_EQ(cg::segment_intersects_rectangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(4, 2)),
                                               cg::rectangle_2t<double>(
                                                   cg::range_t<double>(1, 6), cg::range_t<double>(1, 4))), true);
    EXPECT_EQ(cg::segment_intersects_rectangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(4, 3)),
                                               cg::rectangle_2t<double>(
                                                   cg::range_t<double>(1, 6), cg::range_t<double>(1, 4))), true);
    EXPECT_EQ(cg::segment_intersects_rectangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(8, 2)),
                                               cg::rectangle_2t<double>(
                                                   cg::range_t<double>(1, 6), cg::range_t<double>(1, 4))), true);
    EXPECT_EQ(cg::segment_intersects_rectangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(8, 8)),
                                               cg::rectangle_2t<double>(
                                                   cg::range_t<double>(1, 6), cg::range_t<double>(1, 4))), true);
    EXPECT_EQ(cg::segment_intersects_rectangle(cg::segment_2t<double>(cg::point_2(2, 12), cg::point_2(4, 12)),
                                               cg::rectangle_2t<double>(
                                                   cg::range_t<double>(1, 6), cg::range_t<double>(1, 4))), false);
}
