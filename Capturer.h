#ifndef CAPTURER_H
#define CAPTURER_H

#include "ClientSocketMessages.h"
#include <windows.h>

class Capturer {
public:
    bool IsCapturing;               
    int PauseForMilliseconds;      

    Capturer();                      
    ~Capturer();                   

    void BeginCapturing(          
        const char* participantID,
        ClientSocketMessages& socketHandler,
        bool (*isConnected)(),
        bool (*participantExists)(const char*)
    );

    void StopCapturing();          

private:
    const char* participantID;
    ClientSocketMessages* socketHandler; 
    bool (*isConnectedFunc)();       
    bool (*participantExistsFunc)(const char*); 

    HANDLE captureThreadHandle;

    static DWORD WINAPI CaptureThreadProc(LPVOID param);
};

#endif // CAPTURER_H
