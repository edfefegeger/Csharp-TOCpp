#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "SocketMessageHandler.h"

// Подключение библиотеки для Windows Sockets API
#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize WinSock." << std::endl;
        return -1;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(443); // Замените на порт вашего сервера
    inet_pton(AF_INET, "64.226.68.205", &serverAddr.sin_addr); // Замените на IP вашего сервера

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    SocketMessageHandler handler(clientSocket);
    handler.SendJSON("{\"Type\": \"TestPing\"}");

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
