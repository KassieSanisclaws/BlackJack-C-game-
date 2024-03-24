#pragma once

#include <string>

#include "SDL_net.h"

class NetworkMediator 
{
public:
    virtual ~NetworkMediator() = default;

    virtual void send(TCPsocket, const std::pair<float, float>) = 0;
    virtual void receive(std::pair<float, float>&) = 0;

    virtual void broadcast(TCPsocket, const std::pair<float, float>&) = 0;
};
