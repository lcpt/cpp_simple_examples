#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/class.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/raw_function.hpp>

using namespace boost::python;

tuple f(int x = 1, double y = 4.25, char const* z = "wow")
{
    return make_tuple(x, y, z);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(f_overloads, f, 0, 3)


struct X
{
    tuple f(int x = 1, double y = 4.25, char const* z = "wow")
    {
        return make_tuple(x, y, z);
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(X_f_overloads, X::f, 0, 3)

tuple raw_func(tuple args, dict kw)
{
    return make_tuple(args, kw);
}

BOOST_PYTHON_MODULE(docstrings_example)
{
    def("f", f, (arg("x")=1, arg("y")=4.25, arg("z")="wow")
        , "This is f's docstring"
        );

    def("raw", raw_function(raw_func));

    def("f1", f, f_overloads("f1's docstring", args("x", "y", "z")));


    class_<X>("X", "This is X's docstring", init<>(args("self")))
        .def("f", &X::f
             , "This is X.f's docstring"
             , args("self","x", "y", "z"))

        ;

}
