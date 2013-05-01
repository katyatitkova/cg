#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>

#include <cg/operations/contains/segment_point.h>

using cg::point_2;
using cg::point_2f;

struct segment_contains_point_viewer : cg::visualization::viewer_adapter
{
   segment_contains_point_viewer()
      : s_(cg::segment_2(point_2(-100, -100), point_2(100, 100))),
        rbutton_pressed_(false)
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      if (current_point_ && cg::contains(s_, *current_point_))
         drawer.set_color(Qt::green);

      drawer.draw_line(s_[0], s_[1]);

     if (idx_)
     {
        drawer.set_color(rbutton_pressed_ ? Qt::red : Qt::yellow);
        drawer.draw_point(s_[(*idx_)], 5);
     }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near segment vertex to move it"
                        << cg::visualization::endl
                        << "if segment is green it contains cursor point"
                        << cg::visualization::endl;
   }

   bool on_press(const point_2f & p)
   {
      rbutton_pressed_ = true;
      return set_idx(p);
   }

   bool on_release(const point_2f & p)
   {
      rbutton_pressed_ = false;
      return false;
   }

   bool on_move(const point_2f & p)
   {
      if (!rbutton_pressed_)
         current_point_ = p;
         set_idx(p);
      if (!idx_)
         return true;

      if (rbutton_pressed_) s_[(*idx_)] = p;
      return true;
   }

private:
   bool set_idx (const point_2f & p)
   {
      idx_.reset();
      float max_r = 0;
      for (size_t l = 0; l != 1; ++l)
      {
         for (size_t k = 0; k != 1; ++k) {
            float current_r = (p.x - s_[k].x) * (p.x - s_[k].x) + (p.y - s_[k].y) * (p.y - s_[k].y);
            if ((idx_ && current_r < max_r) || (!idx_ && current_r < 100))
            {
               idx_ = k;
               max_r = current_r;
            }
         }
      }
      return idx_;
   }

   cg::segment_2 s_;
   boost::optional<size_t> idx_;
   boost::optional<cg::point_2> current_point_;
   bool rbutton_pressed_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   segment_contains_point_viewer viewer;
   cg::visualization::run_viewer(&viewer, "segment contains point");
}

