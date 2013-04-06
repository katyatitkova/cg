#include <gtest/gtest.h>
#include <cg/operations/belongings.h>

TEST(belongings, point_in_triangle)
{
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(0.5, 0), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1))), true);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(0, 0), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1))), true);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(3, 3), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1))), false);
    EXPECT_EQ(cg::point_in_triangle(cg::point_2(1, 1), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1))), true);
}
