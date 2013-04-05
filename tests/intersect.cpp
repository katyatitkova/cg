#include <vector>
#include <algorithm>
#include <chrono>
#include "intersect_slow.h"
#include <gtest/gtest.h>
#include <boost/range/algorithm/generate.hpp>
#include <boost/range/algorithm/sort.hpp>
#include "random_utils.h"
#include <cg/common/intersect.h>

TEST(intersect_test, intersect_accuracy)
{
    boost::random::mt19937 gen;
    boost::random::uniform_real_distribution<> distr(-(1LL << 53), (1LL << 53));
    std::vector<cg::point_2> v = uniform_points(30);
    std::sort(v.begin(), v.end());
    cg::point_2 a, b;
    a.x = distr(gen);
    a.y = distr(gen);
    b.x = distr(gen);
    b.y = distr(gen);
    std::vector<cg::point_2> res;
    cg::common::intersect(v, a, b, std::back_inserter(res));
    std::vector<cg::point_2> res_slow;
    intersect_slow(v.begin(), v.end(), a, b, std::back_inserter(res_slow));
    EXPECT_EQ(res, res_slow);
}

TEST(intersect_test, intersect_speed)
{
    boost::random::mt19937 gen;
    boost::random::uniform_real_distribution<> distr(-(1LL << 53), (1LL << 53));
    std::vector<cg::point_2> v = uniform_points(10000);
    std::sort(v.begin(), v.end());
    cg::point_2 a, b;
    a.x = distr(gen);
    a.y = distr(gen);
    b.x = distr(gen);
    b.y = distr(gen);
    std::vector<cg::point_2> res;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    cg::common::intersect(v, a, b, std::back_inserter(res));
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    std::vector<cg::point_2> res_slow;
    start = std::chrono::system_clock::now();
    intersect_slow(v.begin(), v.end(), a, b, std::back_inserter(res_slow));
    std::chrono::duration<double> sec_slow = std::chrono::system_clock::now() - start;
    EXPECT_LE(sec, sec_slow);
}
