#include "Python/PythonScript.h"

#include "Python/PythonEnv.h"

#include "Editor/UI/Props.h"
#include "Editor/ImGui/imgui.h"
#include "Editor/ImGui/TextEditor.h"

PythonScript::PythonScript() {
	code = R"(
import engine

class MyComponent(engine.Component):
	def start(self):
		pass

	def update(self):
		owner = self.getOwner()
		input = engine.getApp().input
)";
}

PythonScript::~PythonScript() {

}

void PythonScript::DrawUI() {
	ui::ObjectHeader(&debug.name, "Python Script");
    
	if (ui::Header("Script Editor")) {
		ui::PropScript("Script Editor", &code);
	}
}

void PythonScript::Run() {
	PythonEnv::Run(code);
}
