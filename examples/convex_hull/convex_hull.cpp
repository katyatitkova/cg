#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>

#include <cg/convex_hull/graham.h>
#include <cg/convex_hull/andrew.h>

#include <string>

using cg::point_2f;
using cg::point_2;

enum ALGO_TYPE
{
   GRAHAM,
   ANDREW
};

struct convex_hull_viewer : cg::visualization::viewer_adapter
{
   convex_hull_viewer(ALGO_TYPE algo_type)
      : ch_size_(0),
        type(algo_type)
   {
      switch (type)
      {
      case GRAHAM:
         type_s = "Graham";
         break;
      case ANDREW:
         type_s = "Andrew";
         break;
      }
   }

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (point_2 const & p : pts_)
         drawer.draw_point(p);

      drawer.set_color(Qt::green);
      for (size_t lp = ch_size_ - 1, l = 0; l != ch_size_; lp = l++)
      {
         drawer.draw_point(pts_[l], 3);
         drawer.draw_line(pts_[lp], pts_[l]);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {

      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << pts_.size() << " convex_hull: " << ch_size_ << cg::visualization::endl
                        << "algo: " << type_s << cg::visualization::endl;
   }

   bool on_release(const point_2f & p)
   {
      pts_.push_back(p);
      switch (type)
      {
      case GRAHAM:
         ch_size_ = std::distance(pts_.begin(), cg::graham_hull(pts_.begin(), pts_.end()));
         break;
      case ANDREW:
         ch_size_ = std::distance(pts_.begin(), cg::andrew_hull(pts_.begin(), pts_.end()));
         break;
      }
      return true;
   }

private:
   std::vector<point_2> pts_;
   size_t ch_size_;
   ALGO_TYPE type;
   std::string type_s;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   //convex_hull_viewer viewer(GRAHAM);
   ALGO_TYPE type = GRAHAM;
   if (argc > 1)
   {
      switch (argv[1][0])
      {
      case 'g':
         type = GRAHAM;
         break;
      case 'a':
         type = ANDREW;
         break;
      }
   }
   convex_hull_viewer viewer(type);
   cg::visualization::run_viewer(&viewer, "convex hull");
}
