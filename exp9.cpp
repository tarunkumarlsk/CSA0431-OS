#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    char buff[100];

    // Create a named shared memory segment
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        1024,                    // maximum object size (low-order DWORD)
        "Local\\MySharedMemory"); // name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map the shared memory segment into the address space
    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,                // handle to map object
        FILE_MAP_ALL_ACCESS,     // read/write permission
        0,
        0,
        1024);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter some data to write to shared memory: ");
    fgets(buff, sizeof(buff), stdin);
    // Copy data to the shared memory
    CopyMemory((PVOID)pBuf, buff, (strlen(buff) + 1) * sizeof(char));

    printf("You wrote: %s\n", pBuf);

    // Clean up
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
