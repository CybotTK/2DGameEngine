#ifndef PYTHON_ENV_H
#define PYTHON_ENV_H

#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

class PythonEnv {
public:
	PythonEnv();
	virtual ~PythonEnv();

	static void Run(const std::string& code, py::object locals = py::object());
private:
	py::scoped_interpreter m_guard;
};

#endif // !PYTHON_ENV_H
