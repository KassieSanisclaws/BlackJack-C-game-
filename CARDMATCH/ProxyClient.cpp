#include "ProxyClient.h"

ProxyClient::ProxyClient()
{
	client = new Client();
}

ProxyClient::~ProxyClient()
{
	delete client;
}

void ProxyClient::open(std::string host)
{
	client->open(host);
}

void ProxyClient::send(std::pair<float, float> message)
{
	client->send(message);
}

std::pair<float, float> ProxyClient::receive()
{
	return client->receive();
}