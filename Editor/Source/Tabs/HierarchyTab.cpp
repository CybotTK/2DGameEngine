#include "Tabs/HierarchyTab.h"

#include "Engine.h"

#include "Editor/UI/Props.h"

HierarchyTab::HierarchyTab() {
	name = "Hierarchy";
}

HierarchyTab::~HierarchyTab() {
}

void HierarchyTab::DrawUI() {
	static bool testB = false;
	static std::string testField;
	static int testInt = 0;
	static float testFloat = 0.f;

	static glm::vec2 testVec;
	
	static glm::vec3 testColor3;
	static glm::vec4 testColor4;

	if (ui::Header("Testing UI")) {
		ui::Prop("testB", &testB);
		ui::Prop("testField", &testField);
		ui::Prop("testInt", &testInt);
		ui::Prop("testFloat", &testFloat);
	}

	ui::Separator();

	ui::Prop("testVec", &testVec);

	ui::Separator();

	ui::PropColor("Color 3", &testColor3);
	ui::PropColor("Color 4", &testColor4);
}
