//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#pragma once

#include "Inputs/Inputs.hpp"
#include "JetpackClient/Poll/Poll.hpp"
#include "Network/socket/Socket.hpp"
#include <memory>
#include <string>

namespace client {
    class Network {
       public:
        Network(const std::string &ip, const std::string &port);
        ~Network();

        void sendInputToServer(const std::string &msg) const;
        std::string retrieveServerInformation() const;
       private:
        std::unique_ptr<client::Socket> _socket;
        std::unique_ptr<client::Poll> _poll;
    };
}  // namespace client
