#include <cstdlib>
#include <iostream>

#include "binsearchtree.h"

void print(int value) {
  std::cout << value << ", ";
}

class printer {
  std::ostream& o;
public:
  printer(std::ostream& o) : o(o) {}

  template <typename T>
  void operator()(const T& value) {
    o << value << ", ";
  }
};

int main()
{
  const int demoitems[] = { 5, 3, 9, 4, 11, 4, 1 };

  // Test insert and do_for_each.
  binsearchtree<int> t;
  for (int i = 0; i < sizeof(demoitems) / sizeof(demoitems[0]); ++i) {
    t.insert(demoitems[i]);

    // It should be sorted after each insert.
    t.do_for_each(print);
    std::cout << std::endl;
  }

  // Also works with function object (aka. functor).
  t.do_for_each(printer(std::cout));
  std::cout << std::endl;

  // Test copy constructor.
  printer p(std::cout);
  binsearchtree<int> s(t);
  t.insert(2);
  t.do_for_each(p);
  std::cout << std::endl;
  s.do_for_each(p);
  std::cout << std::endl;

  // Test operator=.
  s = t;
  s.do_for_each(p);
  std::cout << std::endl;

  // Test clear.
  t.clear();
  t.do_for_each(p);
  std::cout << std::endl;
  s.do_for_each(p);
  std::cout << std::endl;

  // TODO Test iterator.
  /*for (binsearchtree<int>::iterator it = s.begin(); it != s.end(); ++it) {
    p(*it);
  }*/

  return 0;
}

