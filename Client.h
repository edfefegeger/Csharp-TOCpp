#ifndef CLIENT_H
#define CLIENT_H

#include "ClientSocketMessages.h"
#include "Participant.h"
#include <winsock2.h> // ��� SOCKET

// ���������� ������������ ���������� ����������
#define MAX_PARTICIPANTS 100

class Client {
public:
    static bool DesktopSwitchPending;
    static bool IsConnected;
    static Participant ParticipantList[MAX_PARTICIPANTS]; // ������ ����������
    static int ParticipantCount;                          // ���������� ����������
    static char SessionID[128];
    static ClientSocketMessages* SocketMessageHandler;
    static SOCKET TcpClient;

    static void Connect(const char* host, int port);
    static void WaitForServerMessage();

    static bool AddParticipant(const Participant& participant);
    static bool RemoveParticipant(const char* id);
};

#endif // CLIENT_H
