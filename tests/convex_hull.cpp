#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/convex_hull/quick_hull.h>
#include <cg/convex_hull/jarvis.h>

#include <misc/random_utils.h>

#include <iterator>
#include <iostream>
#include <fstream>

#include <cg/io/point.h>

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
      util::uniform_random_int<int, std::random_device> size_distr(10, 15);
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
            std::cout << pts[i] << " ";
         }
         std::cout << std::endl;
         cgal_res.resize(0);
         CGAL::convex_hull_2(cgal_pts.begin(), cgal_pts.end(), std::back_inserter(cgal_res));
         auto it_end = HullAlgorithm<std::vector<cg::point_2>::iterator>::call(pts.begin(), pts.end());
         //EXPECT_EQ(cgal_res.size(), it_end - pts.begin());
         if (cgal_res.size() != it_end - pts.begin())
         {
            std::cout << "QuickHull:" << std::endl << it_end - pts.begin() << std::endl;
            //std::copy(pts.begin(), pts.end(), std::ostream_iterator<cg::point_2>(std::cout, " "));
            for (size_t ololo = 0; ololo < pts.size(); ++ololo)
            {
               std::cout << pts[ololo] << " ";
            }
            std::cout << std::endl;
            std::cout << "CGAL:" << std::endl << cgal_res.size() << std::endl;
            for (size_t ololo = 0; ololo < cgal_res.size(); ++ololo)
            {
               std::cout << "(" << CGAL::to_double(cgal_res[ololo].x()) << ", " << CGAL::to_double(cgal_res[ololo].y()) << ") ";
            }
            std::cout << std::endl << "-----------------------" << std::endl;
         }
         for (int i = 0; pts.begin() + i != it_end; ++i)
         {
            //EXPECT_EQ(CGAL::to_double(cgal_res[i].x()), pts[i].x);
            //EXPECT_EQ(CGAL::to_double(cgal_res[i].y()), pts[i].y);
         }
      }
   }

   template <template <typename T> class Func>
   void test()
   {
      /*std::thread t1(convex_hull_test<Func>);
      std::thread t2(convex_hull_test<Func>);
      std::thread t3(convex_hull_test<Func>);
      std::thread t4(convex_hull_test<Func>);
      t1.join();
      t2.join();
      t3.join();
      t4.join();*/
      convex_hull_test<Func>();
   }

   template <typename BidIter>
   struct andrew_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::andrew_hull(from, to);
      }
   };

   template <typename BidIter>
   struct graham_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::graham_hull(from, to);
      }
   };

   template <typename BidIter>
   struct quick_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::quick_hull(from, to);
      }
   };

   template <typename BidIter>
   struct jarvis_hull_wrapper
   {
      static BidIter call (BidIter from, BidIter to)
      {
         return cg::jarvis_hull(from, to);
      }
   };
}

TEST(convex_hull, DISABLED_andrew)
{
   tests_convex_hull::test<tests_convex_hull::andrew_hull_wrapper>();
}

TEST(convex_hull, DISABLED_graham)
{
   tests_convex_hull::test<tests_convex_hull::graham_hull_wrapper>();
}

TEST(convex_hull, quick_hull)
{
   tests_convex_hull::test<tests_convex_hull::quick_hull_wrapper>();
}

TEST(convex_hull, DISABLED_jarvis)
{
   tests_convex_hull::test<tests_convex_hull::jarvis_hull_wrapper>();
}
