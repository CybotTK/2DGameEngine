#include "Editor/EditorUI.h"

#include "Editor/ImGui/imgui.h"
#include "Editor/ImGui/imgui_impl_sdl2.h"
#include "Editor/ImGui/imgui_impl_opengl3.h"

#include "Engine.h"

EditorUI::EditorUI() {
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

	// ImGui needs a VAO in order to work
	glGenVertexArrays(1, &m_vao);
}

EditorUI::~EditorUI() {
	//ImGui cleanup
	//glDeleteVertexArrays(1, &m_vao);

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
	ImGui::Begin("Testing tabs");

	ImGui::Text("Hello, world!");

	ImGui::End();
}
