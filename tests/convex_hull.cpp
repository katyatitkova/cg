#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/operations/contains/segment_point.h>

#include <cg/io/point.h>

#include <misc/random_utils.h>

#include <iterator>
#include <iostream>

#include "random_utils.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Point_2.h>

#include <thread>

namespace tests_convex_hull
{
   template <template <typename Iter> class HullAlgorithm>
   void convex_hull_test()
   {
      util::uniform_random_int<int, std::mt19937> size_distr(10, 10000);
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_pts;
      std::vector<cg::point_2> pts;
      std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> cgal_res;
      for (int q = 0; q < 2500; ++q)
      {
         cgal_pts = uniform_cgal_points(size_distr());
         pts.resize(0);
         for (size_t i = 0; i < cgal_pts.size(); ++i)
         {
            pts.push_back(cg::point_2(CGAL::to_double(cgal_pts[i].x()), CGAL::to_double(cgal_pts[i].y())));
         }
         cgal_res.resize(0);
         CGAL::convex_hull_2(cgal_pts.begin(), cgal_pts.end(), std::back_inserter(cgal_res));
         auto it_end = HullAlgorithm<std::vector<cg::point_2>::iterator>::call(pts.begin(), pts.end());
         EXPECT_EQ(cgal_res.size(), it_end - pts.begin());
         for (int i = 0; pts.begin() + i != it_end; ++i)
         {
            EXPECT_EQ(CGAL::to_double(cgal_res[i].x()), pts[i].x);
            EXPECT_EQ(CGAL::to_double(cgal_res[i].y()), pts[i].y);
         }
      }
   }

   template <template <typename T> class Func>
   void test()
   {
      std::thread t1(convex_hull_test<Func>);
      std::thread t2(convex_hull_test<Func>);
      std::thread t3(convex_hull_test<Func>);
      std::thread t4(convex_hull_test<Func>);
      t1.join();
      t2.join();
      t3.join();
      t4.join();
   }

   template <typename BidIter>
   struct andrew_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::andrew_hull(from, to);
      }
   };

   TEST(convex_hull, DISABLED_andrew_cgal)
   {
      test<andrew_hull_wrapper>();
   }

   template <typename BidIter>
   struct graham_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::graham_hull(from, to);
      }
   };

   TEST(convex_hull, DISABLED_graham_cgal)
   {
      test<graham_hull_wrapper>();
   }
}
