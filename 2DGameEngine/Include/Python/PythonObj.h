#ifndef PYTHON_OBJ_H
#define PYTHON_OBJ_H

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

class PythonObj {
public:
	PythonObj(const std::string& code);
	virtual ~PythonObj();

	bool HasAttr(const std::string& attr);
	
	void Call(const std::string& method);
	void Call(const std::string& method, const py::object& obj);

	bool IsValid();
	bool IsNone();

	template <typename T>
	T Get(const std::string& attrName) {
		if (IsValid()) {
			auto at = m_object->attr(attrName.c_str());
			return at.cast<T>();
		}
		return T();
	}

	template <typename T>
	void Set(const std::string& attrName, T value) {
		if (IsValid()) {
			m_object->attr(attrName.c_str()) = py::cast(value);
		}
	}

	template <typename T>
	T Cast() {
		if (IsValid()) {
			return m_object->cast<T>();
		}
		return T();
	}
private:
	py::object* m_object = nullptr;
	std::string m_code;
};

#endif // !PYTHON_OBJ_H
