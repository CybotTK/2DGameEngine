#include "Python/PythonRegistry.h"

#include "System/InputTypes.h"

void PyRegisterInputTypes(py::module_& m) {
    // Expose InputType enum (useful for type checking)
    py::enum_<InputType>(m, "InputType")
        .value("None", InputType::None)
        .value("Key", InputType::Key)
        .value("Mouse", InputType::Mouse);

    // Bind the InputCode struct
    py::class_<InputCode>(m, "InputCode")
        .def(py::init<>()) // Default constructor
        .def(py::init<SDL_Scancode>(), "Keyboard Input Constructor") // Constructor for key
        .def(py::init<InputType>(), "Mouse Input Constructor") // Constructor for mouse (no button)
        .def(py::init<Uint8>(), "Mouse Input Constructor") // Constructor for mouse (button code)
        .def(py::init<InputType, SDL_Scancode>(), "Constructor for InputType and Scancode") // Constructor with both
        .def_readwrite("type", &InputCode::type)
        .def_readwrite("key", &InputCode::key)
        .def_readwrite("mouseButton", &InputCode::mouseButton)
        .def("__eq__", &InputCode::operator==); // Equality operator

    // Expose predefined key mappings
    auto inputKeyModule = m.def_submodule("InputKey");

#define ADD_KEY(name) inputKeyModule.attr(#name) = InputKey::name;

    // Letters
    ADD_KEY(KEY_A); ADD_KEY(KEY_B); ADD_KEY(KEY_C); ADD_KEY(KEY_D);
    ADD_KEY(KEY_E); ADD_KEY(KEY_F); ADD_KEY(KEY_G); ADD_KEY(KEY_H);
    ADD_KEY(KEY_I); ADD_KEY(KEY_J); ADD_KEY(KEY_K); ADD_KEY(KEY_L);
    ADD_KEY(KEY_M); ADD_KEY(KEY_N); ADD_KEY(KEY_O); ADD_KEY(KEY_P);
    ADD_KEY(KEY_Q); ADD_KEY(KEY_R); ADD_KEY(KEY_S); ADD_KEY(KEY_T);
    ADD_KEY(KEY_U); ADD_KEY(KEY_V); ADD_KEY(KEY_W); ADD_KEY(KEY_X);
    ADD_KEY(KEY_Y); ADD_KEY(KEY_Z);

    // Numbers
    ADD_KEY(KEY_0); ADD_KEY(KEY_1); ADD_KEY(KEY_2); ADD_KEY(KEY_3);
    ADD_KEY(KEY_4); ADD_KEY(KEY_5); ADD_KEY(KEY_6); ADD_KEY(KEY_7);
    ADD_KEY(KEY_8); ADD_KEY(KEY_9);

    // Control keys
    ADD_KEY(KEY_LEFT_CTRL); ADD_KEY(KEY_RIGHT_CTRL);
    ADD_KEY(KEY_LEFT_ALT); ADD_KEY(KEY_RIGHT_ALT);
    ADD_KEY(KEY_LEFT_SHIFT); ADD_KEY(KEY_RIGHT_SHIFT);

    // Misc keys
    ADD_KEY(KEY_SPACE); ADD_KEY(KEY_ENTER); ADD_KEY(KEY_ESCAPE);
    ADD_KEY(KEY_BACKSPACE); ADD_KEY(KEY_TAB);

    // Arrow keys
    ADD_KEY(KEY_UP); ADD_KEY(KEY_DOWN); ADD_KEY(KEY_LEFT); ADD_KEY(KEY_RIGHT);

    // Function keys
    ADD_KEY(KEY_F1); ADD_KEY(KEY_F2); ADD_KEY(KEY_F3); ADD_KEY(KEY_F4);
    ADD_KEY(KEY_F5); ADD_KEY(KEY_F6); ADD_KEY(KEY_F7); ADD_KEY(KEY_F8);
    ADD_KEY(KEY_F9); ADD_KEY(KEY_F10); ADD_KEY(KEY_F11); ADD_KEY(KEY_F12);

    // Other keys
    ADD_KEY(KEY_INSERT); ADD_KEY(KEY_DELETE); ADD_KEY(KEY_HOME); ADD_KEY(KEY_END);
    ADD_KEY(KEY_PAGE_UP); ADD_KEY(KEY_PAGE_DOWN);
    ADD_KEY(KEY_CAPS_LOCK); ADD_KEY(KEY_NUM_LOCK); ADD_KEY(KEY_SCROLL_LOCK);
    ADD_KEY(KEY_PRINT_SCREEN); ADD_KEY(KEY_PAUSE);

    // Mouse buttons
    ADD_KEY(MOUSE_LEFT); ADD_KEY(MOUSE_RIGHT);
    ADD_KEY(MOUSE_MIDDLE); ADD_KEY(MOUSE_X1); ADD_KEY(MOUSE_X2);

#undef ADD_KEY

    // Option to use it without having to import InputKey
    // from engine import InputKey
    // engine.KEY_A
    // engine.InputKey.KEY_A
    // Both work (I hope :p)

    // Letters
    m.attr("KEY_A") = InputKey::KEY_A;
    m.attr("KEY_B") = InputKey::KEY_B;
    m.attr("KEY_C") = InputKey::KEY_C;
    m.attr("KEY_D") = InputKey::KEY_D;
    m.attr("KEY_E") = InputKey::KEY_E;
    m.attr("KEY_F") = InputKey::KEY_F;
    m.attr("KEY_G") = InputKey::KEY_G;
    m.attr("KEY_H") = InputKey::KEY_H;
    m.attr("KEY_I") = InputKey::KEY_I;
    m.attr("KEY_J") = InputKey::KEY_J;
    m.attr("KEY_K") = InputKey::KEY_K;
    m.attr("KEY_L") = InputKey::KEY_L;
    m.attr("KEY_M") = InputKey::KEY_M;
    m.attr("KEY_N") = InputKey::KEY_N;
    m.attr("KEY_O") = InputKey::KEY_O;
    m.attr("KEY_P") = InputKey::KEY_P;
    m.attr("KEY_Q") = InputKey::KEY_Q;
    m.attr("KEY_R") = InputKey::KEY_R;
    m.attr("KEY_S") = InputKey::KEY_S;
    m.attr("KEY_T") = InputKey::KEY_T;
    m.attr("KEY_U") = InputKey::KEY_U;
    m.attr("KEY_V") = InputKey::KEY_V;
    m.attr("KEY_W") = InputKey::KEY_W;
    m.attr("KEY_X") = InputKey::KEY_X;
    m.attr("KEY_Y") = InputKey::KEY_Y;
    m.attr("KEY_Z") = InputKey::KEY_Z;

    // Numbers
    m.attr("KEY_0") = InputKey::KEY_0;
    m.attr("KEY_1") = InputKey::KEY_1;
    m.attr("KEY_2") = InputKey::KEY_2;
    m.attr("KEY_3") = InputKey::KEY_3;
    m.attr("KEY_4") = InputKey::KEY_4;
    m.attr("KEY_5") = InputKey::KEY_5;
    m.attr("KEY_6") = InputKey::KEY_6;
    m.attr("KEY_7") = InputKey::KEY_7;
    m.attr("KEY_8") = InputKey::KEY_8;
    m.attr("KEY_9") = InputKey::KEY_9;

    // Control keys
    m.attr("KEY_LEFT_CTRL") = InputKey::KEY_LEFT_CTRL;
    m.attr("KEY_RIGHT_CTRL") = InputKey::KEY_RIGHT_CTRL;
    m.attr("KEY_LEFT_ALT") = InputKey::KEY_LEFT_ALT;
    m.attr("KEY_RIGHT_ALT") = InputKey::KEY_RIGHT_ALT;
    m.attr("KEY_LEFT_SHIFT") = InputKey::KEY_LEFT_SHIFT;
    m.attr("KEY_RIGHT_SHIFT") = InputKey::KEY_RIGHT_SHIFT;

    // Misc keys
    m.attr("KEY_SPACE") = InputKey::KEY_SPACE;
    m.attr("KEY_ENTER") = InputKey::KEY_ENTER;
    m.attr("KEY_ESCAPE") = InputKey::KEY_ESCAPE;
    m.attr("KEY_BACKSPACE") = InputKey::KEY_BACKSPACE;
    m.attr("KEY_TAB") = InputKey::KEY_TAB;

    // Arrow keys
    m.attr("KEY_UP") = InputKey::KEY_UP;
    m.attr("KEY_DOWN") = InputKey::KEY_DOWN;
    m.attr("KEY_LEFT") = InputKey::KEY_LEFT;
    m.attr("KEY_RIGHT") = InputKey::KEY_RIGHT;

    // Function keys
    m.attr("KEY_F1") = InputKey::KEY_F1;
    m.attr("KEY_F2") = InputKey::KEY_F2;
    m.attr("KEY_F3") = InputKey::KEY_F3;
    m.attr("KEY_F4") = InputKey::KEY_F4;
    m.attr("KEY_F5") = InputKey::KEY_F5;
    m.attr("KEY_F6") = InputKey::KEY_F6;
    m.attr("KEY_F7") = InputKey::KEY_F7;
    m.attr("KEY_F8") = InputKey::KEY_F8;
    m.attr("KEY_F9") = InputKey::KEY_F9;
    m.attr("KEY_F10") = InputKey::KEY_F10;
    m.attr("KEY_F11") = InputKey::KEY_F11;
    m.attr("KEY_F12") = InputKey::KEY_F12;

    // Other keys
    m.attr("KEY_INSERT") = InputKey::KEY_INSERT;
    m.attr("KEY_DELETE") = InputKey::KEY_DELETE;
    m.attr("KEY_HOME") = InputKey::KEY_HOME;
    m.attr("KEY_END") = InputKey::KEY_END;
    m.attr("KEY_PAGE_UP") = InputKey::KEY_PAGE_UP;
    m.attr("KEY_PAGE_DOWN") = InputKey::KEY_PAGE_DOWN;

    m.attr("KEY_CAPS_LOCK") = InputKey::KEY_CAPS_LOCK;
    m.attr("KEY_NUM_LOCK") = InputKey::KEY_NUM_LOCK;
    m.attr("KEY_SCROLL_LOCK") = InputKey::KEY_SCROLL_LOCK;

    m.attr("KEY_PRINT_SCREEN") = InputKey::KEY_PRINT_SCREEN;
    m.attr("KEY_PAUSE") = InputKey::KEY_PAUSE;

    // Mouse buttons
    m.attr("MOUSE_LEFT") = InputKey::MOUSE_LEFT;
    m.attr("MOUSE_RIGHT") = InputKey::MOUSE_RIGHT;
    m.attr("MOUSE_MIDDLE") = InputKey::MOUSE_MIDDLE;
    m.attr("MOUSE_X1") = InputKey::MOUSE_X1;
    m.attr("MOUSE_X2") = InputKey::MOUSE_X2;
}