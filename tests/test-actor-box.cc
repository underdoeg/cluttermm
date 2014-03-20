/* Copyright (C) 2014 The cluttermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <cluttermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  //a return value to allow make check to output a useful summary:
  int errorval(0);

  int int_a(1);
  int int_b(2);
  int int_c(400);
  int int_d(500);
  std::cout << "Creating Clutter::ActorBox with (int) values:"<< int_a << "/" << int_b << " and " <<   int_c << "/" << int_d << std::endl;

  Clutter::ActorBox box1 = Clutter::ActorBox( int_a, int_b, int_c, int_d );

  if(  ( box1.get_x() != int_a ) || ( box1.get_y() != int_b ) )
  {
    errorval++;
    std::cerr << "Getting incorrect values from Box1: " << box1.get_x() <<
     " should be " << int_a << " , " << box1.get_y() << "should be " <<
      int_b << std::endl;
  }
  if(  ( box1.get_width() != ( int_c - int_a ) ) ||
    ( box1.get_height() !=  (int_d - int_b ) ) )
  {
    errorval++;
    std::cerr << "Getting incorrect values from Box1: " << box1.get_width() <<
     " should be " << int_c - int_a << " , " << box1.get_height() << "should be " <<
       int_d - int_b << std::endl;
  }

  // copy and (in)equality:
  Clutter::ActorBox box2 = box1;

  if(box1 != box2)
  {
   errorval+= 10;
    std::cerr << " box1 and box2 not equal." << std::endl;
    std::cerr << "box1: origin " << box1.get_x() << "/" << box1.get_y() <<
      ", width = " << box1.get_width() << ", height = " << box1.get_height()
      <<std::endl;
  }

  //get and set origin (and default constructor):
  Clutter::ActorBox box3;
  float new_origin_x(100);
  float new_origin_y(101);

  box3.set_origin( new_origin_x, new_origin_y );
  float origin_x(0);
  float origin_y(0);
  box3.get_origin(origin_x, origin_y);

  if( ( origin_x != new_origin_x ) || ( origin_y != new_origin_y )  )
  {
    errorval += 20;
    std::cerr<< "get/set origin not correct: Set " << new_origin_x << "/ " <<
      new_origin_y << "; returned " <<
      origin_x  << "/ " << origin_y <<std::endl;
  }

  //get and set size:
  float new_size_x(200);
  float new_size_y(201);
  box3.set_size( new_size_x, new_size_y );

  float size_x(0);
  float size_y(0);
  box3.get_size(size_x, size_y);

  if( ( size_x != new_size_x ) || ( size_y != new_size_y )  )
  {
    errorval += 30;
    std::cerr << "get/set size not correct: Set " << new_size_x << "/ " <<
      new_size_y << "; returned " <<
      size_x  << "/ " << size_y <<std::endl;
  }

  //get_area:
  if( box1.get_area() != ( (int_d - int_b ) * ( int_c - int_a ) ) )
  {
    errorval += 100;
    std::cerr<< "get area incorrect for box1 " << box1.get_area() << " vs " <<
    ( (int_d - int_b ) * ( int_c - int_a ) ) << std::endl;
  }

  if( box3.get_area() != ( new_size_x * new_size_y ) )
  {
    errorval += 200;
    std::cerr<< "get area incorrect for box3 " << box3.get_area() << " vs " <<
    new_size_x * new_size_y << std::endl;
  }

  // contains:
  Clutter::ActorBox box4(30, 30, 100, 101);
  // outside:
  if( box4.contains(25, 50) )
  {
    errorval+= 1000;
    std::cerr << "ActorBox::contains is wrong: box4 contains 25-50." << std::endl;
  }
  // inside:
  if( box4.contains(50, 50) == false)
  {
    errorval += 2000;
    std::cerr << " ActorBox::contains : 30, 30, 100, 101 doesn't contain 50-50." << std::endl;
  }

  // TODO: clamp_to_pixel, interpolate, unite.

  return errorval;
}
