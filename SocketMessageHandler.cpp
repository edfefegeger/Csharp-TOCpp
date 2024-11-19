#include "SocketMessageHandler.h"
#include <winsock2.h> // Windows Sockets API
#include <ws2tcpip.h> // Дополнительные функции для работы с адресами
#include <cstring>
#include <iostream>

// Подключение библиотеки для Windows Sockets API
#pragma comment(lib, "Ws2_32.lib")

SocketMessageHandler::SocketMessageHandler(int socketFd) : socketFd(socketFd) {}

SocketMessageHandler::~SocketMessageHandler() {
    closesocket(socketFd); // Закрываем сокет
}

void SocketMessageHandler::SendJSON(const char* jsonData) {
    unsigned int dataLen = strlen(jsonData);
    unsigned char encrypted[1024];
    unsigned int encryptedLen = 0;

    encryptor.EncryptBytes((unsigned char*)jsonData, dataLen, encrypted, encryptedLen);

    int result = send(socketFd, (const char*)encrypted, encryptedLen, 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
    }
}

void SocketMessageHandler::ProcessSocketArgs(const char* buffer, unsigned int length) {
    unsigned char decrypted[1024];
    unsigned int decryptedLen = 0;

    encryptor.DecryptBytes((unsigned char*)buffer, length, decrypted, decryptedLen);

    ProcessMessage((const char*)decrypted, decryptedLen);
}

void SocketMessageHandler::ProcessMessage(const char* message, unsigned int length) {
    // Обработка сообщения (например, вывод на экран)
    std::cout.write(message, length);
    std::cout.flush();
}
