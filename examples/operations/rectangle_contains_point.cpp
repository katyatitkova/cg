#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include <cg/primitives/segment.h>
#include <cg/primitives/rectangle.h>
#include <cg/primitives/range.h>
#include <cg/primitives/point.h>

#include <cg/operations/contains/rectangle_point.h>

using cg::point_2;
using cg::point_2f;

struct rectangle_contains_point_viewer : cg::visualization::viewer_adapter
{
   rectangle_contains_point_viewer()
      : r_(cg::range(-50, 50), cg::range(-50, 50)),
        rbutton_pressed_(false)
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      if (current_point_ && cg::contains(r_, *current_point_))
         drawer.set_color(Qt::green);

      for(size_t l = 0; l != 2; ++l)
      {
         drawer.draw_line(r_.corner(l, l), r_.corner(l^1, l));
         drawer.draw_line(r_.corner(l, l), r_.corner(l, l^1));
      }

      if (idx_)
      {
         drawer.set_color(rbutton_pressed_ ? Qt::red : Qt::yellow);
         if(on_rect)
            drawer.draw_point(r_.corner((*idx_).first, (*idx_).second), 5);
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton near segment vertex to move it"
                        << cg::visualization::endl
                        << "if rectangle is green rectangle contains cursor point"
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
      {
         current_point_ = p;
         set_idx(p);
      }
      if (!idx_)
         return true;

      if (rbutton_pressed_)
      {
         if(on_rect)
         {
            (*idx_).first ? r_.x.sup = p.x : r_.x.inf = p.x;
            (*idx_).second ? r_.y.sup = p.y : r_.y.inf = p.y;
         }
      }
      return true;
   }

private:
   bool set_idx (const point_2f & p)
   {
      idx_.reset();
      float max_r;
      for (size_t l = 0; l != 2; ++l)
      {
         for (size_t lp = 0; lp != 2; ++lp)
         {
            float current_r = (p.x - r_.corner(l, lp).x) * (p.x - r_.corner(l, lp).x) + (p.y - r_.corner(l, lp).y) * (p.y - r_.corner(l ,lp).y);
            if ((idx_ && current_r < max_r) || (!idx_ && current_r < 100))
            {
               idx_ = std::make_pair(l, lp);
               max_r = current_r;
               on_rect = true;
            }
         }
      }

      return idx_;
   }

   bool on_rect;
   cg::rectangle_2 r_;
   boost::optional< std::pair<size_t, size_t> > idx_;
   boost::optional<cg::point_2> current_point_;
   bool rbutton_pressed_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   rectangle_contains_point_viewer viewer;
   cg::visualization::run_viewer(&viewer, "rectangle contains point");
}

