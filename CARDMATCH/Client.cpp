#include "Client.h"

Client::Client()
{
    if (SDLNet_Init() == -1)
    {
        std::cout << "SDL NET cannot initialize " << SDLNet_GetError() << std::endl;
        exit(0);
    }

    std::cout << "SDL NET initialized..." << std::endl;
}

Client::~Client()
{
    SDLNet_FreeSocketSet(socketSet);

    if (server)
    {
        std::cout << "Disconnecting from server..." << std::endl;
        SDLNet_TCP_Close(server);
    }

    std::cout << "Shutting down SDL NET..." << std::endl;
    SDLNet_Quit();
}

void Client::open(std::string h)
{
    host = h;

    if (SDLNet_ResolveHost(&serverIP, host.c_str(), PORT) == -1)
    {
        std::cout << "Cannot connect to host - " << SDLNet_GetError() << std::endl;
    }

    server = SDLNet_TCP_Open(&serverIP);

    if (!server)
    {
        std::cout << "TCP host error " << SDLNet_GetError() << std::endl;
    }

    socketSet = SDLNet_AllocSocketSet(1);

    if (!socketSet)
    {
        std::cout << "Cannot create socket set - " << SDLNet_GetError() << std::endl;
    }

    SDLNet_TCP_AddSocket(socketSet, server);

    std::cout << "SDL NET connected..." << std::endl;
}

void Client::send(std::pair<float, float> message)
{
    if (server)
    {
        //std::cout << "Client: sending message..." << std::endl;

        SDLNet_TCP_Send(server, &message, sizeof(message));
    }
}

std::pair<float, float> Client::receive()
{
    int numBytes = 0;
    char buffer[BUFFER_SIZE];
    std::pair<float, float> message;

    int numActiveSockets = SDLNet_CheckSockets(socketSet, 0);

    if (numActiveSockets > 0)
    {
        //std::cout << "Client: receiving message..." << std::endl;
        numBytes = SDLNet_TCP_Recv(server, &message, sizeof(message));
    }

    return message;
}