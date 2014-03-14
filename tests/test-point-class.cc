#include <cluttermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  //an error return value to add information to make check:
  int errorval(0);

  const int p1x(8);
  const int p1y(15);
  Clutter::Point point0;
  Clutter::Point point1(p1x, p1y);

  if( ( point0.get_x() != 0) || ( point0.get_y() != 0 ) ||
    ( point1.get_x() != p1x ) || ( point1.get_y() != p1y ) )
  {
    std::cout << "Problem creating points: p0 = " << point0.get_x() << "/" <<
      point0.get_y() << " and p1 = " << point1.get_x() << "/" << point1.get_y()
      << std::endl;
      errorval++;
  }

  float x_dist(0);
  float y_dist(0);
  float dist = point0.distance(point1, x_dist, y_dist);
  if(dist != 17)
  {
    std::cout << "Distance between the two ( should be 17 ) is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;
    errorval += 10;
  }

  //use the 3/4/5 triangle now:
  point0.set_x(7);
  point0.set_y(6);

  point1.set_x(10);
  point1.set_y(10);

  dist = point0.distance(point1, x_dist, y_dist);
  if(dist != 5)
  {
    std::cout << "Distance between the two is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;
    errorval += 20;
  }

  //reversing to check negative values:

  point0.set_x(10);
  point0.set_y(10);

  point1.set_x(7);
  point1.set_y(6);

  dist = point0.distance(point1, x_dist, y_dist);
  if(dist != 5)
  {
    std::cout << "Distance between the two is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;
    errorval += 30;
  }

  //point equality function check:
  const Clutter::Point comp_point(7.0 ,6.0);
  if(comp_point != point1)
  {
    std::cerr << "double Point unequal to equivalent double point." << std::endl;
    errorval += 100;
  }

  //point equality function check for integer values:
  const Clutter::Point comp2_point(7 ,6);
  if(comp2_point != point1)
  {
    std::cerr << "int Point unequal to equivalent double point." << std::endl;
    errorval += 200;
  }

  std::cout<< "errorval: " << errorval << std::endl;

  return errorval;
}
