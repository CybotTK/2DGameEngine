#include "Editor/EditorTab.h"

#include "Editor/ImGui/imgui.h"

EditorTab::EditorTab() {
    
}

EditorTab::EditorTab(const std::string& tabName) {
    name = tabName;
}

EditorTab::~EditorTab() {

}

bool EditorTab::DrawTab() {
    ImGui::Begin(name.c_str(), &active, m_flags);
    bool out = ImGui::IsWindowHovered();

    DrawUI();
    ImGui::End();

    return out;
}

void EditorTab::DrawUI() {
    ImGui::Text("Empty Tab");
}
