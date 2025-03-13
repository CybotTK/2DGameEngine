#include "Python/PythonEnv.h"

#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace py::literals;

void __DoSomething(int value) {
	std::cout << value << " -> Something happened!\n";
}

void __PleaseWorkSomething() {
	std::cout << "PLEASE WORK\n";
}

#define PY_REFFERENCE py::return_value_policy::reference

PYBIND11_EMBEDDED_MODULE(engine, m) {
	m.def("doSomething", &__DoSomething);
}

void __ShowPythonError(const std::string& method, const std::string& error) {
	std::cout << "Python Error:" << method << "\n\tError: " << error << '\n';
}

PythonEnv::PythonEnv() {
	auto engine = py::module_::import("engine");
	engine.def("pleaseWorkSomething", &__PleaseWorkSomething);
}

PythonEnv::~PythonEnv() {
}

void PythonEnv::Run(const std::string& code) {
	try {
		py::exec(code, py::globals());
	}
	catch (py::error_already_set e) {
		__ShowPythonError(code, e.what());
	}
}
