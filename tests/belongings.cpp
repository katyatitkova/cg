#include <gtest/gtest.h>
#include <cg/operations/belongings.h>

TEST(belongings, point_in_triangle)
{
    EXPECT_TRUE(cg::point_in_triangle(cg::point_2(0.5, 0), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1))));
    EXPECT_TRUE(cg::point_in_triangle(cg::point_2(0, 0), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(1, -1))));
    EXPECT_FALSE(cg::point_in_triangle(cg::point_2(3, 3), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1))));
    EXPECT_TRUE(cg::point_in_triangle(cg::point_2(1, 1), cg::triangle_2t<double>(cg::point_2(1, 1), cg::point_2(-1, -1), cg::point_2(-1, 1))));
}

TEST(belongings, point_in_convex_contour)
{
    std::vector<cg::point_2> v = {cg::point_2(0, 0), cg::point_2(0, 4), cg::point_2(4, 4), cg::point_2(4, 0)};
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(2, 2), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(4, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(0, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(0, 4), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(4, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(1, 3), cg::contour_2t<double>(v)));
    EXPECT_FALSE(cg::point_in_convex_contour(cg::point_2(5, 5), cg::contour_2t<double>(v)));
    EXPECT_FALSE(cg::point_in_convex_contour(cg::point_2(-5, -5), cg::contour_2t<double>(v)));
    v = {cg::point_2(4, 0), cg::point_2(4, 4), cg::point_2(0, 4), cg::point_2(0, 0)};
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(2, 2), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(4, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(0, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(0, 4), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(4, 0), cg::contour_2t<double>(v)));
    EXPECT_TRUE(cg::point_in_convex_contour(cg::point_2(1, 3), cg::contour_2t<double>(v)));
    EXPECT_FALSE(cg::point_in_convex_contour(cg::point_2(5, 5), cg::contour_2t<double>(v)));
    EXPECT_FALSE(cg::point_in_convex_contour(cg::point_2(-5, -5), cg::contour_2t<double>(v)));
}
