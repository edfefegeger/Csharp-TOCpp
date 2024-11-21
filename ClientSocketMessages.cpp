#define _CRT_SECURE_NO_WARNINGS
#include "ClientSocketMessages.h"
#include <cstring>
#include <ctime>
#include <cstdio>

ClientSocketMessages::ClientSocketMessages(SOCKET socketOut) : socketOut(socketOut) {}

void ClientSocketMessages::SendJSON(const char* json) {
    send(socketOut, json, strlen(json), 0);
}

void ClientSocketMessages::SendTestMessage(const char* message) {
    char buffer[1024];
    sprintf_s(buffer, sizeof(buffer), "{\"Type\": \"TestMessageServer\", \"Message\": \"%s\"}", message);
    SendJSON(buffer);
}

void ClientSocketMessages::SendPing() {
    char buffer[1024];
    time_t now = time(0);
    struct tm localtm;
    localtime_s(&localtm, &now);
    char timeStr[128];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localtm);
    sprintf_s(buffer, sizeof(buffer), "{\"Type\": \"TestPing\", \"Date\": \"%s\"}", timeStr);
    SendJSON(buffer);
}
