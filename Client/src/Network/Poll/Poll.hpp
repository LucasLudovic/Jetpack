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

namespace client {

/**
 * @class Poll
 * @brief Wrapper around the POSIX poll mechanism for monitoring socket events.
 */
class Poll {
   public:
    /**
     * @class PollError
     * @brief Exception class for poll-related errors.
     */
    class PollError : public std::exception {
       public:
        /**
         * @brief Constructs a new PollError with an error message.
         * @param msg The error message.
         */
        PollError(const std::string &msg) { this->_msg = msg; }

        /**
         * @brief Returns the error message.
         * @return A C-style string with the error description.
         */
        const char *what() const noexcept override
        {
            return this->_msg.c_str();
        }

       private:
        std::string _msg; ///< Error message.
    };

    /**
     * @brief Constructs a Poll object associated with a file descriptor.
     * @param fd File descriptor to monitor.
     */
    Poll(int fd);

    /**
     * @brief Default destructor.
     */
    ~Poll() = default;

    /**
     * @brief Waits for events on the file descriptor.
     * @param timeout Timeout in milliseconds (-1 to wait indefinitely).
     * @return Result of the poll syscall.
     */
    int triggerPoll(int timeout);

   private:
    std::unique_ptr<struct pollfd> _pfds; ///< Pointer to the pollfd structure used by poll().
};

}  // namespace client

