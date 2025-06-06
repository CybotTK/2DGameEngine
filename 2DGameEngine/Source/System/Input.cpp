#include "System/Input.h"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

Input::Input() {
	quit = false;
	resized = false;
	mouseMotion = { 0.f, 0.f };
	mouseScrollY = 0.0f;
}

Input::~Input() {
	sdlEvents.clear();
}

void Input::Update() {
	resized = false;

	sdlEvents.clear();
	mouseMotion = { 0.f, 0.f };
	mouseScrollY = 0.0f;

	for (auto& [code, state] : inputStatus) {
		state.pressed = false;
		state.released = false;
	}

	SDL_Event event;
	InputCode input;

	while (SDL_PollEvent(&event) > 0)
	{
		sdlEvents.push_back(event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					resized = true;
				}
				break;
			case SDL_KEYDOWN:
				input = { InputType::Key, event.key.keysym.scancode };
				if (!inputStatus[input].active) {
					inputStatus[input].pressed = true;
				}
				inputStatus[input].active = true;
				inputStatus[input].released = false;
				break;
			case SDL_KEYUP:
				input = { InputType::Key, event.key.keysym.scancode };
				inputStatus[input].pressed = false;
				inputStatus[input].released = true;
				inputStatus[input].active = false;
				break;
			case SDL_MOUSEMOTION:
				mouseMotion.x = (float)event.motion.xrel;
				mouseMotion.y = (float)event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				input = { InputType::Mouse };
				input.mouseButton = event.button.button;
				if (!inputStatus[input].active) {
					inputStatus[input].pressed = true;
				}
				inputStatus[input].released = false;
				inputStatus[input].active = true;
				break;
			case SDL_MOUSEBUTTONUP:
				input = { InputType::Mouse };
				input.mouseButton = event.button.button;
				inputStatus[input].pressed = false;
				inputStatus[input].released = true;
				inputStatus[input].active = false;
				break;
			case SDL_MOUSEWHEEL:
				mouseScrollY = (float)event.wheel.y;
				break;
		}
	}

	//TO DO SDL_DROPFILE
}

void Input::ForceQuit() {
	quit = true;
}

void Input::RefuseQuitStatus() {
	quit = false;
}

bool Input::GetQuitStatus() {
	return quit;
}

bool Input::HasResized() {
	return resized;
}

bool Input::Pressed(const InputCode& inputKey) {
	return inputStatus[inputKey].pressed;
}

bool Input::Active(const InputCode& inputKey) {
	return inputStatus[inputKey].active;
}

bool Input::Released(const InputCode& inputKey) {
	return inputStatus[inputKey].released;
}

glm::vec2 Input::GetMouseMotion() const {
	return mouseMotion;
}

float Input::GetMouseScrollY() const {
	return mouseScrollY;
}
