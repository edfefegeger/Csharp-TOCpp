#include "Capturer.h"
#include <windows.h>

// Конструктор
Capturer::Capturer() : IsCapturing(false), PauseForMilliseconds(2000), captureThreadHandle(nullptr) {}

// Функция для захвата
DWORD WINAPI Capturer::CaptureThreadProc(LPVOID param) {
    Capturer* capturer = reinterpret_cast<Capturer*>(param);

    while (capturer->IsCapturing &&
        capturer->isConnectedFunc() &&
        capturer->participantExistsFunc(capturer->participantID)) {
        try {
            char buffer[1024 * 1024] = {}; // Random buffer
            capturer->socketHandler->SendJSON(buffer); // Simulate sending bytes
        }
        catch (...) {
            // Обработка исключений (если потребуется)
        }
        Sleep(600);
    }
    return 0;
}

// Запуск захвата
void Capturer::BeginCapturing(
    const char* participantID,
    ClientSocketMessages& socketHandler,
    bool (*isConnected)(),
    bool (*participantExists)(const char*)
) {
    if (!participantExists(participantID)) return;

    this->participantID = participantID;
    this->socketHandler = &socketHandler;
    this->isConnectedFunc = isConnected;
    this->participantExistsFunc = participantExists;

    IsCapturing = true;

    // Создаём поток с помощью WinAPI
    captureThreadHandle = CreateThread(
        nullptr,             // Атрибуты безопасности
        0,                   // Размер стека
        CaptureThreadProc,   // Функция потока
        this,                // Параметр для потока
        0,                   // Флаги создания
        nullptr              // Указатель для идентификатора потока
    );

    if (!captureThreadHandle) {
        // Если поток не удалось создать
        IsCapturing = false;
        return;
    }

    // Цикл основного потока
    while (IsCapturing && isConnected() && participantExists(participantID)) {
        try {
            Sleep(PauseForMilliseconds);
            PauseForMilliseconds = 2000;
        }
        catch (...) {
            Sleep(600);
        }
    }
}

// Деструктор для завершения потока
Capturer::~Capturer() {
    StopCapturing();
}

// Остановка захвата
void Capturer::StopCapturing() {
    if (IsCapturing) {
        IsCapturing = false;
        if (captureThreadHandle) {
            // Ожидаем завершение потока
            WaitForSingleObject(captureThreadHandle, INFINITE);
            CloseHandle(captureThreadHandle);
            captureThreadHandle = nullptr;
        }
    }
}
