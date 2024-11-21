#include "ClientSocketMessages.h"
#include <ctime>
#include <cstdio>

ClientSocketMessages::ClientSocketMessages(SOCKET socketOut) : socketOut(socketOut) {}

void ClientSocketMessages::SendJSON(const char* json) {
    send(socketOut, json, strlen(json), 0);
}

void ClientSocketMessages::SendTestMessage(const char* message) {
    const char* jsonTemplate = "{\"Type\": \"TestMessageServer\", \"Message\": \"%s\"}";
    char jsonData[1024];
    sprintf_s(jsonData, jsonTemplate, message);
    SendJSON(jsonData);
}

void ClientSocketMessages::SendPing() {
    time_t now = time(0);
    char dateStr[26];

    ctime_s(dateStr, sizeof(dateStr), &now);

    const char* jsonTemplate = "{\"Type\": \"TestPing\", \"Date\": \"%s\"}";
    char jsonData[1024];
    sprintf_s(jsonData, jsonTemplate, dateStr);
    SendJSON(jsonData);
}
