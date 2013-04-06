#pragma once

#include <stdexcept>
#include <boost/lexical_cast.hpp>

#include "point.h"

namespace cg
{
template<class Scalar>
struct triangle_2t
{
    triangle_2t() {};

    triangle_2t(cg::point_2t<Scalar> p1, cg::point_2t<Scalar> p2, cg::point_2t<Scalar> p3):
        p1(p1), p2(p2), p3(p3)
    {}

    point_2t<Scalar> const & operator[] (size_t i) const
    {
        switch (i)
        {
        case 0: return p1;
        case 1: return p2;
        case 2: return p3;
        default:
            throw std::logic_error("invalid index: " + boost::lexical_cast<std::string>(i));
        }
    }

    point_2t<Scalar> & operator[] (size_t i)
    {
        switch (i)
        {
        case 0: return p1;
        case 1: return p2;
        case 2: return p3;
        default:
            throw std::logic_error("invalid index: " + boost::lexical_cast<std::string>(i));
        }
    }

private:
    point_2t<Scalar> p1, p2, p3;
};
}
