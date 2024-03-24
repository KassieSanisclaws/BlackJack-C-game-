#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_net.h"

#include "Client.h"

class ProxyClient
{
public:
    ProxyClient();
    ~ProxyClient();

    void open(std::string);
    void send(std::pair<float, float>);
    std::pair<float, float> receive();

private:
    Client* client;
};