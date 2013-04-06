#pragma once

#include <cg/primitives/segment.h>
#include <cg/operations/orientation.h>
#include <cg/primitives/rectangle.h>
#include <iostream>

namespace cg
{
template<class Scalar>
bool segments_are_intersecting(cg::segment_2t<Scalar> const & a, cg::segment_2t<Scalar> const & b)
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
bool point_in_triangle(cg::point_2t<Scalar> const & p, cg::point_2t<Scalar> const & t1,
                       cg::point_2t<Scalar> const & t2, cg::point_2t<Scalar> const & t3)
{
    cg::orientation_t or1 = cg::orientation(p, t1, t2);
    cg::orientation_t or2 = cg::orientation(p, t2, t3);
    cg::orientation_t or3 = cg::orientation(p, t3, t1);
    //std::cout << or1 << std::endl << or2 << std::endl << or3 << std::endl;
    return (or1 == or2 && or2 == or3) || (or1 == or2 && or3 == cg::CG_COLLINEAR) ||
            (or2 == or3 && or1 == cg::CG_COLLINEAR) || (or1 == or3 && or2 == cg::CG_COLLINEAR) ||
            (or1 == or2 && or1 == cg::CG_COLLINEAR) || (or1 == or3 && or1 == cg::CG_COLLINEAR) ||
            (or2 == or3 && or2 == cg::CG_COLLINEAR);
}

template<class Scalar>
bool segment_intersects_triangle(cg::segment_2t<Scalar> const & seg, cg::point_2t<Scalar> const & t1,
                                 cg::point_2t<Scalar> const & t2, cg::point_2t<Scalar> const & t3)
{
    if (!cg::point_in_triangle(seg[0], t1, t2, t3) && !cg::point_in_triangle(seg[1], t1, t2, t3))
    {
        return false;
    }
    if (cg::point_in_triangle(seg[0], t1, t2, t3) && cg::point_in_triangle(seg[1], t1, t2, t3))
    {
        return true;
    }
    return (cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(t1, t2)) ||
            cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(t2, t3)) ||
            cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(t3, t1)));
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
    return cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(p1, p2)) ||
            cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(p2, p3)) ||
            cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(p3, p4)) ||
            cg::segments_are_intersecting(seg, cg::segment_2t<Scalar>(p4, p1));
}
}
