#include <gtest/gtest.h>
#include <cg/operations/segment_intersect.h>

TEST(intersect, segments_are_intersecting)
{
    EXPECT_EQ(cg::segments_are_intersecting(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(1, 1)),
                                            cg::segment_2t<double>(cg::point_2(1, 0), cg::point_2(0, 1))), true);
    EXPECT_EQ(cg::segments_are_intersecting(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(0, 0.5), cg::point_2(0, 1))), true);
    EXPECT_EQ(cg::segments_are_intersecting(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(1, 0), cg::point_2(1, 1))), false);
    EXPECT_EQ(cg::segments_are_intersecting(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, 1)),
                                            cg::segment_2t<double>(cg::point_2(0, 1), cg::point_2(1, 1))), true);
    EXPECT_EQ(cg::segments_are_intersecting(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(2, 2)),
                                            cg::segment_2t<double>(cg::point_2(3, 3), cg::point_2(3, 2))), false);
}

TEST(intersect, point_in_triangle)
{
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(0.5, 0), cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1)), true);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(0, 0), cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1)), true);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(3, 3), cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1)), false);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(1, 1), cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1)), true);
}

TEST(intersect, segment_and_triangle)
{
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(2, 2)),
                                              cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2)), true);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(5, 5)),
                                              cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2)), false);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(0, 0), cg::point_2(0, -1)),
                                              cg::point_2(0, 2), cg::point_2(-2, -2), cg::point_2(2, -2)), true);
    EXPECT_EQ(cg::segment_intersects_triangle(cg::segment_2t<double>(cg::point_2(2, 2), cg::point_2(3, 3)),
                                              cg::point_2(0, 0), cg::point_2(0, 10), cg::point_2(10, 0)), true);
}

TEST(intersect, segment_and_rectangle)
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
