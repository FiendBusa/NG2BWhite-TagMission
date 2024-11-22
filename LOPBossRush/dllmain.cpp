#include "pch.h"
#include <Windows.h>
#include <Xinput.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "SimpleIni.h"
//#include "bass.h"

//#pragma comment(lib,"bass.lib")

/*Author: Fiend Busa*/

DWORD_PTR GetBaseAddress(LPCWSTR module) {
    return (DWORD_PTR)GetModuleHandle(module);
}



struct BossInfo {
    std::wstring name;
    float x, y, z;
    float orientation;
    bool isGroupStart;
    bool isGroupEnd;
};;

struct HookInfo {
    DWORD_PTR offset;
    int length;
    void* hookFunction;
    const char* hookName;
    DWORD_PTR* returnAddress;
};

struct BlackRabbit {
    std::vector<BossInfo> members;
};

BlackRabbit blackRabbit1 = {
    {
        {L"CH05_Stalker_BRabbit_StrongMale_Boss_00", 17177.75, 24574.95, 5738.50},
        {L"CH05_Stalker_BRabbit_Female_Boss_00", 16109.74, 24356.96, 5740.17},
        {L"CH05_Stalker_BRabbit_NormalMale_Boss_00", 15927.28, 25043.33, 5741.02},
        {L"CH05_Stalker_BRabbit_TallMale_Boss_00", 17837.36, 24912.91, 5739.98}
    }
};

BlackRabbit blackRabbit2 = {
    {
        {L"CH11_Stalker_BRabbit_StrongMale_Boss_01", 17177.75, 24574.95, 5738.50},
        {L"CH11_Stalker_BRabbit_Female_Boss_01", 16109.74, 24356.96, 5740.17},
        {L"CH11_Stalker_BRabbit_NormalMale_Boss_01", 15927.28, 25043.33, 5741.02},
        {L"CH11_Stalker_BRabbit_TallMale_Boss_01", 17837.36, 24912.91, 5739.98}
    }
};

//WHERE TO SPAWN NPC
extern "C" struct SpawnCoords {
    float x, y, z;
};

extern "C" SpawnCoords spawnCoords = {
    17177.75, 24574.95, 5738.50
};



extern "C" DWORD_PTR returnInjectMouse = 0;
extern "C" DWORD_PTR returnInjectConsole = 0;
extern "C" DWORD_PTR returnInjectDamage = 0;
extern "C" DWORD_PTR returnInjectCoords = 0;
extern "C" DWORD_PTR lopBaseAddress = 0;
extern "C" int dmgReductionMulp = 0;

bool restartMusic = false;
bool playCustomMusic = false;
std::wstring soundTrackPath = L"";
float volume = 50;
//HSTREAM currentStream = 0;

DWORD_PTR dxgiBaseAddress = 0;

int spawnBoss = 0x2D;
int resetRush = 0x24;
int reloadConfig = 0x23;
bool bassInitialized = false;

void NopMemory(void* address, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(address, 0x90, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}

//LOP HOOK - DISABLE MOUSE
void  __attribute__((naked))InjectMouse() {

    __asm__ volatile(".intel_syntax noprefix;"
        "mov rax,00;"
        "jmp qword ptr [rip + returnInjectMouse];"
        /*"setne cl;"
        "or al, cl;"
        "mov al,00;"
        "jmp qword ptr [rip + returnInjectMouse];"*/



        );
}

//LOP HOOK - HIDE CONSOLE
void  __attribute__((naked))InjectConsole() {

    __asm__ volatile(".intel_syntax noprefix;"






        );
}

//LOP HOOK - INJECT DAMAGE
void  __attribute__((naked))InjectDamage() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "cmp r15b, 0x02;"
        "jne dmgMulpCheck;"
        "mov ecx, 0xFFFFFF9C;"
        "cmp eax, ecx;"
        "cmovle eax, ecx;"


        "dmgMulpCheck:"
        "cmp word ptr [rdi+0x12C],0x12;"
        "jne applyDmgMulp;"

        "jmp injectDamageExit;"


        "applyDmgMulp:"
        "cmp word ptr [rdi+0xCFC],0x00;"
        "jne injectDamageExit;"
        "cmp word ptr [rdi+0x12C],0x00;"
        "jne injectDamageExit;"

        //"xor rax,rax;"//JUST TO BE SAFE
        //"movzx rax, word ptr [rdi+0x0C];"
        //"test rax,rax;"
        //"jz injectDamageExit;"
        //"xorps xmm12,xmm12;"
        //"cvtsi2ss xmm12,rax;"
        //"movss xmm13,xmm12;"
        //"movss xmm15, [rip + dmgReductionMulp];"
        //"mulss xmm13,xmm15;"
        //"comiss xmm13,xmm12;"
        //"ja injectDamageExit;"
        //"subss xmm12,xmm13;"
        //"cvtss2si rax,xmm12;"
        //"sub [rdi+0x0C],rax;"
        //"shr rax, 1;"
        "xor rax,rax;"
        "movzx rax, word ptr [rip + dmgReductionMulp];"
        "sub [rdi+0x0C], rax;"
        "pop rax;"

        "jmp qword ptr [rip + returnInjectDamage];"



        "injectDamageExit:"
        "pop rax;"
        "mov[rdi + 0x0C], eax;"
        "jmp qword ptr [rip + returnInjectDamage];"





        );
}

//LOP HOOK - INJECT SPAWN COORDS
void  __attribute__((naked))InjectCoords() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rcx;"
        "xorps xmm7,xmm7;"

        "mov rcx, qword ptr [rip + lopBaseAddress];"
        "movaps xmm8, [rip + spawnCoords];"

        "comiss xmm7,xmm8;"
        "je setCoords;"

        //"movaps [rax+0x10], xmm8;"
        "movaps [rip + spawnCoords], xmm7;"

        "test rax, rax;"
        "je loadAddress;"

        "add rax, 0x000001B0;"
        "jmp setCoords;"

        "loadAddress:"
        "lea rax, [rbx + 0x71330C0];"

        "setCoords:"
        "pop rcx;"
        //"movups xmm8, [rax + 0x10];"
        "jmp qword ptr [rip + returnInjectCoords];"






        );
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


    std::wstring iniPath = std::wstring(exePath) + L"\\mods\\bossrush.ini";

    CSimpleIniW ini;
    ini.SetUnicode();

    SI_Error rc = ini.LoadFile(iniPath.c_str());
    if (rc < 0) {
        MessageBox(NULL, L"Can't load 'config.ini'", L"ERROR", NULL);
        return;
    }
    dmgReductionMulp = ini.GetDoubleValue(L"GENERAL", L"ReduceDamage", 500);
    playCustomMusic = ini.GetBoolValue(L"GENERAL", L"PlayCustomMusic", false);
    soundTrackPath = ini.GetValue(L"GENERAL", L"CustomMusicPath");
    volume = ini.GetDoubleValue(L"GENERAL", L"Volume", 50);
    spawnBoss = ini.GetDoubleValue(L"GENERAL", L"SpawnBoss", 0x2D);
    resetRush = ini.GetDoubleValue(L"GENERAL", L"resetRush", 0x24);
    reloadConfig = ini.GetDoubleValue(L"GENERAL", L"ReloadConfig", 0x23);

}

HookInfo hooks[] = {
    {0x407471C, 15, InjectMouse, "InjectMouse", &returnInjectMouse},
    //{0x1AC1D60, 15, InjectDamage, "InjectDamage", &returnInjectDamage},
    {0x1B9FEB3, 25, InjectCoords, "InjectCoords", &returnInjectCoords}




};

bool Hook(void* hookAddress, void* myFunc, int len) {

    if (len < 14) {
        return false;
    }

    DWORD oldProtect;
    VirtualProtect(hookAddress, len, PAGE_EXECUTE_READWRITE, &oldProtect);


    *(BYTE*)hookAddress = 0xFF;
    *((BYTE*)hookAddress + 1) = 0x25;
    *(DWORD*)((BYTE*)hookAddress + 2) = 0;
    *(DWORD_PTR*)((BYTE*)hookAddress + 6) = (DWORD_PTR)myFunc;


    VirtualProtect(hookAddress, len, oldProtect, &oldProtect);




    return true;
}




void ApplyHooks(HookInfo* hooks, int count, DWORD_PTR baseAddress) {
    for (int i = 0; i < count; i++) {
        DWORD_PTR hookAddress = baseAddress + hooks[i].offset;
        if (hooks[i].returnAddress) {
            *(hooks[i].returnAddress) = hookAddress + hooks[i].length;
        }
        if (!Hook((void*)hookAddress, hooks[i].hookFunction, hooks[i].length)) {
            std::stringstream ss;
            ss << "Failed to hook: " << hooks[i].hookName << " at address: 0x" << std::hex << hookAddress;
            //MessageBoxA(NULL, ss.str().c_str(), "Hook Error", MB_OK | MB_ICONERROR);
        }
    }
}

std::vector<BossInfo> bosses = {
    {L"CH01_Puppet_Fguide_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    //DONKEY
   {L"CH02_Stalker_MadStalker_00", 17177.75, 24574.95, 5738.50, 104.56, false},


    {L"CH02_Puppet_Judge_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    //STALKER SURVIVOR
    {L"CH03_Stalker_SurvivorStalker_00", 17177.75, 24574.95, 5738.50, 104.56, false},


    {L"CH03_Puppet_FireEater_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
    {L"CH04_Carcass_FallenArchBishop_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
    {L"CH04_Carcass_FallenArchBishop_Boss_01", 17177.75, 24574.95, 5738.50, 104.56, false},

    // BLACK RABBIT
    {L"CH05_Stalker_BRabbit_StrongMale_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    //WHITE LADY
    {L"CH06_Stalker_WhiteStalker_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    //CLOWN
    {L"CH06_Puppet_Clown_Seed_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    {L"CH06_Puppet_PuppetKing_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
    {L"CH06_Puppet_PuppetKingP3_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},

    //VICTOR
     {L"CH07_Reborner_Victor_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
     {L"CH07_Reborner_Victor_Boss_01", 17177.75, 24574.95, 5738.50, 104.56, false},

     //WEASEL
      {L"CH09_Stalker_Weasel_00", 17177.75, 24574.95, 5738.50, 104.56, false},

      //SWAMP
      {L"CH08_Carcass_GreenHunter_Main_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
      {L"CH08_Carcass_GreenHunter_Fusion_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},

      //ILLUSION
      {L"CH09_Reborner_Illusion_Seed_00", 17177.75, 24574.95, 5738.50, 104.56, false},

      //CORRUPTED PUP
      {L"CH09_Carcass_GraveKeeper_Seed_00", 17177.75, 24574.95, 5738.50, 104.56, false},


      // BLACK RABBIT
      {L"CH11_Stalker_BRabbit_StrongMale_Boss_01", 17177.75, 24574.95, 5738.50, 104.56, false},

      //STALKER CAT
     {L"CH12_Stalker_Cat_00", 17177.75, 24574.95, 5738.50, 104.56, false},


      {L"CH12_Reborner_Raxasia_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
      {L"CH12_Reborner_Raxasia_Boss_01", 17177.75, 24574.95, 5738.50, 104.56, false},

      //STALKER RED FOX
      {L"CH13_Stalker_Fox_00", 17177.75, 24574.95, 5738.50, 104.56, false},

      {L"CH13_Reborner_Simon_Boss_P1", 17177.75, 24574.95, 5738.50, 104.56, false},
      {L"CH13_Reborner_Simon_Boss_P2", 17177.75, 24574.95, 5738.50, 104.56, false},
      {L"CH13_Puppet_1stPinoccio_Boss_00", 17177.75, 24574.95, 5738.50, 104.56, false},
      {L"CH13_Puppet_1stPinoccio_Boss_P2_00", 17177.75, 24574.95, 5738.50, 104.56, false},
};


size_t currentIndex = 0;

void CopyToClipboard(const std::wstring& text) {
    const size_t len = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), text.c_str(), len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
}


void WriteMemory(void* address, const void* buffer, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(address, buffer, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}


void ShowConsole(void* consoleVisibilityAddress) {
    int showConsoleValue = 0x00047CE1;
    WriteMemory(consoleVisibilityAddress, &showConsoleValue, sizeof(showConsoleValue));
}


void HideConsole(void* consoleVisibilityAddress) {
    int hideConsoleValue = 0x00000000;
    WriteMemory(consoleVisibilityAddress, &hideConsoleValue, sizeof(hideConsoleValue));
}


void SimulatePaste() {
    INPUT input[4] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_CONTROL;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = 'V';
    input[2].type = INPUT_KEYBOARD;
    input[2].ki.wVk = 'V';
    input[2].ki.dwFlags = KEYEVENTF_KEYUP;
    input[3].type = INPUT_KEYBOARD;
    input[3].ki.wVk = VK_CONTROL;
    input[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, input, sizeof(INPUT));
}

// Function to simulate pressing Enter
void SimulateEnterKey() {
    INPUT input[2] = {};
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_RETURN;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_RETURN;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
}

void SpawnBlackRabbitGroup(const BlackRabbit& group, void* consoleVisibilityAddress) {
    ShowConsole(consoleVisibilityAddress);

    for (const auto& member : group.members) {
        std::wstring command = L"SpawnNPC " + member.name + L" 1";
        ShowConsole(consoleVisibilityAddress);
        Sleep(200);
        CopyToClipboard(command);
        Sleep(200);
        SimulatePaste();
        Sleep(200);
        SimulateEnterKey();
        Sleep(200);
        spawnCoords.x = member.x;
        spawnCoords.y = member.y;
        spawnCoords.z = member.z;
    }

    HideConsole(consoleVisibilityAddress);
    spawnCoords.x = 17177.75;
    spawnCoords.y = 24574.95;
    spawnCoords.z = 5738.50;
}

DWORD WINAPI MainThread(LPVOID param) {
    Sleep(8000);

    dxgiBaseAddress = (DWORD_PTR)GetModuleHandle(L"sunbeam.dll");
    lopBaseAddress = (DWORD_PTR)GetModuleHandle(L"LOP-Win64-Shipping.exe");

    /*bool bassInitialized = InitializeBass();*/

    if (dxgiBaseAddress == 0 || lopBaseAddress == 0) {
        MessageBoxA(NULL, "Failed to get base address of modules", "ERROR", MB_OK);
        return 0;
    }

    DWORD_PTR consoleOffset = 0x352E8;
    DWORD_PTR consoleVisibilityOffset = 0xD8;
    void* consoleBaseAddress = *(void**)(dxgiBaseAddress + consoleOffset);
    void* consoleVisibilityAddress = (BYTE*)consoleBaseAddress + consoleVisibilityOffset;

    if (!consoleBaseAddress || !consoleVisibilityAddress) {
        MessageBoxA(NULL, "Failed to resolve console addresses", "ERROR", MB_OK);
        return 0;
    }

    int hookCount = sizeof(hooks) / sizeof(HookInfo);
    ApplyHooks(hooks, hookCount, lopBaseAddress);
    DWORD_PTR renderConsoleAddres = lopBaseAddress + 0x4073060;
    NopMemory((void*)renderConsoleAddres, 6);
    LoadConfig();
    currentIndex = 0;

    while (true) {
        if (GetAsyncKeyState(reloadConfig) & 0x8000) {
            LoadConfig();
        }
        if (GetAsyncKeyState(resetRush) & 0x8000) {
            currentIndex = 0;
        }
        if (GetAsyncKeyState(spawnBoss) & 0x8000) {
            BossInfo& boss = bosses[currentIndex];

            if (boss.name == L"Stalker_BRabbit_StrongMale_Boss_00") {

                HideConsole(consoleVisibilityAddress);
                SpawnBlackRabbitGroup(blackRabbit1, consoleVisibilityAddress);
                currentIndex++;
            }
            else if (boss.name == L"Stalker_BRabbit_StrongMale_Boss_01") {

                HideConsole(consoleVisibilityAddress);
                SpawnBlackRabbitGroup(blackRabbit2, consoleVisibilityAddress);
                currentIndex++;
            }
            else {
                // Regular single boss spawn
                std::wstring command = L"SpawnNPC " + boss.name + L" 1";
                CopyToClipboard(command);
                ShowConsole(consoleVisibilityAddress);
                Sleep(50);
                SimulatePaste();
                Sleep(50);
                SimulateEnterKey();
                Sleep(50);
                HideConsole(consoleVisibilityAddress);
                spawnCoords.x = boss.x;
                spawnCoords.y = boss.y;
                spawnCoords.z = boss.z;




                currentIndex++;
            }


            if (currentIndex >= bosses.size()) currentIndex = 0;
        }
        /*if (currentIndex <= 1 && playCustomMusic) {
            if (!bassInitialized) {
                bassInitialized = InitializeBass();
            }
            //MessageBoxW(NULL, soundTrackPath.c_str(), L"Sound Track Path", MB_OK);
            if (!PlayWavFile(soundTrackPath.c_str(), volume, false)) {
                //MessageBoxW(NULL, L"Failed to play the sound track.", L"Error", MB_OK);
            }

        }*/
        Sleep(100);
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


//bool InitializeBass() {
//
//    if (!BASS_Init(-1, 44100, 0, 0, nullptr)) {
//        DWORD errorCode = BASS_ErrorGetCode();
//        std::string errorMsg = "Failed to initialize BASS: Error Code " + std::to_string(errorCode);
//        //MessageBoxA(nullptr, errorMsg.c_str(), "Error", MB_ICONERROR);
//        return false;
//    }
//
//    //MessageBoxA(nullptr, "BASS Initialized", "Debug", MB_OK);
//    return true;
//
//}

//bool PlayWavFile(const wchar_t* filePath, float volume, bool waitForSound) {
//    if (volume < 0.0f) {
//        volume = 25.00f;
//    }
//
//    // Stop the currently playing stream if it exists
//    if (currentStream) {
//        BASS_ChannelStop(currentStream);
//        BASS_StreamFree(currentStream); // Free the stream to release memory
//    }
//
//    // Try to create a stream for the specified .wav file
//    currentStream = BASS_StreamCreateFile(FALSE, filePath, 0, 0, BASS_UNICODE);
//
//    if (!currentStream) {
//        DWORD errorCode = BASS_ErrorGetCode();
//        std::wstring errorMsg = L"Failed to load file: Error Code " + std::to_wstring(errorCode);
//        MessageBoxW(nullptr, errorMsg.c_str(), L"Error", MB_ICONERROR);
//        return false;
//    }
//
//    // Set the volume for the stream (0.0 to 1.0)
//    if (!BASS_ChannelSetAttribute(currentStream, BASS_ATTRIB_VOL, volume)) {
//        DWORD errorCode = BASS_ErrorGetCode();
//        std::wstring errorMsg = L"Failed to set volume: Error Code " + std::to_wstring(errorCode);
//        MessageBoxW(nullptr, errorMsg.c_str(), L"Error", MB_ICONERROR);
//    }
//
//    // Play the loaded .wav file
//    if (!BASS_ChannelPlay(currentStream, FALSE)) {
//        DWORD errorCode = BASS_ErrorGetCode();
//        std::wstring errorMsg = L"Failed to play sound: Error Code " + std::to_wstring(errorCode);
//        MessageBoxW(nullptr, errorMsg.c_str(), L"Error", MB_ICONERROR);
//        BASS_StreamFree(currentStream); // Clean up stream resources
//        currentStream = 0;
//        return false;
//    }
//
//    if (waitForSound) {
//        // Wait while the sound is playing
//        while (BASS_ChannelIsActive(currentStream) == BASS_ACTIVE_PLAYING) {
//            Sleep(10); // Sleep to reduce CPU usage
//        }
//    }
//
//    return true;
//}







































































