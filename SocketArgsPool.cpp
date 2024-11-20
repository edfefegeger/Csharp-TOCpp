#include "SocketArgsPool.h"
#include <mutex>
#include <algorithm> // ��� ������

// ���������� ����������� ���������� ��� ������
std::vector<SocketArgs> SocketArgsPool::SocketReceiveArgs;
std::vector<SocketArgs> SocketArgsPool::SocketSendArgs;

std::mutex receiveMutex;
std::mutex sendMutex;

SocketArgs* SocketArgsPool::GetReceiveArg() {
    receiveMutex.lock();
    for (auto& arg : SocketReceiveArgs) {
        if (!arg.IsInUse) {
            arg.IsInUse = true;
            receiveMutex.unlock();
            return &arg;
        }
    }

    // ���� ��������� ���������� ���, ������� �����
    SocketArgs newArg(1024); // ������ ������� ������
    newArg.IsInUse = true;
    SocketReceiveArgs.push_back(newArg);
    receiveMutex.unlock();
    return &SocketReceiveArgs.back();
}

SocketArgs* SocketArgsPool::GetSendArg() {
    sendMutex.lock();
    for (auto& arg : SocketSendArgs) {
        if (!arg.IsInUse) {
            arg.IsInUse = true;
            sendMutex.unlock();
            return &arg;
        }
    }

    // ���� ��������� ���������� ���, ������� �����
    SocketArgs newArg(1024); // ������ ������� ������
    newArg.IsInUse = true;
    SocketSendArgs.push_back(newArg);
    sendMutex.unlock();
    return &SocketSendArgs.back();
}
