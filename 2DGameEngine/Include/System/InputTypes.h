#ifndef INPUTTYPES_H
#define INPUTTYPES_H

#include <SDL2/SDL.h>
#include <functional>

enum class InputType {
	Key,
	Mouse
};

struct InputCode {
	InputType type;

	union {
		SDL_Scancode key;	// Scancode for keyboard input
		Uint8 mouseButton;	// Button code for mouse input
	};

	bool operator==(const InputCode& other) const {
		return type == other.type && key == other.key
				&& mouseButton == other.mouseButton;
	}
};

namespace std {
	template <>
	struct hash<InputCode> {
		std::size_t operator()(const InputCode& iCode) const {
			std::size_t typeHash = std::hash<int>()(static_cast<int>(iCode.type));
			std::size_t keyHash = std::hash<int>()(iCode.key);
			std::size_t mouseHash = std::hash<int>()(iCode.mouseButton);
			return typeHash ^ (keyHash << 1) ^ (mouseHash << 2);
		}
	};
}

#endif