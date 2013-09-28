#include <gtest/gtest.h>
#include <cg/operations/douglas_peucker.h>
#include <cg/primitives/point.h>
#include <vector>
#include <iostream>

TEST(douglas_peucker, first)
{
   std::vector<cg::point_2> v = { cg::point_2(0.0, 0.0),
                                  cg::point_2(1.0, 0.0),
                                  cg::point_2(1.0, 1.0),
                                  cg::point_2(2.0, 1.0),
                                  cg::point_2(2.0, 0.0),
                                  cg::point_2(3.0, 0.0)
                                };
   std::vector<cg::point_2> r;
   cg::simplify(v.begin(), v.end(), 0.1, std::back_inserter(r));
   EXPECT_EQ(r.size(), 6);
   EXPECT_EQ(r[0], v[0]);
   EXPECT_EQ(r[1], v[1]);
   EXPECT_EQ(r[2], v[2]);
   EXPECT_EQ(r[3], v[3]);
   EXPECT_EQ(r[4], v[4]);
   EXPECT_EQ(r[5], v[5]);
   r.clear();
   cg::simplify(v.begin(), v.end(), 0.5, std::back_inserter(r));
   EXPECT_EQ(r.size(), 4);
   EXPECT_EQ(r[0], v[0]);
   EXPECT_EQ(r[1], v[1]);
   EXPECT_EQ(r[2], v[2]);
   EXPECT_EQ(r[3], v[5]);
   r.clear();
   cg::simplify(v.begin(), v.end(), 1, std::back_inserter(r));
   EXPECT_EQ(r.size(), 2);
   EXPECT_EQ(r[0], v[0]);
   EXPECT_EQ(r[1], v[5]);
}

TEST(douglas_peucker, second)
{
   std::vector<cg::point_2> v = { cg::point_2(-180.0, 6.0),
                                  cg::point_2(-7.0, 170.0),
                                  cg::point_2(137.0, -99.0),
                                  cg::point_2(-223.0, -209.0)
                                };
   std::vector<cg::point_2> r;
   cg::simplify(v.begin(), v.end(), 10.0, std::back_inserter(r));
}
