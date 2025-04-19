//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// client.hpp
//

#pragma once

#include <cstdint>
#define RET_SUCCESS 0
#define RET_FAILURE -1

uint8_t launchClient(int argc, char const *argv[], char **env);
