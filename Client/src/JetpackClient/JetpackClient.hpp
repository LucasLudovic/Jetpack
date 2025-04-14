//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.hpp
//

#pragma once

#include <cstdint>
#include <string>

namespace client {
    class JetpackClient {
       public:
        JetpackClient(const std::string &ip, const std::string &port);
        ~JetpackClient();

        std::uint8_t runClient();

       private:
        std::string _ip;
        std::string _port;
    };
}  // namespace client
