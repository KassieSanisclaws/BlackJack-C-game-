#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	server = nullptr;
	managerID = "network";
}

NetworkManager::~NetworkManager()
{
	for (auto it = clientSockets.begin(); it != clientSockets.end(); ++it)
	{
		TCPsocket client = *it;

		if (client)
		{
			std::cout << "Disconnecting client connections..." << std::endl;
			SDLNet_TCP_Close(client);
		}
	}

	delete server;
}

NetworkManager* NetworkManager::getInstance()
{
	if (!instance)
		instance = new NetworkManager();

	return instance;
}

void NetworkManager::removeInstance()
{
	if (instance)
		delete instance;
}

void NetworkManager::open(std::string host, Uint16 port)
{
	if (!server)
		server = new Server();

	server->init(host, port);
	server->open();

	TimeManager::getInstance()->addTimer(managerID);
	startTime = TimeManager::getInstance()->get(managerID);
}

void NetworkManager::send(TCPsocket client, const std::pair<float, float> message)
{
	if (!server)
	{
		std::cout << "Error: Server not initialized..." << std::endl;
		return;
	}

	server->send(client, message);
}

void NetworkManager::receive(std::pair<float, float>& message)
{	
	if (!server)
	{
		std::cout << "Error: Server not initialized..." << std::endl;
		message = { 0.0f, 0.0f };
	}

	for (auto it = clientSockets.begin(); it != clientSockets.end(); ++it)
	{
		TCPsocket client = *it;

		int numBytes;

		server->receive(client, message, numBytes);

		if (numBytes > 0)
			broadcast(client, message);
	}
}

void NetworkManager::broadcast(TCPsocket sender, const std::pair<float, float>& message)
{
	if (SDLNet_TCP_GetPeerAddress(sender) == nullptr)
	{
		std::cout << "Client disconnected..." << std::endl;
		SDLNet_TCP_Close(sender);
		
		for (auto it = clientSockets.begin(); it != clientSockets.end(); ++it)
		{
			TCPsocket client = *it;

			if (client != sender)
				send(client, message);
		}
	}
}

void NetworkManager::listen()
{
	delta += TimeManager::getInstance()->get(managerID) - startTime;
	startTime = TimeManager::getInstance()->get(managerID);

	if (delta >= 5000)
	{ 
		TCPsocket client;
		if (server->listen(client))
			addClient(client);
		delta = 0;
	}
}

void NetworkManager::addClient(TCPsocket client)
{
	clientSockets.push_back(client);
}

NetworkManager* NetworkManager::instance = nullptr;