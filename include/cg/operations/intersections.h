#pragma once

#include <cg/primitives/segment.h>
#include <cg/operations/orientation.h>
#include <cg/primitives/rectangle.h>
#include <cg/primitives/triangle.h>
#include <cg/operations/belongings.h>

namespace cg
{
template<class Scalar>
bool segment_intersects_segment(cg::segment_2t<Scalar> const & a, cg::segment_2t<Scalar> const & b)
{
    if (cg::orientation(a[0], a[1], b[0]) == cg::CG_COLLINEAR &&
            cg::orientation(a[0], a[1], b[1]) == cg::CG_COLLINEAR)
    {
        return (b[0] >= cg::min(a) && b[0] <= cg::max(a)) ||
                (b[1] >= cg::min(a) && b[1] <= cg::max(a));
    }
    return cg::orientation(a[0], a[1], b[0]) != cg::orientation(a[0], a[1], b[1]) &&
            cg::orientation(b[0], b[1], a[0]) != cg::orientation(b[0], b[1], a[1]);
}

template<class Scalar>
bool segment_intersects_triangle(cg::segment_2t<Scalar> const & seg, cg::triangle_2t<Scalar> const & t)
{
    if (!cg::point_in_triangle(seg[0], t) && !cg::point_in_triangle(seg[1], t))
    {
        return false;
    }
    if (cg::point_in_triangle(seg[0], t) && cg::point_in_triangle(seg[1], t))
    {
        return true;
    }
    return (cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(t[0], t[1])) ||
            cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(t[1], t[2])) ||
            cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(t[2], t[0])));
}

template<class Scalar>
bool segment_intersects_rectangle(cg::segment_2t<Scalar> const & seg, cg::rectangle_2t<Scalar> const & rect)
{
    if (rect.x.contains(seg[0].x) && rect.y.contains(seg[0].y) &&
            rect.x.contains(seg[1].x) && rect.y.contains(seg[1].y))
    {
        return true;
    }
    if (!rect.x.contains(seg[0].x) && !rect.y.contains(seg[0].y) &&
            !rect.x.contains(seg[1].x) && !rect.y.contains(seg[1].y))
    {
        return false;
    }
    cg::point_2t<Scalar> p1(rect.x.inf, rect.y.inf);
    cg::point_2t<Scalar> p2(rect.x.sup, rect.y.inf);
    cg::point_2t<Scalar> p3(rect.x.inf, rect.y.sup);
    cg::point_2t<Scalar> p4(rect.x.sup, rect.y.sup);
    return cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(p1, p2)) ||
            cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(p2, p3)) ||
            cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(p3, p4)) ||
            cg::segment_intersects_segment(seg, cg::segment_2t<Scalar>(p4, p1));
}
}
