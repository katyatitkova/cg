#pragma once

#include <random>
#include <cg/primitives/point.h>
#include <misc/random_utils.h>

#include <CGAL/Point_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

inline std::vector<cg::point_2> uniform_points(size_t count)
{
   util::uniform_random_real<double> rand(-100., 100.);

   std::vector<cg::point_2> res(count);

   for (size_t l = 0; l != count; ++l)
   {
      rand >> res[l].x;
      rand >> res[l].y;
   }

   return res;
}

inline std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> uniform_cgal_points(size_t count)
{
   std::mt19937 gen;
   std::uniform_real_distribution<> distr(-100.0, 100.0);

   std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> res(count);

   for (size_t l = 0; l != count; ++l)
   {
      res[l] = CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(distr(gen), distr(gen));
   }

   return res;
}
