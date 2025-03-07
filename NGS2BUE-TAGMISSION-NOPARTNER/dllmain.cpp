#include "pch.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>

struct Coords {
    float x, y, z, w;
};

extern "C" DWORD_PTR baseAddress = 0;

extern "C" uintptr_t returnInjectCoordsTag = 0;

extern "C" uintptr_t currentLevelAddress = 0;

extern "C" uintptr_t coordsAddress = 0;

extern "C" Coords coordsToAssign = { 0.00, 0.00, 0.00, 0.00 };

extern "C" uintptr_t inventoryStartAddress = 0x3625848;

extern "C" void SetTagMissionCoords(Coords* coords, uint16_t currentLevel) {
    
    //ACOLYTE WILL STILL PULL CORRECT COORDS FOR WHATEVER REASON
    
    switch (currentLevel) {
    //WARRIOR
    case 0x0052: *coords = { -49.30,  87.06,  276.15,  0.00 }; break;
    case 0x0053: *coords = { -51.95,  21.38,  218.86,  0.00 }; break;
    case 0x0054: *coords = { -155.80, -25.31,  86.72,  0.00 }; break;
    case 0x0055: *coords = { -205.00,  29.76, -51.00,  0.00 }; break;
    case 0x0056: *coords = { 1.25,   14.85,  128.00,  0.00 }; break;
    case 0x0057: *coords = { 8.00,  305.24,  -38.00,  0.00 }; break;
    case 0x0058: *coords = { 155.25,   5.87, -256.00,  0.00 }; break;
    case 0x0059: *coords = { 196.25,  78.68,  155.00,  0.00 }; break;
    case 0x005A: *coords = { 156.25,   2.44,  155.08,  0.00 }; break;
    case 0x005B: *coords = { -27.80, -53.24, -124.30,  0.00 }; break;

    //MENTOR
    case 0x005C: *coords = { -1.25,  0.01,  -4.65,   0.00 }; break;
    case 0x005D: *coords = { 95.00,  7.35, -108.00,  0.00 }; break;
    case 0x005E: *coords = { -205.00,  29.76,  -51.00,  0.00 }; break;
    case 0x005F: *coords = { 156.30,  5.22, -120.30,  0.00 }; break;
    case 0x0060: *coords = { 8.00,  305.24, -38.00,  0.00 }; break;

    //MASTER
    case 0x0066: *coords = { -153.10, -25.31,  69.25,   0.00 }; break;
    case 0x0067: *coords = { 395.98,   30.06, -190.00,  0.00 }; break;
    case 0x0068: *coords = { 117.00,  311.76,  510.00,  0.00 }; break;
    case 0x0069: *coords = { -1.25,    1.00,  140.35,  0.00 }; break;
    case 0x006A: *coords = { 1.25,  -223.27,  190.00,  0.00 }; break;

    //UN 
    case 0x0070: *coords = { 1.25,  -223.27,  190.00,  0.00 }; break;
    case 0x0071: *coords = { 156.25,   2.44,  155.08,  0.00 }; break;
    case 0x0072: *coords = { 58.50,    3.53,  -41.25,  0.00 }; break;
    case 0x0073: *coords = { -52.65,  86.93,  267.00,  0.00 }; break;
    case 0x0074: *coords = { -896.55, 597.44, -567.48,  0.00 }; break;

   
    default: *coords = { 0.00, 0.00, 0.00, 0.00 }; break;
    }
}




void  __attribute__((naked))InjectCoordsTag() {

    __asm__ volatile(".intel_syntax noprefix;"
        "movss xmm3,xmm1;"
        "shufps xmm3,xmm3,0xC6;"
        "movss xmm3,xmm2;"
        "shufps xmm3, xmm3,0xC9;"

        "movss xmm15,xmm0;"
        

        "push rax;"
        "push rbx;"

        "mov rax, qword ptr [rip + currentLevelAddress];"
        "movzx rax, word ptr [rax];"

        "cmp ax,0x0038;"
        "je setWeapons;"
        "cmp ax,0x0039;"
        "je setWeapons;"
        "cmp ax,0x003A;"
        "je setWeapons;"
        "cmp ax,0x003B;"
        "je setWeapons;"
        "cmp ax,0x003C;"
        "je setWeapons;"
        "cmp ax,0x003D;"
        "je setWeapons;"
        "cmp ax,0x003E;"
        "je setWeapons;"
        "cmp ax,0x003F;"
        "je setWeapons;"
        "cmp ax,0x0040;"
        "je setWeapons;"
        "cmp ax,0x0041;"
        "je setWeapons;"

        "push rcx;"
        "push rdx;"
        "push r8;"
        "push r9;"

        "sub rsp,0x08;"

        "xorps xmm0,xmm0;"
        "xorps xmm14,xmm14;"

        "lea rcx, qword ptr [rip + coordsToAssign];"
        "lea rbx, qword ptr [rip + SetTagMissionCoords];"
        "mov rdx, qword ptr [rip + currentLevelAddress];"
        "movzx rdx, word ptr [rdx];"

        "call rbx;"

        "add rsp,0x08;"

        "pop r9;"
        "pop r8;"
        "pop rdx;"
        "pop rcx;"
       

     

        "comiss xmm0,xmm14;"
        "je exitCoordsTagMission;"
        "movaps xmm3,xmm0;"
        
        "setWeapons:"
        "mov rax,qword ptr [rip+inventoryStartAddress];"
        "mov rbx,0x0201000C00010007;"
        "mov qword ptr [rax],rbx;"
        "mov rbx,0x0201001102000021;"
        "mov qword ptr [rax+8],rbx;"
        "mov rbx,0x020100CC02010012;"
        "mov qword ptr [rax+16],rbx;"
        "mov rbx,0x0201001502000014;"
        "mov qword ptr [rax+24],rbx;"
        "mov rbx,0x0201001802000015;"
        "mov qword ptr [rax+32],rbx;"
        "mov rbx,0x0001009300010000;"
        "mov qword ptr [rax+40],rbx;"
        "mov rbx,0x0001015100010093;"
        "mov qword ptr [rax+48],rbx;"
        "mov rbx,0x0201005202000006;"
        "mov qword ptr [rax+56],rbx;"
        "mov rbx,0x0201005302000092;"
        "mov qword ptr [rax+64],rbx;"
        "mov rbx,0x0001000902000008;"
        "mov qword ptr [rax+72],rbx;"
        "mov rbx,0x0001000500010094;"
        "mov qword ptr [rax+80],rbx;"
        "mov rbx,0x0000000000000000;"
        "mov qword ptr [rax+88],rbx;"
        "jmp exitCoordsTagMission;"





      
        "exitCoordsTagMission:"
        "pop rbx;"
        "pop rax;"
        "jmp qword ptr [rip + returnInjectCoordsTag];"

        );
}


struct HookInfo {
    DWORD_PTR offset;
    int length;
    void* hookFunction;
    const char* hookName;
    DWORD_PTR* returnAddress;
    int nopeLen;
};

HookInfo hooks[] = {

    {0x170E90C, 16, InjectCoordsTag, "InjectCoordsTag", &returnInjectCoordsTag, 0},
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
            MessageBoxA(NULL, ss.str().c_str(), "Hook Error", MB_OK | MB_ICONERROR);
        }
    }
}




DWORD_PTR GetBaseAddress(LPCWSTR module) {
    return (DWORD_PTR)GetModuleHandle(module);
}



void NopMemory(void* address, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(address, 0x90, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}




TCHAR* GetExecutablePath(TCHAR* exePath, DWORD size) {
    GetModuleFileName(NULL, exePath, size);
    TCHAR* lastSlash = wcsrchr(exePath, '\\');
    if (lastSlash) {
        *lastSlash = '\0';
    }
    return exePath;
}





void WriteByte(DWORD_PTR address, BYTE value) {
    DWORD oldProtect;
    VirtualProtect((void*)address, sizeof(BYTE), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)address = value;
    VirtualProtect((void*)address, sizeof(BYTE), oldProtect, &oldProtect);
}




void WriteMemory(void* address, const void* buffer, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(address, buffer, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}




DWORD WINAPI MainThread(LPVOID param) {
    Sleep(2000);

    baseAddress = (DWORD_PTR)GetModuleHandle(L"gamemodule.dll");
  


    if (baseAddress == 0) {
        //MessageBoxA(NULL, "Failed to get base address of modules. \nHALF CUTS WILL NOT BE ENABLED", "ERROR", MB_OK);
        return 0;
    }
    //DISABLE ASSIGN IN TAG MISSION
    uintptr_t disableTag = baseAddress + 0x147B3EF;
    NopMemory((void*)disableTag, 5);

    currentLevelAddress = baseAddress + 0x222EEC8;
    coordsAddress = baseAddress + 0x6C52680;
    inventoryStartAddress += baseAddress;
    int hookSize = sizeof(hooks) / sizeof(HookInfo);
    ApplyHooks(hooks, hookSize, baseAddress);

    
   
  

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








































































