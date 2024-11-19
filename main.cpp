#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring> // Для работы с C-строками
#include <ctime>   // Для получения текущей даты и времени
#include "SocketMessageHandler.h"

// Подключение библиотеки для Windows Sockets API
#pragma comment(lib, "Ws2_32.lib")

// Пример функции для вывода сообщений об ошибках
void PrintErrorMessage(const char* msg) {
    DWORD err = WSAGetLastError();
    char buffer[256];
    sprintf_s(buffer, "Error: %s. Code: %lu\n", msg, err);
    OutputDebugStringA(buffer); // Выводит в окно отладки, вместо std::cerr
}

// Функция для отправки сообщения типа "TestMessageServer"
void SendTestMessage(SocketMessageHandler& handler, const char* message) {
    // Формируем JSON-строку
    const char* jsonTemplate = "{\"Type\": \"TestMessageServer\", \"Message\": \"%s\"}";
    char jsonData[1024];  // Буфер для сформированной строки JSON
    sprintf_s(jsonData, jsonTemplate, message);  // Подставляем сообщение в JSON
    handler.SendJSON(jsonData);  // Отправляем через сокет
}

// Функция для отправки сообщения типа "TestPing"
void SendPing(SocketMessageHandler& handler) {
    // Получаем текущую дату и время
    time_t now = time(0);
    char dateStr[26];  // Массив для даты (26 символов — это длина строки, возвращаемой ctime_s)

    // Используем ctime_s для безопасного получения строки даты
    size_t len;
    ctime_s(dateStr, sizeof(dateStr), &now);  // ctime_s записывает дату в dateStr

    // Формируем JSON-строку для Ping
    const char* jsonTemplate = "{\"Type\": \"TestPing\", \"Date\": \"%s\"}";
    char jsonData[1024];  // Буфер для сформированной строки JSON
    sprintf_s(jsonData, jsonTemplate, dateStr);  // Подставляем дату в JSON
    handler.SendJSON(jsonData);  // Отправляем через сокет
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        PrintErrorMessage("Failed to initialize WinSock");
        return -1;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        PrintErrorMessage("Socket creation failed");
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(443); // Замените на порт вашего сервера
    inet_pton(AF_INET, "64.226.68.205", &serverAddr.sin_addr); // Замените на IP вашего сервера

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        PrintErrorMessage("Connection failed");
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    SocketMessageHandler handler(clientSocket);

    // Отправляем Ping
    SendPing(handler);

    // Отправляем сообщение
    SendTestMessage(handler, "Hello, this is a test message!");

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
