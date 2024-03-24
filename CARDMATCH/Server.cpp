#include "Server.h"
#include "NetworkManager.h"

Server::Server() : server(nullptr), socketSet(nullptr), connections(0)
{
    std::cout << "Starting SDL NET..." << std::endl;

    if (SDLNet_Init() == -1)
    {
        std::cout << "SDL NET cannot initialize - " << SDLNet_GetError() << std::endl;
    }
}

Server::~Server()
{
    std::cout << "Shutting down SDL NET..." << std::endl;
    if (socketSet) 
        SDLNet_FreeSocketSet(socketSet);

    if (server) 
        SDLNet_TCP_Close(server);

    SDLNet_Quit();
}

void Server::init(std::string host, Uint16 port)
{
    if (SDLNet_ResolveHost(&serverIP, nullptr, port) == -1)
    {
        std::cout << "Cannot connect to host - " << SDLNet_GetError() << std::endl;
    }
}

void Server::open()
{
    server = SDLNet_TCP_Open(&serverIP);

    if (!server)
    {
        std::cout << "TCP host error - " << SDLNet_GetError() << std::endl;
    }

    std::cout << "SDL NET initialized..." << std::endl;
    
    socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
    if (!socketSet) 
    {
        std::cout << "SDLNet_AllocSocketSet error..." << std::endl;
    }

    if (SDLNet_TCP_AddSocket(socketSet, server) == -1)
    {
        std::cout << "SDLNet_TCP_AddSocket error..." << std::endl;
    }
}

void Server::send(TCPsocket client, std::pair<float, float> message)
{
    SDLNet_TCP_Send(client, &message, sizeof(message));
}

void Server::receive(TCPsocket client, std::pair<float, float>& message, int& numBytes)
{
    numBytes = SDLNet_TCP_Recv(client, &message, sizeof(message));
}

bool Server::listen(TCPsocket& client)
{
    if (SDLNet_CheckSockets(socketSet, 0) > 0) 
    {
        if (SDLNet_SocketReady(server)) 
        {
            client = SDLNet_TCP_Accept(server);

            if (client) 
            {
                connections = SDLNet_TCP_AddSocket(socketSet, client);
                
                std::cout << "Client connected..." << std::endl;
                std::cout << "Clients connected: " << (connections - 1) << std::endl;

                return true;
            }
        }
    }

    return false;
}