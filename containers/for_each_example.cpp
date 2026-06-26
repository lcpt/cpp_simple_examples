// Source - https://stackoverflow.com/a/719491
// Posted by kyku
// Retrieved 2026-06-26, License - CC BY-SA 2.5

#include <iostream>
#include <functional>
#include <boost/bind/bind.hpp>
#include <vector>
#include <algorithm>

struct Foo
  {
    Foo(int value) : value_(value)
      {}

    void func(int value)
      {
        std::cout << "member = " << value_ << " argument = " << value << std::endl;
      }

  private:
    int value_;
  };

int main()
  {
    std::vector<Foo> foo_vector;

    for (int i = 0; i < 5; i++)
        foo_vector.push_back(Foo(i));

    std::for_each(foo_vector.begin(), foo_vector.end(),
		  boost::bind(&Foo::func, boost::placeholders::_1, 1));
  }
