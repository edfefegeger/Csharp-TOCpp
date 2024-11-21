#include "Client.h"
#include <winsock2.h>
#include <cstring>
#include <ws2tcpip.h> 


Participant Client::ParticipantList[MAX_PARTICIPANTS];
int Client::ParticipantCount = 0;

bool Client::DesktopSwitchPending = false;
bool Client::IsConnected = false;
char Client::SessionID[128] = {};
ClientSocketMessages* Client::SocketMessageHandler = nullptr;
SOCKET Client::TcpClient = INVALID_SOCKET;

void Client::Connect(const char* host, int port) {
    if (IsConnected) return;

    TcpClient = socket(AF_INET, SOCK_STREAM, 0);
    if (TcpClient == INVALID_SOCKET) return;

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);


    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) <= 0) {
        closesocket(TcpClient);
        return;
    }

    if (connect(TcpClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(TcpClient);
        return;
    }

    SocketMessageHandler = new ClientSocketMessages(TcpClient);
    WaitForServerMessage();
}

void Client::WaitForServerMessage() {
    char buffer[1024];
    while (true) {
        int bytesRead = recv(TcpClient, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            break;
        }

        buffer[bytesRead] = '\0';

    }
}

bool Client::AddParticipant(const Participant& participant) {
    if (ParticipantCount >= MAX_PARTICIPANTS) return false;

    ParticipantList[ParticipantCount++] = participant;
    return true;
}

bool Client::RemoveParticipant(const char* id) {
    for (int i = 0; i < ParticipantCount; ++i) {
        if (strcmp(ParticipantList[i].ID, id) == 0) {
            for (int j = i; j < ParticipantCount - 1; ++j) {
                ParticipantList[j] = ParticipantList[j + 1];
            }
            --ParticipantCount;
            return true;
        }
    }
    return false;
}
