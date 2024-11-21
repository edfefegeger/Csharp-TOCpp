#ifndef CAPTURER_H
#define CAPTURER_H

#include "ClientSocketMessages.h"
#include <windows.h>

class Capturer {
public:
    bool IsCapturing;                  // Флаг, указывающий, идет ли захват
    int PauseForMilliseconds;          // Время паузы в миллисекундах

    Capturer();                        // Конструктор
    ~Capturer();                       // Деструктор

    void BeginCapturing(               // Начать захват
        const char* participantID,
        ClientSocketMessages& socketHandler,
        bool (*isConnected)(),
        bool (*participantExists)(const char*)
    );

    void StopCapturing();              // Остановить захват

private:
    const char* participantID;         // ID участника
    ClientSocketMessages* socketHandler;  // Указатель на обработчик сообщений сокета
    bool (*isConnectedFunc)();         // Указатель на функцию проверки соединения
    bool (*participantExistsFunc)(const char*); // Указатель на функцию проверки участника

    HANDLE captureThreadHandle;        // Дескриптор потока

    static DWORD WINAPI CaptureThreadProc(LPVOID param); // Функция для потока
};

#endif // CAPTURER_H
