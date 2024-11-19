#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream> // Для работы с файлами
#include <cstring>
#include <ctime>
#include "SocketMessageHandler.h"
#include "Config.h" // Подключаем конфигурацию

#pragma comment(lib, "Ws2_32.lib")

// Пример функции для вывода сообщений об ошибках
void PrintErrorMessage(const char* msg) {
    DWORD err = WSAGetLastError();
    char buffer[256];
    sprintf_s(buffer, "Error: %s. Code: %lu\n", msg, err);
    OutputDebugStringA(buffer); // Выводит в окно отладки
    printf("%s", buffer);       // Выводит в консоль
}

// Функция для записи в лог (в файл и в консоль)
void LogMessage(const char* message) {
    // Получаем текущее время
    time_t now = time(0);
    char timestamp[26];
    ctime_s(timestamp, sizeof(timestamp), &now);

    // Удаляем символ новой строки из timestamp
    timestamp[strcspn(timestamp, "\n")] = '\0';

    // Формируем полное сообщение
    char fullMessage[512];
    strcpy_s(fullMessage, "[");
    strcat_s(fullMessage, timestamp);
    strcat_s(fullMessage, "] ");
    strcat_s(fullMessage, message);

    // Записываем в файл
    FILE* logFile;
    if (fopen_s(&logFile, "connection.log", "a") == 0) {
        fprintf(logFile, "%s\n", fullMessage);
        fclose(logFile);
    }

    // Выводим в консоль
    printf("%s\n", fullMessage);
}

// Функция для отправки сообщения типа "TestMessageServer"
void SendTestMessage(SocketMessageHandler& handler, const char* message) {
    const char* jsonTemplate = "{\"Type\": \"TestMessageServer\", \"Message\": \"%s\"}";
    char jsonData[1024];
    sprintf_s(jsonData, jsonTemplate, message);
    handler.SendJSON(jsonData);
}

// Функция для отправки сообщения типа "TestPing"
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
    // Получаем параметры из Config
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
    serverAddr.sin_port = htons(config.ClientPort); // Используем порт из Config
    inet_pton(AF_INET, config.ClientHost, &serverAddr.sin_addr); // Используем хост из Config

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        LogMessage("Connection failed");
        PrintErrorMessage("Connection failed");
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }
    LogMessage("Connected to server successfully");

    SocketMessageHandler handler(clientSocket);

    // Отправляем Ping
    LogMessage("Sending Ping...");
    SendPing(handler);
    LogMessage("Ping sent successfully");

    // Отправляем сообщение
    LogMessage("Sending TestMessageServer...");
    SendTestMessage(handler, "Hello, this is a test message!");
    LogMessage("TestMessageServer sent successfully");

    closesocket(clientSocket);
    LogMessage("Socket closed successfully");
    WSACleanup();
    LogMessage("WinSock cleaned up");

    return 0;
}
