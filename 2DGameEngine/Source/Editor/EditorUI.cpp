#include "Editor/EditorUI.h"
#include "Editor/EditorTheme.h"

#include "Editor/ImGui/imgui.h"
#include "Editor/ImGui/imgui_impl_sdl2.h"
#include "Editor/ImGui/imgui_impl_opengl3.h"

#include "Engine.h"

EditorUI::EditorUI() : viewport(1280, 720){
	auto app = App::Get();

	//ImGui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

	// Multi Viewport stuff
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplSDL2_InitForOpenGL(app->m_window.GetSDLWindow(), app->m_window.GetContext());
	ImGui_ImplOpenGL3_Init("#version 430 core"); 

	// Fonts:
	io.Fonts->AddFontDefault();

	// UI Theme
	UI::SetTheme();

	// Testing:
	tabs.push_back(new EditorTab("Tab 1"));
	tabs.push_back(new EditorTab("Tab 2"));
	tabs.push_back(new EditorTab("Tab 3"));
	tabs.push_back(new EditorTab("Tab 4"));
}

EditorUI::~EditorUI() {
	// Remove the tabs
	for (auto tab : tabs) {
		delete tab;
	}
	tabs.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void EditorUI::Update() {
	auto app = App::Get();
	for (SDL_Event ev : app->input.sdlEvents) {
		ImGui_ImplSDL2_ProcessEvent(&ev);
	}
}

void EditorUI::Draw() {
	auto app = App::Get();

	FrameBuffer::UseDefault(); //Screen
	app->m_window.UpdateViewport();

	RenderBegin();
	Render();
	RenderEnd();
}

void EditorUI::RenderBegin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();

	ImGui::NewFrame();
}

void EditorUI::Render() {
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size, ImGuiCond_Always);

	auto flags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | 
		ImGuiWindowFlags_NoTitleBar | 
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse;
	
	// Top menu
	flags |= ImGuiWindowFlags_MenuBar;

	if (ImGui::Begin("EditorMain", 0, flags)) {
		ImGuiID dockspaceId = ImGui::GetID("dockspace");
		ImGui::DockSpace(dockspaceId, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::End();
	}

	DrawTabs();
}

void EditorUI::RenderEnd() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Multi Viewport
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void EditorUI::DrawTabs() {
	for (auto tab : tabs) {
		tab->DrawTab();
	}
	
	/*
	auto app = App::Get();

	ImGui::Begin("Testing tabs");

	ImGui::Text("Viewport Test");

	bool gameLogic = app->IsGameLogicEnabled();
	ImGui::Checkbox("Run Logic", &gameLogic);

	if (gameLogic) {
		app->EnableGameLogic();
	}
	else {
		app->DisableGameLogic();
	}

	ImGui::Image(
		viewport.GetTexture(0)->GetTextureID(),
		{ 1280.f, 720.f },			// Size
		{ 0.f, 1.f }, { 1.f, 0.f }, // UV0, UV1
		{ 1.f, 1.f, 1.f, 1.f }		// Tint
	);

	ImGui::End();*/
}
