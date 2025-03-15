#include "Python/PythonObj.h"

#include <iostream>

void __ShowPythonObjectError(const std::string& method, const std::string& error) {
	std::cout << "Python Error:" << method << "\n\tError: " << error << '\n';
}

PythonObj::PythonObj(const std::string& code) {
	m_code = code; 

	try {
		m_object = new py::object(py::eval(code));
	}
	catch (py::error_already_set e) {
		__ShowPythonObjectError(code, e.what());
	}
}

PythonObj::~PythonObj() {
	if (m_object) {
		try {
			delete m_object;
		}
		catch (py::error_already_set e) {
			__ShowPythonObjectError("Destroying Python Object", e.what());
		}
	}
}

bool PythonObj::HasAttr(const std::string& attr) {
	try {
		return !m_object->attr(attr.c_str()).is_none();
	}
	catch (py::error_already_set& e) {
		__ShowPythonObjectError(attr, e.what());
		return false;
	}
}

void PythonObj::Call(const std::string& method) {
	if (IsValid() && !IsNone()) {
		try {
			auto mt = m_object->attr(method.c_str());
			if (!mt.is_none()) {
				mt();
			}
		}
		catch (py::error_already_set e) {
			__ShowPythonObjectError(method, e.what());
		}
		catch (std::exception e) {

		}
	}
}

void PythonObj::Call(const std::string& method, const py::object& obj) {
	if (IsValid()) {
		try {
			m_object->attr(method.c_str())(obj);
		}
		catch (py::error_already_set e) {
			__ShowPythonObjectError(method, e.what());
		}
		catch (std::exception e) {

		}
	}
}

bool PythonObj::IsValid() {
	return m_object != nullptr;
}

bool PythonObj::IsNone() {
	return m_object && m_object->is_none();
}
