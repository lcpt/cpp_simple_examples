#include <iostream>
#include <memory> //std::shared_ptr
#include <deque>

struct Base
  {
    int a;
    Base(const int &aa)
      {
	a= aa;
	std::cout << "  Base::Base()\n";
      }
    // Note: non-virtual destructor is OK here
    ~Base(void)
      {
	std::cout << "  Base::~Base(): "
		  << this->a << std::endl;
      }
  };

struct Derived: public Base
  {
    double b;
    Derived(const int &a, const double &bb)
      : Base(a)
      {
	b= bb;
	std::cout << "  Derived::Derived()\n";
      }
    ~Derived()
      {
        std::cout << "  Derived::~Derived(): "
		  << this->b << std::endl;
      }
  };


int main(void)
  {
    std::deque<std::shared_ptr<Base> > container;
    std::shared_ptr<Base> p = std::make_shared<Derived>(1,2.0);
    container.push_back(p);
    std::shared_ptr<Base> q = std::make_shared<Derived>(2,4.0);
    container.push_back(q);
    std::shared_ptr<Base> r = std::make_shared<Derived>(3,6.0);
    container.push_back(r);

  }
