#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream> 
#include <cstring>
#include <ctime>
#include "SocketMessageHandler.h"
#include "Config.h"

#pragma comment(lib, "Ws2_32.lib")

void PrintErrorMessage(const char* msg) {
    DWORD err = WSAGetLastError();
    char buffer[256];
    sprintf_s(buffer, "Error: %s. Code: %lu\n", msg, err);
    OutputDebugStringA(buffer); 
    printf("%s", buffer);      
}

void LogMessage(const char* message) {
    time_t now = time(0);
    char timestamp[26];
    ctime_s(timestamp, sizeof(timestamp), &now);
    timestamp[strcspn(timestamp, "\n")] = '\0';

    char fullMessage[512];
    strcpy_s(fullMessage, "[");
    strcat_s(fullMessage, timestamp);
    strcat_s(fullMessage, "] ");
    strcat_s(fullMessage, message);

    FILE* logFile;
    if (fopen_s(&logFile, "connection.log", "a") == 0) {
        fprintf(logFile, "%s\n", fullMessage);
        fclose(logFile);
    }

    printf("%s\n", fullMessage);
}

void SendTestMessage(SocketMessageHandler& handler, const char* message) {
    const char* jsonTemplate = "{\"Type\": \"TestMessageServer\", \"Message\": \"%s\"}";
    char jsonData[1024];
    sprintf_s(jsonData, jsonTemplate, message);
    handler.SendJSON(jsonData);
}

void SendPing(SocketMessageHandler& handler) {
    time_t now = time(0);
    char dateStr[26];

    ctime_s(dateStr, sizeof(dateStr), &now);

    const char* jsonTemplate = "{\"Type\": \"TestPing\", \"Date\": \"%s\"}";
    char jsonData[1024];
    sprintf_s(jsonData, jsonTemplate, dateStr);
    handler.SendJSON(jsonData);
}

int main() {
    Config& config = Config::Instance();

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LogMessage("Failed to initialize WinSock");
        PrintErrorMessage("Failed to initialize WinSock");
        return -1;
    }
    LogMessage("WinSock initialized successfully");

    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        LogMessage("Socket creation failed");
        PrintErrorMessage("Socket creation failed");
        WSACleanup();
        return -1;
    }
    LogMessage("Socket created successfully");

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(config.ClientPort); 
    inet_pton(AF_INET, config.ClientHost, &serverAddr.sin_addr); 

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        LogMessage("Connection failed");
        PrintErrorMessage("Connection failed");
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }
    LogMessage("Connected to server successfully");

    SocketMessageHandler handler(clientSocket);
    LogMessage("Sending Ping...");
    SendPing(handler);
    LogMessage("Ping sent successfully");

    LogMessage("Sending TestMessageServer...");
    SendTestMessage(handler, "Hello, this is a test message!");
    LogMessage("TestMessageServer sent successfully");

    char recvBuffer[1024];
    int recvResult = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
    if (recvResult > 0) {
        handler.ProcessSocketArgs(recvBuffer, recvResult);
    }
    else if (recvResult == 0) {
        LogMessage("Connection closed by server");
    }
    else {
        PrintErrorMessage("Receive failed");
    }

    closesocket(clientSocket);
    LogMessage("Socket closed successfully");
    WSACleanup();
    LogMessage("WinSock cleaned up");

    return 0;
}
