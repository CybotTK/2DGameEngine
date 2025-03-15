#include "Python/PythonEnv.h"

#include <iostream>

#include "Python/PythonRegistry.h"

namespace py = pybind11;
using namespace py::literals;

PYBIND11_EMBEDDED_MODULE(engine, m) {
	PyRegisterInputTypes(m);
	PyRegisterMath(m);

	PyRegisterEngineCode(m);
}

void __ShowPythonError(const std::string& method, const std::string& error) {
	std::cout << "Python Error:" << method << "\n\tError: " << error << '\n';
}

PythonEnv::PythonEnv() {
	auto engine = py::module_::import("engine");
}

PythonEnv::~PythonEnv() {
}

void PythonEnv::Run(const std::string& code, py::object locals) {
	try {
		py::exec(code, py::globals(), locals);
	}
	catch (py::error_already_set e) {
		__ShowPythonError(code, e.what());
	}
}
