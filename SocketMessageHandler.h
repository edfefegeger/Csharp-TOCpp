#ifndef SOCKETMESSAGEHANDLER_H
#define SOCKETMESSAGEHANDLER_H

#include "Encryption.h"
#include <winsock2.h>  
#include <ws2tcpip.h>  
#pragma comment(lib, "Ws2_32.lib")
class SocketMessageHandler {
public:
    explicit SocketMessageHandler(int socketFd);
    ~SocketMessageHandler();

    void SendJSON(const char* jsonData);
    void ProcessSocketArgs(const char* buffer, unsigned int length);

private:
    int socketFd;       
    Encryption encryptor;

    void ProcessMessage(const char* message, unsigned int length);
};

#endif 
