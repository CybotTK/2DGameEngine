#include "Tabs/DetailsTab.h"

#include "Engine.h"

#include "Editor/UI/Props.h"

DetailsTab::DetailsTab() {
	name = "Details";
}

DetailsTab::~DetailsTab() {

}

void DetailsTab::DrawUI() {
	auto app = App::Get();
	auto editor = app->GetEditor();

	if (editor->selected) {
		editor->selected->DrawUI();
	}
	else {
		ui::Text("Nothing selected.");
	}
}
