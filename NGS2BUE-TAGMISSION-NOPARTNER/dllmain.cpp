#include "pch.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>

struct Coords {
    float x, y, z, w;
};

struct LevelData {
    uint16_t missionID;
    float x, y, z, w;
};

//ACOLYTE WILL STILL PULL CORRECT COORDS FOR WHATEVER REASON
const LevelData levelDataArray[] = {
    // WARRIOR
    {0x0052, -49.30f,  87.06f,  276.15f,  0.00f},
    {0x0053, -51.95f,  21.38f,  218.86f,  0.00f},
    {0x0054, -155.80f, -25.31f,  86.72f,  0.00f},
    {0x0055, -205.00f,  29.76f, -51.00f,  0.00f},
    {0x0056, 1.25f,   14.85f,  128.00f,  0.00f},
    {0x0057, 8.00f,  305.24f,  -38.00f,  0.00f},
    {0x0058, 155.25f,   5.87f, -256.00f,  0.00f},
    {0x0059, 196.25f,  78.68f,  155.00f,  0.00f},
    {0x005A, 156.25f,   2.44f,  155.08f,  0.00f},
    {0x005B, -27.80f, -53.24f, -124.30f,  0.00f},

    // MENTOR
    {0x005C, -1.25f,  0.01f,  -4.65f,   0.00f},
    {0x005D, 95.00f,  7.35f, -108.00f,  0.00f},
    {0x005E, -205.00f,  29.76f,  -51.00f,  0.00f},
    {0x005F, 156.30f,  5.22f, -120.30f,  0.00f},
    {0x0060, 8.00f,  305.24f, -38.00f,  0.00f},

    // MASTER
    {0x0066, -153.10f, -25.31f,  69.25f,   0.00f},
    {0x0067, 395.98f,   30.06f, -190.00f,  0.00f},
    {0x0068, 117.00f,  311.76f,  510.00f,  0.00f},
    {0x0069, -1.25f,    1.00f,  140.35f,  0.00f},
    {0x006A, 1.25f,  -223.27f,  190.00f,  0.00f},

    // UN 
    {0x0070, 1.25f,  -223.27f,  190.00f,  0.00f},
    {0x0071, 156.25f,   2.44f,  155.08f,  0.00f},
    {0x0072, 58.50f,    3.53f,  -41.25f,  0.00f},
    {0x0073, -52.65f,  86.93f,  267.00f,  0.00f},
    {0x0074, -896.55f, 597.44f, -567.48f,  0.00f}
};

const uint16_t acolyteMissions[] = {
    0x0038, 0x0039, 0x003A, 0x003B, 0x003C,
    0x003D, 0x003E, 0x003F, 0x0040, 0x0041
};

extern "C" DWORD_PTR baseAddress = 0;

extern "C" uintptr_t returnInjectCoordsTag = 0;

extern "C" uintptr_t currentLevelAddress = 0;

extern "C" uintptr_t coordsAddress = 0;

extern "C" Coords coordsToAssign = { 0.00, 0.00, 0.00, 0.00 };

extern "C" uintptr_t inventoryStartAddress = 0x3625848;

uintptr_t exitToMainMenuAddress = 0x222EE98;

uintptr_t gameModeAddress = 0x222EE9C;

extern "C" uintptr_t ccFlagAddress = 0x222EE92;

uintptr_t playerHPAddress = 0x3380DB6;


extern "C" void SetTagMissionCoords(Coords* coords, uint16_t currentLevel) {

    for (auto& levelID : levelDataArray) {
        if (levelID.missionID == currentLevel) {
            *coords = { levelID.x, levelID.y, levelID.z, levelID.w };
            return;
        }
        *coords = { 0.00, 0.00, 0.00, 0.00 };
    }

}

bool isTagMission(uint16_t currentLevel) {
    for (auto& level : levelDataArray) {
        if (level.missionID == currentLevel) { return true; }
    }
    return false;
}

bool isAcolyteMission(uint16_t missionID) {
    return std::find(std::begin(acolyteMissions), std::end(acolyteMissions), missionID) != std::end(acolyteMissions);
}

void ReturnToMainMenu() {
    *(uint8_t*)exitToMainMenuAddress = 0x01;
    *(uint8_t*)ccFlagAddress = 0x00;
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
        "mov byte ptr [rip + ccFlagAddress],0x01;"
        
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
    exitToMainMenuAddress += baseAddress;
    gameModeAddress += baseAddress;
    ccFlagAddress += baseAddress;
    playerHPAddress += baseAddress;

    int hookSize = sizeof(hooks) / sizeof(HookInfo);
    ApplyHooks(hooks, hookSize, baseAddress);

    while (true) {


        uint16_t currentLevel = *(uint16_t*)currentLevelAddress;
        if (isTagMission(currentLevel) || isAcolyteMission(currentLevel)) {
            *(uint8_t*)ccFlagAddress = 0x01;

            if (*(uint8_t*)gameModeAddress == 0x08) {
                ReturnToMainMenu();
            }
            if (*(uint16_t*)playerHPAddress <= 0) {
                ReturnToMainMenu();
            }
        }
       

        
        Sleep(1000);
    }
}
       
      



BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {

    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hinstDLL, 0, 0);
        break;

    }

    return true;
}








































































