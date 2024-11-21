#include "Capturer.h"
#include <windows.h>


Capturer::Capturer() : IsCapturing(false), PauseForMilliseconds(2000), captureThreadHandle(nullptr) {}


DWORD WINAPI Capturer::CaptureThreadProc(LPVOID param) {
    Capturer* capturer = reinterpret_cast<Capturer*>(param);

    while (capturer->IsCapturing &&
        capturer->isConnectedFunc() &&
        capturer->participantExistsFunc(capturer->participantID)) {
        try {
            char buffer[1024 * 1024] = {};
            capturer->socketHandler->SendJSON(buffer); 
        }
        catch (...) {
            Sleep(600);
        }
        Sleep(600);
    }
    return 0;
}


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

 
    captureThreadHandle = CreateThread(
        nullptr,        
        0,                   
        CaptureThreadProc,   
        this,               
        0,                   
        nullptr              
    );

    if (!captureThreadHandle) {
        IsCapturing = false;
        return;
    }

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
Capturer::~Capturer() {
    StopCapturing();
}


void Capturer::StopCapturing() {
    if (IsCapturing) {
        IsCapturing = false;
        if (captureThreadHandle) {
            WaitForSingleObject(captureThreadHandle, INFINITE);
            CloseHandle(captureThreadHandle);
            captureThreadHandle = nullptr;
        }
    }
}
