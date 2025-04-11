//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#pragma once

#include <string>
namespace client {
    class Network {
       public:
        Network();
        ~Network();

        void createConnection(const std::string &ip, const std::string &port);
        void sendInputToServer() const;
        void retrieveServerInformation();
       private:
    };
}  // namespace client
