#pragma once

#include <random>
#include <algorithm>
#include <exception>
#include <iostream>

#include <cg/primitives/point.h>
#include <misc/random_utils.h>

#include <CGAL/Point_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Polygon_2.h>

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
   util::uniform_random_real<double, std::random_device> distr(-100.0, 100.0);

   std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> res(count);

   for (size_t l = 0; l != count; ++l)
   {
      res[l] = CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>(distr(), distr());
   }

   return res;
}

inline CGAL::Triangulation_2<CGAL::Exact_predicates_exact_constructions_kernel>::Vertex_handle get_vertex_handle
         (CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel> const & point,
          CGAL::Triangulation_2<CGAL::Exact_predicates_exact_constructions_kernel> const & t)
{
   auto fh = t.locate(point);
   for (size_t i = 0; i < 2; ++i)
   {
      if (fh->vertex(i)->point() == point)
      {
         return fh->vertex(i);
      }
   }
   return fh->vertex(2);
}

inline std::vector<int> dfs(std::vector<std::vector<int>> const & graph, std::vector<bool> visited,
                            std::vector<int> pol, int i, size_t count)
{
   std::vector<std::vector<int>> res;
   bool f = false;
   if (count < graph.size() / 4)
   {
      for (size_t j = 0; j < graph[i].size(); ++j)
      {
         if (!visited[graph[i][j]])
         {
            visited[graph[i][j]] = true;
            pol.push_back(graph[i][j]);
            res.push_back(dfs(graph, visited, pol, graph[i][j], count + 1));
            visited[graph[i][j]] = false;
            pol.pop_back();
            f = true;
         }
      }
   }
   if (!f)
   {
      for (size_t i = pol.size() - 1; i > 0; --i)
      {
         auto v = std::lower_bound(graph[pol[i]].begin(), graph[pol[i]].end(), pol[0]);
         if (v != graph[pol[i]].end() && (*v) == pol[0])
         {
            pol.erase(pol.begin() + i + 1, pol.end());
            break;
         }
      }
      res.push_back(pol);
   }
   return *(std::max_element(res.begin(), res.end(),
                              [] (std::vector<int> const & left, std::vector<int> const & right)
                              {
                                 return left.size() < right.size();
                              }));
}

inline CGAL::Polygon_2<CGAL::Exact_predicates_exact_constructions_kernel> generate_simple_polygon(size_t size)
{
   std::vector<CGAL::Point_2<CGAL::Exact_predicates_exact_constructions_kernel>> pts = uniform_cgal_points(size);
   CGAL::Triangulation_2<CGAL::Exact_predicates_exact_constructions_kernel> t;
   t.insert(pts.begin(), pts.end());
   util::uniform_random_int<int, std::mt19937> size_distr(0, size - 1);
   int n = size_distr();
   for (int q = 0; q < n; ++q)
   {
      auto f = t.locate(pts[size_distr()]);
      for (int j = 0; j < 3; ++j)
      {
         try
         {
            t.flip(f, j);
            break;
         }
         catch (std::exception & e)
         {}
      }
   }
   std::vector<std::vector<int>> graph(pts.size());
   for (size_t i = 0; i < pts.size(); ++i)
   {
      auto vh = get_vertex_handle(pts[i], t);
      for (size_t j = i + 1; j < pts.size(); ++j)
      {
         if (t.is_edge(vh, get_vertex_handle(pts[j], t)))
         {
            graph[i].push_back(j);
            graph[j].push_back(i);
         }
      }
   }
   std::vector<int> pol;
   std::vector<bool> visited(pts.size(), false);
   pol.push_back(0);
   visited[0] = true;
   pol = dfs(graph, visited, pol, 0, 0);
   CGAL::Polygon_2<CGAL::Exact_predicates_exact_constructions_kernel> plg;
   for (size_t i = 0; i < pol.size(); ++i)
   {
      plg.push_back(pts[pol[i]]);
   }
   pts = uniform_cgal_points(3);
   while (plg.size() < 3)
   {
      plg.push_back(pts[plg.size()]);
   }
   return plg;
}
