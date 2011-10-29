/**
 * IRC Client
 *
 * Fredi Machado
 * http://github.com/Fredi
 */

#include <iostream>
#include "IRCSocket.h"
#include "IRCClient.h"

bool IRCClient::InitSocket()
{
    return _socket.Init();
}

bool IRCClient::Connect(char* host, int port)
{
    return _socket.Connect(host, port);
}

void IRCClient::Disconnect()
{
    SendIRC("QUIT");
    _socket.Disconnect();
}

bool IRCClient::SendIRC(std::string data)
{
    data.append("\n");
    return _socket.SendData(data.c_str());
}

bool IRCClient::Login(std::string nick, std::string user)
{
    if (SendIRC("HELLO"))
        if (SendIRC("NICK " + nick))
            if (SendIRC("USER " + user + " 0 * :Cpp IRC Client"))
                return true;

    return false;
}

void IRCClient::ReceiveData()
{
    std::string buffer = _socket.ReceiveData();

    std::string line;
    std::istringstream iss(buffer);
    while(getline(iss, line))
        Parse(line);
}

void IRCClient::Parse(std::string data)
{
    if (data.substr(0, 5) == "ERROR")
    {
        Disconnect();
        return;
    }

    if (data.substr(0, 4) == "PING")
        SendIRC("PONG " + data.substr(4, data.size() - 4));

    std::cout << data << std::endl;
}
