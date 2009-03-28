#include <cluttermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  std::cout << "Creating Clutter::Interval with (int) values: 10, 20" << std::endl;

  Glib::RefPtr<Clutter::Interval> interval1 = Clutter::Interval::create(10, 20);
  Glib::Value<int> initial1, final1, compute1;
  initial1.init(initial1.value_type());
  final1.init(final1.value_type());
  compute1.init(compute1.value_type());

  interval1->get_interval(initial1, final1);
  std::cout << "Getting values from created interval: " << initial1.get() << ", " << final1.get() << std::endl;

  interval1->compute_value(0.5, compute1);
  std::cout << "Computing a value with factor = 0.5: " << compute1.get() << std::endl << std::endl;


  Glib::Value<double> initial2, final2, compute2;
  initial2.init(initial2.value_type());
  final2.init(final2.value_type());
  compute2.init(compute2.value_type());
  initial2.set(10.35);
  final2.set(20.73);

  std::cout << "Creating Clutter::Interval with Glib::Value<double> values: " << initial2.get() << ", " << final2.get() << std::endl;

  Glib::RefPtr<Clutter::Interval> interval2 = Clutter::Interval::create_with_values(initial2, final2);

  initial2.reset();
  final2.reset();

  interval2->get_interval(initial2, final2);
  std::cout << "Getting values from created interval: " << initial2.get() << ", " << final2.get() << std::endl;

  interval2->compute_value(0.7, compute2);
  std::cout << "Computing a value with factor = 0.7: " << compute2.get() << std::endl;

  return 0;
}
