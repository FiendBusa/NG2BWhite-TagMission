#include "pch.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <fstream>
#include <iostream>
#include <iomanip>
#include "globals.h"
#include "hook.h"
#include "functions.h"


//#include "bass.h"

//#pragma comment(lib,"bass.lib")

/*Author: Fiend Busa*/

DWORD_PTR GetBaseAddress(LPCWSTR module) {
    return (DWORD_PTR)GetModuleHandle(module);
}


struct HookInfo {
    DWORD_PTR offset;
    int length;
    void* hookFunction;
    const char* hookName;
    DWORD_PTR* returnAddress;
    int nopeLen;
};

void NopMemory(void* address, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(address, 0x90, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}




void dumpMemoryToFile(DWORD_PTR address, size_t size, const std::string& filePath) {
    if (IsBadReadPtr((void*)address, size)) {
        std::cerr << "Invalid memory address!" << std::endl;
        return;
    }

    // Open the file in append mode
    std::ofstream file(filePath, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }

    // Write a separator or header for each new dump
    file << "\n--- Memory Dump ---\n";

    // Dump the memory
    file << "Memory dump at address 0x" << std::hex << address << ":" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        unsigned char* byteAddress = (unsigned char*)(address + i);
        file << std::hex << std::setw(2) << std::setfill('0') << (int)*byteAddress << " ";
        if ((i + 1) % 16 == 0) file << "\n"; // New line after 16 bytes
    }

    file << "\n"; // Separate each dump with a newline
    file.close();
}

TCHAR* GetExecutablePath(TCHAR* exePath, DWORD size) {
    GetModuleFileName(NULL, exePath, size);
    TCHAR* lastSlash = wcsrchr(exePath, '\\');
    if (lastSlash) {
        *lastSlash = '\0';
    }
    return exePath;
}
void LoadConfig() {
    TCHAR exePath[MAX_PATH];
    GetExecutablePath(exePath, MAX_PATH);




}

bool compareMemory(DWORD_PTR address, const std::vector<unsigned char>& pattern) {
    if (IsBadReadPtr((void*)address, pattern.size())) {
        std::cerr << "Invalid memory address!" << std::endl;
        return false;
    }


    for (size_t i = 0; i < pattern.size(); ++i) {
        unsigned char* byteAddress = (unsigned char*)(address + i);
        if (*byteAddress != pattern[i]) {
            return false;
        }
    }
    return true;
}


HookInfo hooks[] = {
    {0x1F93E60, 16, InjectLvlHelper, "InjecLvlHelper", &returnInjectLvlHelper, 0},
    {0x1AC0807, 15, InjectHPScaler, "InjectHPScaler", &returnInjectHPScaler, 0},
    //{0x3EA5449, 16, InjectPinoBaseAddress,"InjectPinoBaseAddress", &returnInjectPinoBaseAddress,0}
};

bool Hook(void* hookAddress, void* myFunc, int len, int nopeLen = 0) {

    if (len < 14 && nopeLen <= 0) {
        return false;
    }

    DWORD oldProtect;
    VirtualProtect(hookAddress, len, PAGE_EXECUTE_READWRITE, &oldProtect);


    *(BYTE*)hookAddress = 0xFF;
    *((BYTE*)hookAddress + 1) = 0x25;
    *(DWORD*)((BYTE*)hookAddress + 2) = 0;
    *(DWORD_PTR*)((BYTE*)hookAddress + 6) = (DWORD_PTR)myFunc;

    if (nopeLen > 0) {
        for (int i = 0; i < nopeLen; i++) {
            *((BYTE*)hookAddress + len + i) = 0x90;
        }
    }

    VirtualProtect(hookAddress, len, oldProtect, &oldProtect);

    return true;
}




void ApplyHooks(HookInfo* hooks, int count, DWORD_PTR baseAddress) {
    for (int i = 0; i < count; i++) {
        DWORD_PTR hookAddress = baseAddress + hooks[i].offset;
        if (hooks[i].returnAddress) {
            *(hooks[i].returnAddress) = hookAddress + hooks[i].length;
        }
        if (!Hook((void*)hookAddress, hooks[i].hookFunction, hooks[i].length, hooks[i].nopeLen)) {
            std::stringstream ss;
            //ss << "Failed to hook: " << hooks[i].hookName << " at address: 0x" << std::hex << hookAddress;
            MessageBoxA(NULL, ss.str().c_str(), "Hook Error", MB_OK | MB_ICONERROR);
        }
    }
}








void WriteMemory(void* address, const void* buffer, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(address, buffer, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}





DWORD WINAPI MainThread(LPVOID param) {
    Sleep(20000);

    lopBaseAddress = (DWORD_PTR)GetModuleHandle(L"LOP-Win64-Shipping.exe");

    injectHPScaler0875 += lopBaseAddress;
    

    if (lopBaseAddress == 0) {
        MessageBoxA(NULL, "Failed to get base address of modules", "ERROR", MB_OK);
        return 0;
    }


    int hookCount = sizeof(hooks) / sizeof(HookInfo);
    ApplyHooks(hooks, hookCount, lopBaseAddress);



    while (true) {
        /*  if (previousAddress != addressFnameString) {
              dumpMemoryToFile(addressFnameString, 64, "D:\\dump.txt");
              previousAddress = addressFnameString;
          }*/
        if (GetAsyncKeyState(0x26) & 0x8000) {
            std::string activeChapter = "Current Chapter: " + std::to_string(static_cast<uintptr_t>(currentChapter));
            MessageBoxA(NULL, activeChapter.c_str(), "Debug Info", MB_OK | MB_TOPMOST);
        }


        Sleep(10);

    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {

    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hinstDLL, 0, 0);
        break;

    }

    return true;
}








































































