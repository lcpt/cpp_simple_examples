
#include <boost/python.hpp>
#include <string>

// Compile once, get back a boost::python::object wrapping the code object
boost::python::object compile_script(const std::string& code,
                           const std::string& name = "<script>")
{
    PyObject* co = Py_CompileString(code.c_str(), name.c_str(), Py_file_input);
    if (!co) {
        boost::python::throw_error_already_set();
    }
    // handle<> takes ownership of the new reference
    return boost::python::object(boost::python::handle<>(co));
}

// Execute a previously-compiled code object against given globals/locals
boost::python::object exec_compiled(const boost::python::object& code,
                          boost::python::object globals,
                          boost::python::object locals)
{
    PyObject* result = PyEval_EvalCode(code.ptr(), globals.ptr(), locals.ptr());
    if (!result) {
        boost::python::throw_error_already_set();
    }
    return boost::python::object(boost::python::handle<>(result));
}

class ScriptRunner {
public:
    explicit ScriptRunner(const std::string& script_text) {
        code_ = compile_script(script_text);
        main_module_ = boost::python::import("__main__");
        main_namespace_ = main_module_.attr("__dict__");
    }

    boost::python::object run() {
        // Fresh locals each call if you don't want state to leak between runs;
        // reuse main_namespace_ as globals (mirrors what exec() does by default)
        boost::python::dict locals;
        return exec_compiled(code_, main_namespace_, locals);
    }

private:
    boost::python::object code_;
    boost::python::object main_module_;
    boost::python::object main_namespace_;
};
