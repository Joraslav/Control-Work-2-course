#include <iostream>  // std::{cin, cout, endl}
#include <stdexcept> // std::runtime_error
#include <utility>   // std::move

#include "SmartPointer.hpp"

template <class T>
auto output(T const &t)
{
  try
  {
    std::cout << t << std::endl;
  }
  catch (std::runtime_error const &re)
  {
    std::cout << re.what() << std::endl;
  }
}

int main()
{
  using element_type = int;
  using smart_pointer_type = SmartPointer<element_type>;

  smart_pointer_type st1;
  output(st1);
  smart_pointer_type st2{st1};
  output(st1);
  output(st2);
  smart_pointer_type st3{std::move(st2)};
  output(st2);
  output(st3);

  smart_pointer_type st4 = new element_type{42};
  output(st4);
  smart_pointer_type st5 = st4;
  output(st4);
  output(st5);
  smart_pointer_type st6 = std::move(st5);
  output(st5);
  output(st6);

  return 0;
}