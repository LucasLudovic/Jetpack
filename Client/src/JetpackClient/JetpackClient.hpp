//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.hpp
//

#pragma once

#include <cstdint>
#include <string>
#include <queue>
#include <vector>

namespace client {
    class JetpackClient {
       public:
        JetpackClient(const std::string &ip, const std::string &port);
        ~JetpackClient();

        std::uint8_t runClient();

       private:
        std::string _ip;
        std::string _port;
        bool _running;
        std::vector<std::string> _data;
        std::vector<std::string> _msg;
    };
}  // namespace client
