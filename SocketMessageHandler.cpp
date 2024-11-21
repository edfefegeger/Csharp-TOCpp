#include "SocketMessageHandler.h"
#include <winsock2.h> 
#include <ws2tcpip.h> 
#include <cstring>
#include <windows.h> 
#include <cstdio>    
#pragma comment(lib, "Ws2_32.lib")

SocketMessageHandler::SocketMessageHandler(int socketFd) : socketFd(socketFd) {}

SocketMessageHandler::~SocketMessageHandler() {
    closesocket(socketFd); 
}

void SocketMessageHandler::SendJSON(const char* jsonData) {
    unsigned int dataLen = strlen(jsonData);
    unsigned char encrypted[1024];
    unsigned int encryptedLen = 0;

    encryptor.EncryptBytes((unsigned char*)jsonData, dataLen, encrypted, encryptedLen);

    int result = send(socketFd, (const char*)encrypted, encryptedLen, 0);
    if (result == SOCKET_ERROR) {
        char errorMsg[256];
        sprintf_s(errorMsg, sizeof(errorMsg), "Error sending data: %ld\n", WSAGetLastError());
        WriteConsole(GetStdHandle(STD_ERROR_HANDLE), errorMsg, (DWORD)strlen(errorMsg), nullptr, nullptr);
    }
}

void SocketMessageHandler::ProcessSocketArgs(const char* buffer, unsigned int length) {
    unsigned char decrypted[1024];
    unsigned int decryptedLen = 0;

    encryptor.DecryptBytes((unsigned char*)buffer, length, decrypted, decryptedLen);

    ProcessMessage((const char*)decrypted, decryptedLen);
}

void SocketMessageHandler::ProcessMessage(const char* message, unsigned int length) {
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, nullptr, nullptr);
}
