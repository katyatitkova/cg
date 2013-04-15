#pragma once

#include <random>
#include <cg/primitives/point.h>

inline std::vector<cg::point_2> uniform_points(size_t count)
{
   std::mt19937 gen;
   std::uniform_real_distribution<> distr;

   std::vector<cg::point_2> res(count);
   for (size_t l = 0; l != count; ++l)
   {
      res[l].x = distr(gen);
      res[l].y = distr(gen);
   }

   return res;
}
