#pragma once

#include <cg/operations/orientation.h>
#include <cg/primitives/triangle.h>

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
}
