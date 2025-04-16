//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Poll.cpp
//

#include "Poll.hpp"
#include <memory>
#include <sys/poll.h>
#include <sys/socket.h>

client::Poll::Poll(int fd)
{
    this->_pfds = std::make_unique<struct pollfd>();
    this->_pfds->fd = fd;
    this->_pfds->events = POLLIN;
}

int client::Poll::triggerPoll(int timeout)
{
    return poll(this->_pfds.get(), 1, timeout);
}
