#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>
#include <cg/convex_hull/quick_hull.h>
#include <cg/convex_hull/jarvis.h>

#include <cg/operations/douglas_peucker.h>

#include <string>

using cg::point_2f;
using cg::point_2;

struct douglas_peucker_viewer : cg::visualization::viewer_adapter
{
   douglas_peucker_viewer():
      eps(100.0)
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (point_2 const & p : pts_)
         drawer.draw_point(p);

      drawer.set_color(Qt::green);
      for (size_t lp = 0, l = 0; l != s_pts_.size(); lp = l++)
      {
         drawer.draw_point(s_pts_[l], 3);
         drawer.draw_line(s_pts_[lp], s_pts_[l]);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {

      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "all points: " << pts_.size()
                        << " simplified points: " << s_pts_.size() << cg::visualization::endl
                        << "eps = " << eps << cg::visualization::endl
                        << "press W to eps += 10, S to eps -= 10" << cg::visualization::endl;
   }

   void make_simple()
   {
      s_pts_.clear();
      cg::simplify(pts_.begin(), pts_.end(), eps, std::back_inserter(s_pts_));
   }

   bool on_release(const point_2f & p)
   {
      pts_.push_back(p);
      make_simple();
      return true;
   }

   bool on_key(int key)
   {
      switch (key)
      {
      case Qt::Key_W :
         eps += 10;
         break;
      case Qt::Key_S :
         if (eps >= 10)
            eps -= 10;
         break;
      default :
         return false;
      }
      make_simple();
      return true;
   }

private:
   std::vector<point_2> pts_;
   std::vector<point_2> s_pts_;
   double eps;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   douglas_peucker_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Douglas-Peucker");
}

