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

std::ostream& operator<<(std::ostream& out, Clutter::Size size)
{
	out << size.get_width() << "/ " << size.get_height();
	return out;
}

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  //an error return value to add information to make check:
  int errorval(0);

  const int p1x(8);
  const int p1y(15);
  Clutter::Size size0;
  Clutter::Size size1(p1x, p1y);

  if( ( size0.get_width() != 0) || ( size0.get_height() != 0 ) ||
    ( size1.get_width() != p1x ) || ( size1.get_height() != p1y ) )
  {
    std::cerr << "Problem creating sizes: p0 = " << size0.get_width() << "/" <<
      size0.get_height() << " and p1 = " << size1.get_width() << "/" <<
      size1.get_height() << std::endl;
      errorval++;
  }

  //size equality:
  Clutter::Size comp_size(0 ,0);
  if(comp_size != size0)
  {
    std::cerr << "default Size unequal to (0, 0) " << comp_size <<" vs " << size0 << std::endl;
    errorval += 10;
  }

  Clutter::Size comp1_size(8.0 ,15.0);
  if(comp1_size != size1)
  {
    std::cerr << "double Size unequal to equivalent double size: " << comp1_size <<" vs " << size1 << std::endl;
    errorval += 10;
  }

  Clutter::Size comp2_size(8 ,15);
  if(comp2_size != size1)
  {
    std::cerr << "int Size unequal to equivalent double size: "  << comp2_size <<" vs " << size1 << std::endl;
    errorval += 20;
  }

  //get:
  if( (comp_size.get_width() != 0) || (comp1_size.get_width() != 8.0) ||
      (comp2_size.get_width() != 8) )
  {
    std::cerr << "failure in get_width(): " <<
    comp_size << " width = " <<  comp_size.get_width() << "; " <<
    comp1_size << " width = " <<  comp1_size.get_width() << "; " <<
    comp2_size << " width = " <<  comp2_size.get_width() << "; " << std::endl;
    errorval += 100;
  }

  if( comp_size.get_height() != 0)
  {
    std::cerr << "failure in get_height(): " <<
    comp_size << " height = " <<  comp_size.get_height() << std::endl;
     errorval += 200;
  }
  if( comp1_size.get_height() != 15.0)
  {
    std::cerr << "failure in get_height(): " << comp1_size << " height = " <<  comp1_size.get_height() << std::endl;
     errorval += 200;
  }
  if( comp2_size.get_height() != 15)
  {
    std::cerr << "failure in get_height(): " << comp2_size << " height = " <<  comp2_size.get_height() << std::endl;
     errorval += 200;
  }

 //set:
  int w1 = 53;
  double w2 = 75.0;
  float w3 = 13000;
  comp_size.set_width(w1);
  comp1_size.set_width(w2);
  comp2_size.set_width(w3);

  if( (comp_size.get_width() != w1) || (comp1_size.get_width() != w2) ||
      (comp2_size.get_width() != w3) )
  {
    std::cerr << "failure in set_width(): " <<
    comp_size << " width = " <<  comp_size.get_width() << "; " <<
    comp1_size << " width = " <<  comp1_size.get_width() << "; " <<
    comp2_size << " width = " <<  comp2_size.get_width() << "; " << std::endl;
    errorval += 1000;
  }

  int h1 = 28;
  double h2 = 56.3;
  float h3 = 7100;
  comp_size.set_height(h1);
  comp1_size.set_height(h2);
  comp2_size.set_height(h3);


  if( comp_size.get_height() != h1)
  {
    std::cerr << "failure in get_height(): " <<
    comp_size << " height = " <<  comp_size.get_height() << std::endl;
     errorval += 2000;
  }
  /**
   * This is guaranteed to fail as Size contains floats, so there is a
   * rounding error.
   * Left in to highlight the issue.
   *
  if( comp1_size.get_height() != h2)
  {
    std::cerr << "failure in get_height(): " << comp1_size << " height = " <<  comp1_size.get_height() << "; diff = " << comp1_size.get_height() - h2 << std::endl;
     errorval += 2000;
  }
  */
  if( comp2_size.get_height() != h3)
  {
    std::cerr << "failure in get_height(): " << comp2_size << " height = " <<  h3 << std::endl;
     errorval += 2000;
  }

  //output any error:
  if(errorval != 0)
  {
    std::cerr << "Error value: " << errorval << std::endl;
  }
  return errorval;
}
