#ifndef INPUTTYPES_H
#define INPUTTYPES_H

#include <SDL2/SDL.h>
#include <functional>

enum class InputType {
    None,
	Key,
	Mouse
};

struct InputCode {
	InputType type;

	union {
		SDL_Scancode key;	// Scancode for keyboard input
		Uint8 mouseButton;	// Button code for mouse input
	};

    // Default constructor
    InputCode() : type(InputType::None), key(SDL_SCANCODE_UNKNOWN) {}

    // Constructor for keyboard input
    InputCode(SDL_Scancode k) : type(InputType::Key) {
        key = k;
        mouseButton = 0; // Ensure the other union member does not hold garbage data
    }

    // Constructor for mouse input (with just InputType)
    InputCode(InputType type) : type(type), key(SDL_SCANCODE_UNKNOWN) {}

    // Constructor for mouse input (with button code)
    InputCode(Uint8 button) : type(InputType::Mouse), mouseButton(button) {}

    // Constructor for initializing with both InputType and Scancode
    InputCode(InputType type, SDL_Scancode k) : type(type), key(k) {}

    bool operator==(const InputCode& other) const {
        return type == other.type &&
            ((type == InputType::Key && key == other.key) ||
                (type == InputType::Mouse && mouseButton == other.mouseButton));
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

namespace InputKey {
    // Letters
    const InputCode KEY_A = { InputType::Key, SDL_SCANCODE_A };
    const InputCode KEY_B = { InputType::Key, SDL_SCANCODE_B };
    const InputCode KEY_C = { InputType::Key, SDL_SCANCODE_C };
    const InputCode KEY_D = { InputType::Key, SDL_SCANCODE_D };
    const InputCode KEY_E = { InputType::Key, SDL_SCANCODE_E };
    const InputCode KEY_F = { InputType::Key, SDL_SCANCODE_F };
    const InputCode KEY_G = { InputType::Key, SDL_SCANCODE_G };
    const InputCode KEY_H = { InputType::Key, SDL_SCANCODE_H };
    const InputCode KEY_I = { InputType::Key, SDL_SCANCODE_I };
    const InputCode KEY_J = { InputType::Key, SDL_SCANCODE_J };
    const InputCode KEY_K = { InputType::Key, SDL_SCANCODE_K };
    const InputCode KEY_L = { InputType::Key, SDL_SCANCODE_L };
    const InputCode KEY_M = { InputType::Key, SDL_SCANCODE_M };
    const InputCode KEY_N = { InputType::Key, SDL_SCANCODE_N };
    const InputCode KEY_O = { InputType::Key, SDL_SCANCODE_O };
    const InputCode KEY_P = { InputType::Key, SDL_SCANCODE_P };
    const InputCode KEY_Q = { InputType::Key, SDL_SCANCODE_Q };
    const InputCode KEY_R = { InputType::Key, SDL_SCANCODE_R };
    const InputCode KEY_S = { InputType::Key, SDL_SCANCODE_S };
    const InputCode KEY_T = { InputType::Key, SDL_SCANCODE_T };
    const InputCode KEY_U = { InputType::Key, SDL_SCANCODE_U };
    const InputCode KEY_V = { InputType::Key, SDL_SCANCODE_V };
    const InputCode KEY_W = { InputType::Key, SDL_SCANCODE_W };
    const InputCode KEY_X = { InputType::Key, SDL_SCANCODE_X };
    const InputCode KEY_Y = { InputType::Key, SDL_SCANCODE_Y };
    const InputCode KEY_Z = { InputType::Key, SDL_SCANCODE_Z };

    // Numbers
    const InputCode KEY_0 = { InputType::Key, SDL_SCANCODE_0 };
    const InputCode KEY_1 = { InputType::Key, SDL_SCANCODE_1 };
    const InputCode KEY_2 = { InputType::Key, SDL_SCANCODE_2 };
    const InputCode KEY_3 = { InputType::Key, SDL_SCANCODE_3 };
    const InputCode KEY_4 = { InputType::Key, SDL_SCANCODE_4 };
    const InputCode KEY_5 = { InputType::Key, SDL_SCANCODE_5 };
    const InputCode KEY_6 = { InputType::Key, SDL_SCANCODE_6 };
    const InputCode KEY_7 = { InputType::Key, SDL_SCANCODE_7 };
    const InputCode KEY_8 = { InputType::Key, SDL_SCANCODE_8 };
    const InputCode KEY_9 = { InputType::Key, SDL_SCANCODE_9 };

    // Control keys
    const InputCode KEY_LEFT_CTRL  = { InputType::Key, SDL_SCANCODE_LCTRL };
    const InputCode KEY_RIGHT_CTRL = { InputType::Key, SDL_SCANCODE_RCTRL };
    const InputCode KEY_LEFT_ALT   = { InputType::Key, SDL_SCANCODE_LALT };
    const InputCode KEY_RIGHT_ALT  = { InputType::Key, SDL_SCANCODE_RALT };
    const InputCode KEY_LEFT_SHIFT = { InputType::Key, SDL_SCANCODE_LSHIFT };
    const InputCode KEY_RIGHT_SHIFT = { InputType::Key, SDL_SCANCODE_RSHIFT };

    // Misc keys
    const InputCode KEY_SPACE      = { InputType::Key, SDL_SCANCODE_SPACE };
    const InputCode KEY_ENTER      = { InputType::Key, SDL_SCANCODE_RETURN };
    const InputCode KEY_ESCAPE     = { InputType::Key, SDL_SCANCODE_ESCAPE };
    const InputCode KEY_BACKSPACE  = { InputType::Key, SDL_SCANCODE_BACKSPACE };
    const InputCode KEY_TAB        = { InputType::Key, SDL_SCANCODE_TAB };

    // Arrow keys
    const InputCode KEY_UP         = { InputType::Key, SDL_SCANCODE_UP };
    const InputCode KEY_DOWN       = { InputType::Key, SDL_SCANCODE_DOWN };
    const InputCode KEY_LEFT       = { InputType::Key, SDL_SCANCODE_LEFT };
    const InputCode KEY_RIGHT      = { InputType::Key, SDL_SCANCODE_RIGHT };

    // Function keys
    const InputCode KEY_F1  = { InputType::Key, SDL_SCANCODE_F1 };
    const InputCode KEY_F2  = { InputType::Key, SDL_SCANCODE_F2 };
    const InputCode KEY_F3  = { InputType::Key, SDL_SCANCODE_F3 };
    const InputCode KEY_F4  = { InputType::Key, SDL_SCANCODE_F4 };
    const InputCode KEY_F5  = { InputType::Key, SDL_SCANCODE_F5 };
    const InputCode KEY_F6  = { InputType::Key, SDL_SCANCODE_F6 };
    const InputCode KEY_F7  = { InputType::Key, SDL_SCANCODE_F7 };
    const InputCode KEY_F8  = { InputType::Key, SDL_SCANCODE_F8 };
    const InputCode KEY_F9  = { InputType::Key, SDL_SCANCODE_F9 };
    const InputCode KEY_F10 = { InputType::Key, SDL_SCANCODE_F10 };
    const InputCode KEY_F11 = { InputType::Key, SDL_SCANCODE_F11 };
    const InputCode KEY_F12 = { InputType::Key, SDL_SCANCODE_F12 };

    // Other keys
    const InputCode KEY_INSERT     = { InputType::Key, SDL_SCANCODE_INSERT };
    const InputCode KEY_DELETE     = { InputType::Key, SDL_SCANCODE_DELETE };
    const InputCode KEY_HOME       = { InputType::Key, SDL_SCANCODE_HOME };
    const InputCode KEY_END        = { InputType::Key, SDL_SCANCODE_END };
    const InputCode KEY_PAGE_UP    = { InputType::Key, SDL_SCANCODE_PAGEUP };
    const InputCode KEY_PAGE_DOWN  = { InputType::Key, SDL_SCANCODE_PAGEDOWN };

    const InputCode KEY_CAPS_LOCK  = { InputType::Key, SDL_SCANCODE_CAPSLOCK };
    const InputCode KEY_NUM_LOCK   = { InputType::Key, SDL_SCANCODE_NUMLOCKCLEAR };
    const InputCode KEY_SCROLL_LOCK = { InputType::Key, SDL_SCANCODE_SCROLLLOCK };

    const InputCode KEY_PRINT_SCREEN = { InputType::Key, SDL_SCANCODE_PRINTSCREEN };
    const InputCode KEY_PAUSE        = { InputType::Key, SDL_SCANCODE_PAUSE };

    // Mouse buttons (using the simplified approach)
    const InputCode MOUSE_LEFT = SDL_BUTTON_LEFT;
    const InputCode MOUSE_RIGHT = SDL_BUTTON_RIGHT;
    const InputCode MOUSE_MIDDLE = SDL_BUTTON_MIDDLE;
    const InputCode MOUSE_X1 = SDL_BUTTON_X1;
    const InputCode MOUSE_X2 = SDL_BUTTON_X2;
}

#endif