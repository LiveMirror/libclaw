/*
  CLAW - a C++ Library Absolutely Wonderful

  CLAW is a free library without any particular aim but being useful to 
  anyone.

  Copyright (C) 2005-2011 Julien Jorge

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  contact: julien.jorge@gamned.org
*/
/**
 * \file claw/curve.hpp
 * \brief Claw's implementation of B�zier curves.
 * \author Julien Jorge
 */
#ifndef __CLAW_MATH_CURVE_HPP__
#define __CLAW_MATH_CURVE_HPP__

#include <claw/coordinate_traits.hpp>

namespace claw
{
  namespace math
  {
    /**
     * \brief Implementation of the B�zier curve.
     *
     * The curve is made of a sequence of points, each of which having a
     * direction telling how the curve enters the point and how to leave.
     *
     * \author Julien Jorge
     */
    template< typename C, typename Traits = coordinate_traits<C> >
    class curve
    {
    public:
      /** \brief The type of the coordinates of the curve. */
      typedef C coordinate_type;

      /** \brief The traits provide an access to the properties of the
          coordinates. */
      typedef Traits coordinate_traits_type;

      /** \brief The type of the components of the coordinates. */
      typedef typename coordinate_traits_type::value_type value_type;

      /**
       * \brief The control_point class describes a control point of the curve,
       *        with the direction of the curve before and after the point.
       * \author Julien Jorge
       */
      class control_point
      {
      public:
        /** \brief The type of the coordinates of the curve. */
        typedef C coordinate_type;

        /** \brief The traits provide an access to the properties of the
            coordinates. */
        typedef Traits coordinate_traits_type;

        /** \brief The type of the components of the coordinates. */
        typedef typename coordinate_traits_type::value_type value_type;

      public:
        control_point();
        explicit control_point( const coordinate_type& p );
        control_point
        ( const coordinate_type& p, const coordinate_type& input_direction,
          const coordinate_type& output_direction );

      private:
        /** \brief The position of this control point in the space. */
        coordinate_type m_position;

        /** \brief The point giving the direction of the curve before this
            control point. */
        coordinate_type m_input_direction;

        /** \brief The point giving the direction of the curve after this
            control point. */
        coordinate_type m_output_direction;

      }; // class control_point

      /**
       * \brief A section is a part of the curve between two control points.
       * \author Julien Jorge
       */
      class section
      {
      public:
        /** \brief The type of the coordinates of the curve. */
        typedef C coordinate_type;

        /** \brief The traits provide an access to the properties of the
            coordinates. */
        typedef Traits coordinate_traits_type;

        /** \brief The type of the components of the coordinates. */
        typedef typename coordinate_traits_type::value_type value_type;

        /** \brief The type of the iterators on the ends of the section. */
        typedef const_iterator iterator_type;

      public:
        section( const iterator_type& origin, const iterator_type& end );

        coordinate_type get_point_at( double t ) const;
        value_type get_tangent_at( double t ) const;

      private:
        value_type evaluate
        ( double t, value_type origin, value_type output_direction,
          value_type input_direction, value_type end ) const;
        value_type evaluate_derived
        ( double t, value_type origin, value_type output_direction,
          value_type input_direction, value_type end ) const;

      private:
        /** \brief The point at the beginning of the section. */
        const iterator_type m_origin;

        /** \brief The point at the end of the section. */
        const iterator_type m_end;

      }; // class section

    private:
      /** \brief The type of the container in which the control points are
          stored. */
      typedef std::list<control_point> control_point_list;

    public:
      /** \brief The type of the iterator on the control points of the curve. */
      typedef typename control_point_list::iterator iterator;

      /** \brief The type of the iterator on the control points of the curve. */
      typedef typename control_point_list::const_iterator const_iterator;

    public:
      void push_back( const control_point& p );
      void push_front( const control_point& p );
      void insert( const iterator& pos, const control_point& p );

      section get_section( const const_iterator& pos ) const;
      std::vector<value_type> get_y_at( value_type x ) const;

      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

    private:
      /** \brief The points of this curve. */
      control_point_list m_points;
      
    }; // class curve

  } // namespace math
} // namespace claw

#include "claw/impl/bezier.tpp"

#endif // __CLAW_MATH_CURVE_HPP__
