#ifndef CLIENTSOCKETMESSAGES_H
#define CLIENTSOCKETMESSAGES_H

#include <winsock2.h>

class ClientSocketMessages {
private:
    SOCKET socketOut;

public:
    ClientSocketMessages(SOCKET socketOut);
    void SendJSON(const char* json);
    void SendTestMessage(const char* message);
    void SendPing();
};

#endif 
