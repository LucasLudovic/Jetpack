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

client::Poll::Poll()
{
    struct pollfd fd;
    int sockt = socket(AF_INET, SOCK_STREAM, 0);
    if (sockt == -1)
        throw PollError("Socket Failed");
}
