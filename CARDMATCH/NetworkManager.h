#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_net.h"

#include "NetworkMediator.h"
#include "Server.h"
#include "TimeManager.h"

class NetworkManager : public NetworkMediator
{
public:
    static NetworkManager* getInstance();
    static void removeInstance();

    void open(std::string, Uint16);
    void send(TCPsocket, const std::pair<float, float>);
    void receive(std::pair<float, float>&);
    void listen();

    void broadcast(TCPsocket, const std::pair<float, float>&);

    void addClient(TCPsocket);

private:
    NetworkManager();
    ~NetworkManager();

    Server* server;
    long startTime;
    long delta;

    std::string managerID;

    std::vector<TCPsocket> clientSockets;

    static NetworkManager* instance;
};