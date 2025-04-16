//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Poll.hpp
//

#pragma once

#include <memory>
#include <string>
#include <sys/poll.h>
#include <vector>

namespace client {
    class Poll {
       public:
        class PollError : public std::exception {
           public:
            PollError(const std::string &msg) { this->_msg = msg; }

            const char *what() const noexcept override
            {
                return this->_msg.c_str();
            }

           private:
            std::string _msg;
        };

        Poll(int fd);
        ~Poll() = default;
        int triggerPoll(int timeout);

       private:
        std::unique_ptr<struct pollfd> _pfds;
    };
}  // namespace client
