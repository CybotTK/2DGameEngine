#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include "System/InputTypes.h"

class Input {
public:
	Input();
	virtual ~Input();

	virtual void Update();

	void ForceQuit();
	void RefuseQuitStatus();
	bool GetQuitStatus();
	bool HasResized();

	bool Pressed(InputCode& inputKey);
	bool Active(InputCode& inputKey);
	bool Released(InputCode& inputKey);

	glm::vec2 GetMouseMotion() const;
	float GetMouseScrollY() const;

	//We need this for ImGui
	std::vector<SDL_Event> sdlEvents;

private:
	struct KeyState
	{
		bool pressed = false;
		bool released = false;
		bool active = false;
	};

	std::unordered_map<InputCode, KeyState> inputStatus;

	bool quit = false;
	bool resized = false;

	glm::vec2 mouseMotion;
	float mouseScrollY = 0.0f;
};

#endif // INPUT_H