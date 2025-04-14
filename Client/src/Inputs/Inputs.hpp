//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Inputs.hpp
//

#pragma once

#include <optional>

namespace client {
    enum class ev_keys {
        KEY_NULL,
        KEY_SPACE,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        SPECIAL_KEY_SPACE,
        SPECIAL_KEY_BACKSPACE,
        SPECIAL_KEY_ENTER,
        ARROW_LEFT,
        ARROW_RIGHT,
        ARROW_DOWN,
        ARROW_UP,
        CLOSE,
    };

    enum class ev_state {
        PRESSED,
        RELEASED,
    };

    class Inputs {
       public:
        std::optional<ev_keys> key;
        std::optional<ev_state> state;
    };
}  // namespace client
