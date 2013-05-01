#include <gtest/gtest.h>

#include <vector>
#include <iostream>

#include <cg/operations/intersection/segment_segment.h>

#include <CGAL/intersections.h>
#include <CGAL/Segment_2.h>

#include <misc/random_utils.h>

#include "test.h"
#include "random_utils.h"

namespace tests_intersection_segment_segment
{
   class visitor_t : public boost::static_visitor<>
   {
   public:

      void operator()(boost::none_t &)
      {
         ASSERT_EQ(numbers.size(), 0);
      }

      void operator()(cg::point_2 & p)
      {
         ASSERT_EQ(numbers.size(), 2);
         EXPECT_EQ(numbers[0], p.x);
         EXPECT_EQ(numbers[1], p.y);
         std::cout.precision(20);
         std::cout << numbers[0] << std::endl << p.x << std::endl;
      }

      void operator()(cg::segment_2 & s)
      {
         ASSERT_EQ(numbers.size(), 4);
         EXPECT_EQ(numbers[0], s[0].x);
         EXPECT_EQ(numbers[1], s[0].y);
         EXPECT_EQ(numbers[2], s[1].x);
         EXPECT_EQ(numbers[3], s[1].y);
      }

      std::vector<double> numbers;
   };

   void test()
   {
      util::uniform_random_real<double, std::random_device> distr(-10.0, 10.0);
      std::array<double, 4> seg1;
      std::array<double, 4> seg2;
      for (size_t k = 0; k < 1; ++k)
      {
         for (size_t i = 0; i < seg1.size(); ++i)
         {
            seg1[i] = distr();
            seg2[i] = distr();
         }
         auto cgal_res = CGAL::intersection(CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                                (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[0], seg1[1]),
                                                CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg1[2], seg1[3])),
                                            CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>
                                                (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[0], seg2[1]),
                                                CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(seg2[2], seg2[3])));
         auto res = cg::intersection(cg::segment_2(cg::point_2(seg1[0], seg1[1]), cg::point_2(seg1[2], seg1[3])),
                                     cg::segment_2(cg::point_2(seg2[0], seg2[1]), cg::point_2(seg2[2], seg2[3])),
                                     -1020);
         visitor_t visitor;
         if (const CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> *ipoint =
             CGAL::object_cast<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>>(&cgal_res))
         {
            visitor.numbers.push_back(CGAL::to_double((*ipoint).x()));
            visitor.numbers.push_back(CGAL::to_double((*ipoint).y()));
            res.apply_visitor(visitor);
         }
         else
         {
            if (const CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel> *iseg =
                CGAL::object_cast<CGAL::Segment_2<CGAL::Exact_predicates_exact_constructions_kernel>>(&cgal_res))
            {
               visitor.numbers.push_back(CGAL::to_double((*iseg)[0].x()));
               visitor.numbers.push_back(CGAL::to_double((*iseg)[0].y()));
               visitor.numbers.push_back(CGAL::to_double((*iseg)[1].x()));
               visitor.numbers.push_back(CGAL::to_double((*iseg)[1].y()));
               res.apply_visitor(visitor);
            }
            else
            {
               res.apply_visitor(visitor);
            }
         }
      }
   }
}

TEST(intersection, segment_segment)
{
   void (*test_case)() = tests_intersection_segment_segment::test;
   test(test_case);
}

