#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_net.h"

class Client
{
public:
	Client();
	~Client();

	void open(std::string);
	void send(std::pair<float, float>);
	std::pair<float, float> receive();

	static const Uint16 PORT = 9999;

private:
	std::string host;

	IPaddress serverIP;
	TCPsocket server;

	SDLNet_SocketSet socketSet;

	std::vector<TCPsocket> clientSockets;

	static const int BUFFER_SIZE = 1024;
};