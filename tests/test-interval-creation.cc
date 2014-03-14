#include <cluttermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  //a return value to allow make check to output a useful summary:
  int errorval(0);

  const int int_a(10);
  const int int_b(20);

  Glib::RefPtr<Clutter::Interval> interval1 = Clutter::Interval::create(10, 20);
  Glib::Value<int> initial1, final1, compute1;
  initial1.init(initial1.value_type());
  final1.init(final1.value_type());
  compute1.init(compute1.value_type());

  interval1->get_interval(initial1, final1);
  if(  (int(initial1.get()) != int_a) || ( int(final1.get()) != int_b) )
  {
    errorval++;
    std::cerr << "Getting incorrect values from created interval: " <<
      initial1.get() << ", " << final1.get() << std::endl;
  }

  interval1->compute_value(0.5, compute1);
  std::cout << "Computing a value with factor = 0.5: " <<
                  compute1.get() << std::endl << std::endl;
  if( compute1.get() != (int_a + int_b ) /2 )
  {
    std::cerr << "Computed incorrect value with factor = 0.5: " <<
                  compute1.get() << std::endl << std::endl;
    errorval += 10;
  }

  const double dub_a(10.35);
  const double dub_b(20.73);

  Glib::Value<double> initial2, final2, compute2;
  initial2.init(initial2.value_type());
  final2.init(final2.value_type());
  compute2.init(compute2.value_type());
  initial2.set(dub_a);
  final2.set(dub_b);

  std::cout << "Creating Clutter::Interval with Glib::Value<double> values: " <<
                initial2.get() << ", " << final2.get() << std::endl;

  Glib::RefPtr<Clutter::Interval> interval2 = Clutter::Interval::create_with_values(initial2, final2);

  initial2.reset();
  final2.reset();

  interval2->get_interval(initial2, final2);
  if( ( dub_a != initial2.get() ) || ( dub_b != final2.get() ) )
  {
    std::cerr << "Getting incorrect values from created interval: " <<
              initial2.get() << ", " << final2.get() << std::endl;
    errorval += 100;
  }

  interval2->compute_value( 0.7, compute2 );
  double compval = dub_a + ( ( dub_b - dub_a ) / 2 );
  if( compute2.get() != compval )
  {
    std::cerr << "Error computing a value with factor = 0.7: " << compute2.get() << "; correct value is "<< compval << std::endl;
    errorval += 1000;
  }

  return errorval;
}
