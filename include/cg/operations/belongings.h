#pragma once

#include <cg/operations/orientation.h>
#include <cg/primitives/triangle.h>
#include <cg/primitives/contour.h>
#include <iostream>

namespace cg
{
template<class Scalar>
bool point_in_triangle(cg::point_2t<Scalar> const & p, cg::triangle_2t<Scalar> const & t)
{
    cg::orientation_t or1 = cg::orientation(p, t[0], t[1]);
    cg::orientation_t or2 = cg::orientation(p, t[1], t[2]);
    cg::orientation_t or3 = cg::orientation(p, t[2], t[0]);
    return (or1 == or2 && or2 == or3) || (or1 == or2 && or3 == cg::CG_COLLINEAR) ||
            (or2 == or3 && or1 == cg::CG_COLLINEAR) || (or1 == or3 && or2 == cg::CG_COLLINEAR) ||
            (or1 == or2 && or1 == cg::CG_COLLINEAR) || (or1 == or3 && or1 == cg::CG_COLLINEAR) ||
            (or2 == or3 && or2 == cg::CG_COLLINEAR);
}

template<class Scalar>
bool point_in_convex_contour(cg::point_2t<Scalar> const & p, cg::contour_2t<Scalar> const & con)
{
    typename cg::contour_2t<Scalar>::const_iterator l = lower_bound(con.begin() + 1, con.end(), p,
                                                                    [&con] (cg::point_2t<Scalar> const & p1, cg::point_2t<Scalar> const & p2) {return cg::orientation(con[0], p1, p2) == cg::contour_orientation(con) || cg::orientation(con[0], p1, p2) == cg::CG_COLLINEAR;});
    //std::cout << l - con.begin() << std::endl;
    return cg::point_in_triangle(p, cg::triangle_2t<Scalar>(con[0], con[l - con.begin() - 1], con[l - con.begin()]));
}
}
