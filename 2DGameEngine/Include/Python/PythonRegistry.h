#ifndef PYTHON_REGISTRY_H
#define PYTHON_REGISTRY_H

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

void PyRegisterEngineCode(py::module_& m);

void PyRegisterMath(py::module_& m);

void PyRegisterInputTypes(py::module_& m);

#endif // !PYTHON_REGISTRY_H
