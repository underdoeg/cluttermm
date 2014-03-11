#include <cluttermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  std::cout << "Creating Clutter::Point with (int) values: 8, 15" << std::endl;

  Clutter::Point point0(0, 0);
  Clutter::Point point1(8, 15);

  std::cout<<"Initialisation: point0 = "<<point0.get_x()<<
    "/ "<<point0.get_y()<<std::endl;
  std::cout<<"and point1 = "<<point1.get_x()<<"/ "<<point1.get_y()<<std::endl;

  float x_dist(0);
  float y_dist(0);
  float dist = point0.distance(point1, x_dist, y_dist);
  std::cout << "Distance between the two is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;

  //make life easy and use the 3/4/5 triangle now:
  point0.set_x(7);
  point0.set_y(6);

  point1.set_x(10);
  point1.set_y(10);

  dist = point0.distance(point1, x_dist, y_dist);
  std::cout << "Reset values; now distance is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;

  //reversing to check negative values:

  point0.set_x(10);
  point0.set_y(10);

  point1.set_x(7);
  point1.set_y(6);

  dist = point0.distance(point1, x_dist, y_dist);
  std::cout << "Reversed values; now distance is "<< dist <<
    " with x and y distances " << x_dist << "/ " << y_dist << std::endl;

  //point equality function check:
  Clutter::Point comp_point(7.0 ,6.0);
  if(comp_point == point1){
    std::cout << "Points equal." << std::endl;
  }
  else{
    std::cout<< "Points not equal: comp = " << comp_point.get_x() <<
    "/" << comp_point.get_y() << " vs " <<
    point1.get_x() << "/" << point1.get_y() << std::endl;
  }

  return 0;
}
