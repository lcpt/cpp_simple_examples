#include <boost/python.hpp>
#include <memory>
#include <iostream>

using namespace boost::python;

struct Foo {
    Foo(int v) : value(v) { std::cout << "Foo(" << value << ") constructed\n"; }
    ~Foo() { std::cout << "Foo(" << value << ") destroyed\n"; }

    void hello() const { std::cout << "Hello from Foo(" << value << ")\n"; }

    int value;
};

// --- 1. Owned instance (Python owns) ---
std::shared_ptr<Foo> make_owned(int v) {
    return std::make_shared<Foo>(v);
}

// --- 2. Borrowed instance (C++ owns) ---
Foo globalFoo(999);

Foo* get_borrowed() {
    return &globalFoo;  // still alive for entire program
}

BOOST_PYTHON_MODULE(example)
{
    class_<Foo, std::shared_ptr<Foo>>("Foo", init<int>())
        .def("hello", &Foo::hello)
        .def_readwrite("value", &Foo::value);

    // Python owns this one
    def("make_owned", &make_owned);

    // Python borrows this one (C++ owns it)
    def("get_borrowed", &get_borrowed,
        return_value_policy<reference_existing_object>());
}
