/**
 * IRC Client
 *
 * Fredi Machado
 * http://github.com/Fredi
 */

#ifndef _IRCCLIENT_H
#define _IRCCLIENT_H

#include <string>
#include "IRCSocket.h"
 
class IRCClient
{
public:
    bool InitSocket();
    bool Connect(char* /*host*/, int /*port*/);
    void Disconnect();
    bool Connected() { return _socket.Connected(); };

    bool SendIRC(std::string /*data*/);

    bool Login(std::string /*nick*/, std::string /*user*/);

    void ReceiveData();

private:
    void Parse(std::string /*data*/);

    IRCSocket _socket;
};

#endif
