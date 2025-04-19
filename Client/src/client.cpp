//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// client.cpp
//

#include "client.hpp"
#include "Display/Display.hpp"
#include "JetpackClient/JetpackClient.hpp"
#include "Network/socket/Socket.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

static int checkEnv(char **env)
{
    size_t envChecker = 0;
    if (env == nullptr)
        return RET_FAILURE;
    for (int i = 0; env[i] != nullptr; i += 1) {
        if (strncmp(env[i], "DISPLAY=", 8) == 0)
            envChecker += 1;
        if (strncmp(env[i], "TERM=", 5) == 0)
            envChecker += 1;
    }
    if (envChecker < 2)
        return RET_FAILURE;
    return RET_SUCCESS;
}

static std::string retrievePort(const char *argv[])
{
    std::string str;
    bool portFound = false;

    if (argv == nullptr)
        return str;
    for (size_t i = 0; argv[i] != nullptr; i += 1) {
        if (portFound) {
            str = argv[i];
            break;
        }
        if (strcmp(argv[i], "-p") == 0)
            portFound = true;
    }
    return str;
}

static bool retrieveDebug(const char *argv[])
{
    std::string str;
    bool debugFound = false;

    if (argv == nullptr)
        return false;
    for (size_t i = 0; argv[i] != nullptr; i += 1) {
        if (strcmp(argv[i], "-d") == 0) {
            debugFound = true;
            break;
        }
    }
    return debugFound;
}

static std::string retrieveIP(const char *argv[])
{
    std::string str;
    bool ipFound = false;

    if (argv == nullptr)
        return str;
    for (size_t i = 0; argv[i] != nullptr; i += 1) {
        if (ipFound) {
            str = argv[i];
            break;
        }
        if (strcmp(argv[i], "-h") == 0)
            ipFound = true;
    }
    return str;
}

uint8_t launchClient(const int argc, char const *argv[], char **env)
{
    if (argc < 5)
        return RET_FAILURE;
    std::string ip = retrieveIP(argv);
    std::string port = retrievePort(argv);
    bool debugMode = retrieveDebug(argv);
    if (checkEnv(env) == RET_FAILURE)
        return RET_FAILURE;
    try {
        client::JetpackClient NewClient(ip, port, debugMode);
        NewClient.runClient();
    } catch (client::Socket::SocketError &e) {
        std::cerr << e.what() << '\n';
        return RET_FAILURE;
    } catch (client::JetpackClient::ClientError &e) {
        std::cerr << e.what() << '\n';
        return RET_FAILURE;
    } catch (client::Display::DisplayError &e) {
        std::cerr << e.what() << '\n';
        return RET_FAILURE;
    }
    return RET_SUCCESS;
}
