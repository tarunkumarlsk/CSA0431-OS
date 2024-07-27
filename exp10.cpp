#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    DWORD dwWritten;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\MyNamedPipe"), // name of the pipe
        PIPE_ACCESS_OUTBOUND,             // write access
        PIPE_TYPE_MESSAGE |               // message type pipe
        PIPE_READMODE_MESSAGE |           // message-read mode
        PIPE_WAIT,                        // blocking mode
        PIPE_UNLIMITED_INSTANCES,         // max. instances
        512,                              // output buffer size
        512,                              // input buffer size
        0,                                // client time-out
        NULL);                            // default security attribute

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed, GLE=%d.\n", GetLastError());
        return 1;
    }

    printf("Waiting for client to connect...\n");

    // Wait for the client to connect
    BOOL connected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

    if (!connected) {
        printf("ConnectNamedPipe failed, GLE=%d.\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    // Write to the pipe
    char message[] = "Hello";
    WriteFile(
        hPipe,                  // handle to pipe
        message,                // buffer to write from
        sizeof(message),        // number of bytes to write
        &dwWritten,             // number of bytes written
        NULL);                  // not overlapped I/O

    if (!dwWritten) {
        printf("WriteFile failed, GLE=%d.\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Message sent: %s\n", message);

    // Close the pipe
    CloseHandle(hPipe);

    return 0;
}
#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    DWORD dwRead;
    char buffer[512];

    // Open the named pipe
    hPipe = CreateFile(
        TEXT("\\\\.\\pipe\\MyNamedPipe"), // name of the pipe
        GENERIC_READ,                     // read access
        0,                                // no sharing
        NULL,                             // default security attributes
        OPEN_EXISTING,                    // opens existing pipe
        0,                                // default attributes
        NULL);                            // no template file

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateFile failed, GLE=%d.\n", GetLastError());
        return 1;
    }

    // Read from the pipe
    BOOL success = ReadFile(
        hPipe,                // handle to pipe
        buffer,               // buffer to receive data
        sizeof(buffer),       // size of buffer
        &dwRead,              // number of bytes read
        NULL);                // not overlapped I/O

    if (!success || dwRead == 0) {
        printf("ReadFile failed, GLE=%d.\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Message received: %s\n", buffer);

    // Close the pipe
    CloseHandle(hPipe);

    return 0;
}
