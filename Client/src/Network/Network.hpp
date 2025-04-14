//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#pragma once

#include "Inputs/Inputs.hpp"
#include "Network/socket/Socket.hpp"
#include <memory>
#include <string>

namespace client {
    class Network {
       public:
        Network(const std::string &ip, const std::string &port);
        ~Network();

        void sendInputToServer(client::Inputs input) const;
        std::string retrieveServerInformation() const;
       private:
        std::unique_ptr<client::Socket> _socket;
    };
}  // namespace client
