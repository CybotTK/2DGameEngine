#ifndef PYTHON_SCRIPT_H
#define PYTHON_SCRIPT_H

#include <string>

#include "Asset/Object.h"

class PythonScript : public Object {
public:
	PythonScript();
	virtual ~PythonScript();

	virtual void Save(File* file) override;
	virtual void Load(File* file) override;

	virtual void DrawUI() override;

	void Run();

	std::string code;
};

#endif // !PYTHON_SCRIPT_H
