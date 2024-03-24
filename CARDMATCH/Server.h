#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h" 
#include "SDL_net.h" 

class Server
{
public:
	Server();
	~Server();

	void init(std::string, Uint16);
	void open();
	void send(TCPsocket, std::pair<float, float>);
	void receive(TCPsocket, std::pair<float, float>&, int&);
	bool listen(TCPsocket&);

private:
	IPaddress serverIP;
	TCPsocket server;

	SDLNet_SocketSet socketSet;

	int connections;
	
	static const int MAX_SOCKETS = 4;
};