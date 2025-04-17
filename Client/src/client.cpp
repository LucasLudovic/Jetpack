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

uint8_t launchClient(const int argc, char const *argv[])
{
    if (argc < 5)
        return RET_FAILURE;
    std::string ip = retrieveIP(argv);
    std::string port = retrievePort(argv);
    try {
        client::JetpackClient NewClient(ip, port);
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
