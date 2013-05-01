#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include "cg/visualization/viewer_adapter.h"
#include "cg/visualization/draw_util.h"

#include "cg/io/point.h"

#include <cg/primitives/triangle.h>
#include <cg/primitives/point.h>
#include <cg/operations/intersection/segment_segment.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/io/segment.h>

using cg::point_2f;
using cg::point_2;


struct triangle_contains_point_viewer : cg::visualization::viewer_adapter
{
    class visitor_t : public boost::static_visitor<>
    {
    public:

        void operator()(boost::none_t &) {
            if (printer) (*printer).corner_stream() << "none" << cg::visualization::endl;
        }

        void operator()(cg::segment_2 & s) {
            if (printer) (*printer).corner_stream() << "[" << s[0] << ", " << s[1] << "]" << cg::visualization::endl;
        }

        void operator()(cg::point_2 & s) {
            if (printer) (*printer).corner_stream() << s << cg::visualization::endl;
            if (drawer) drawer->draw_point(s, 5);
        }

        static visitor_t print_visitor (cg::visualization::printer_type & printer)
        {
           visitor_t v;
           v.printer = &printer;
           return v;
        }

        static visitor_t draw_visitor (cg::visualization::drawer_type & drawer)
        {
           visitor_t v;
           v.drawer = &drawer;
           return v;
        }

        cg::visualization::printer_type * printer = nullptr;
        cg::visualization::drawer_type * drawer = nullptr;

    };

    triangle_contains_point_viewer()
        : s1(point_2(0, 0), point_2(100, 100)),
          s2(point_2(100, 0), point_2(0, 100))
    {}

    void draw(cg::visualization::drawer_type& drawer) const
    {
        drawer.set_color(Qt::white);

        if (cg::has_intersection(s1, s2))
        {
            drawer.set_color(Qt::green);
        }

        drawer.draw_line(s1[0], s1[1]);
        drawer.draw_line(s2[0], s2[1]);

        auto is = cg::intersection(s1, s2, -6);
        visitor_t visitor = visitor_t::draw_visitor(drawer);
        is.apply_visitor(visitor);
    }

    void print(cg::visualization::printer_type& p) const
    {
        p.corner_stream() << "press mouse rbutton near segment vertex to move it"
                          << cg::visualization::endl
                          << "if segments are green, they have intersection"
                          << cg::visualization::endl;

        auto is = cg::intersection(s1, s2, -1020);
        visitor_t visitor = visitor_t::print_visitor(p);
        is.apply_visitor(visitor);
    }

    bool on_press(const point_2f& p)
    {
        for (size_t l = 0; l != 2; ++l)
        {
            if (fabs(p.x - s1[l].x) < 4 && fabs(p.y - s1[l].y) < 4)
            {
                idx_ = l;
                is_s1 = true;
                return true;
            }
        }

        for (size_t l = 0; l != 2; ++l)
        {
            if (fabs(p.x - s2[l].x) < 4 && fabs(p.y - s2[l].y) < 4)
            {
                idx_ = l;
                is_s1 = false;
                return true;
            }
        }

        return false;
    }

    bool on_release(const point_2f& p)
    {
        idx_.reset();
        return false;
    }

    bool on_move(const point_2f& p)
    {
        current_point_ = p;

        if (!idx_)
        {
            return true;
        }

        if (is_s1)
        {
            s1[*idx_] = p;
        }
        else
        {
            s2[*idx_] = p;
        }

        return true;
    }

private:
    cg::segment_2 s1, s2;

    bool is_s1;
    boost::optional<size_t> idx_;
    boost::optional<cg::point_2> current_point_;
};

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    triangle_contains_point_viewer viewer;
    cg::visualization::run_viewer(&viewer, "Segment intersects segment");
}
