#include "pch.h"
#include "globals.h"
#include "hook.h"
#include "functions.h"

void  __attribute__((naked))InjectPinoBaseAddress() {

    __asm__ volatile(".intel_syntax noprefix;"    
        //ORIGINAL
        "push rax;"
        "mov r15,[rcx+0x00000210];"
        "mov rax,r15;"
        "mov rax, qword ptr [rax+0xE0];"
        "test rax,rax;"
        "je exitPinoBaseAddress;"
        "mov rax, qword ptr [rax+0x28];"
        "mov [rip + pinoBaseAddress], rax;"
        "exitPinoBaseAddress:"
        "pop rax;"
        "xor r14d,r14d;"
        "mov rbx,rdx;"
        "mov rdi,rcx;"
        "jmp qword ptr [rip + returnInjectPinoBaseAddress];"
            




        );
}

void  __attribute__((naked))InjectLvlHelper() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "push rcx;"
        "push rdi;"
        "push rsi;"
        "mov rsi, r9;"
        "xor rcx,rcx;"

        //Maybe i should of just moved to two xmm registers lol but w.e
        //CHAPTER 1
        "lea rdi, qword ptr [rip+LD_Outer_Station];"
        "movzx rcx, byte ptr [rip+LD_Outer_Station_Size];"
        "repe cmpsb;"
        "je setChapter1;"

        //CHAPTER 2
        "lea rdi, qword ptr [rip+LV_Inner_UpperStreet];"
        "movzx rcx, byte ptr [rip+LV_Inner_UpperStreet_Size];"
        "repe cmpsb;"
        "je setChapter2;"

        //CHAPTER 3
        "lea rdi, qword ptr [rip+LV_Inner_Factory];"
        "movzx rcx, byte ptr [rip+LV_Inner_Factory_Size];"
        "repe cmpsb;"
        "je setChapter3;"


        //CHAPTER 5
        "lea rdi, qword ptr [rip+LV_Krat_Old_Town];"
        "movzx rcx, byte ptr [rip+LV_Krat_Old_Town_Size];"
        "repe cmpsb;"
        "je setChapter5;"

        //CHAPTER 6
        "lea rdi, qword ptr [rip+LV_Krat_EastEndWard];"
        "movzx rcx, byte ptr [rip+LV_Krat_EastEndWard_Size];"
        "repe cmpsb;"
        "je setChapter6;"

        //CHAPTER 7
        "lea rdi, qword ptr [rip+LV_Outer_Exhibition];"
        "movzx rcx, byte ptr [rip+LV_Outer_Exhibition_Size];"
        "repe cmpsb;"
        "je setChapter7;"

        //CHAPTER 9
        "lea rdi, qword ptr [rip+LV_Outer_CentralStatinB];"
        "movzx rcx, byte ptr [rip+LV_Outer_CentralStatinB_Size];"
        "repe cmpsb;"
        "je setChapter9;"

        //CHAPTER 11
        "lea rdi, qword ptr [rip+LV_Outer_Underdark_A];"
        "movzx rcx, byte ptr [rip+LV_Outer_Underdark_A_Size];"
        "repe cmpsb;"
        "je setChapter11;"

        //CHAPTER 12
        "lea rdi, qword ptr [rip+LV_Monastery_A];"
        "movzx rcx, byte ptr [rip+LV_Monastery_A_Size];"
        "repe cmpsb;"
        "je setChapter12;"

        //CHAPTER 13
        "lea rdi, qword ptr [rip+LV_Monastery_B];"
        "movzx rcx, byte ptr [rip+LV_Monastery_B_Size];"
        "repe cmpsb;"
        "je setChapter13;"

        //CHAPTER 4
        "lea rdi, qword ptr [rip+LV_Inner_Cathedral];"
        "movzx rcx, byte ptr [rip+LV_Inner_Cathedral_Size];"
        "repe cmpsb;"
        "je setChapter4;"

        //CHAPTER 8
        "lea rdi, qword ptr [rip+LV_Outer_Grave];"
        "movzx rcx, byte ptr [rip+LV_Outer_Grave_Size];"
        "repe cmpsb;"
        "je setChapter8;"

        "jmp exitHelper;"

        "setChapter1:"
        "mov byte ptr [rip + currentChapter], 0x01;"
        "jmp exitHelper;"

        "setChapter2:"
        "mov byte ptr [rip + currentChapter], 0x02;"
        "jmp exitHelper;"

        "setChapter3:"
        "mov byte ptr [rip + currentChapter], 0x03;"
        "jmp exitHelper;"

        "setChapter4:"
        "mov byte ptr [rip + currentChapter], 0x04;"
        "jmp exitHelper;"

        "setChapter5:"
        "mov byte ptr [rip + currentChapter], 0x05;"
        "jmp exitHelper;"

        "setChapter6:"
        "mov byte ptr [rip + currentChapter], 0x06;"
        "jmp exitHelper;"

        "setChapter7:"
        "mov byte ptr [rip + currentChapter], 0x07;"
        "jmp exitHelper;"

        "setChapter8:"
        "mov byte ptr [rip + currentChapter], 0x08;"
        "jmp exitHelper;"

        "setChapter9:"
        "mov byte ptr [rip + currentChapter], 0x09;"
        "jmp exitHelper;"

        "setChapter11:"
        "mov byte ptr [rip + currentChapter], 0x0B;"
        "jmp exitHelper;"

        "setChapter12:"
        "mov byte ptr [rip + currentChapter], 0x0C;"
        "jmp exitHelper;"

        "setChapter13:"
        "mov byte ptr [rip + currentChapter], 0x0D;"
        "jmp exitHelper;"



        "exitHelper:"
        "pop rsi;"
        "pop rdi;"
        "pop rcx;"
        "pop rax;"

        //ORIGINAL
        "movzx eax, byte ptr [r11+r9];"
        "movzx r8d, byte ptr [r9];"
        "lea r9, qword ptr [r9+0x01];"
        "cmp al,r8b;"
        "jmp qword ptr [rip + returnInjectLvlHelper];"


        );
}

void  __attribute__((naked))InjectHPScaler() {

    __asm__ volatile(".intel_syntax noprefix;"
        //ORIGINAL
        "mov rdi,[rsp+0x38];"
        "add eax,ebp;"

        "cmp rdx,0x15;"
        "je getPinoAddressNewGame;"
        
        "cmp qword ptr [rip + pinoBaseAddress],0x00;"
        "jz getPinoAddress;"

        "jmp hpScalerStart;"

        "getPinoAddressNewGame:"
        /*"cmp ax,0x11B;"
        "jne hpScalerStart;"*/
        "mov qword ptr [rip + pinoBaseAddress],r14;"
        "jmp cleanUpHPScaler;"

        "hpScalerStart:"
        "cmp r11,0x45;"
        "je cleanUpHPScaler;"
        
        //PRE CHECKS BEFORE CALL
        "cmp r10,0x01;"
        "jne cleanUpHPScaler;"

        "cmp qword ptr [rip + pinoBaseAddress],0x00;"
        "jz getPinoAddress;"

        //PINO CHECK
        "push rbx;"
        "mov rbx, qword ptr [rip + pinoBaseAddress];"
       
        "cmp r14,rbx;"
        "pop rbx;"
        "je cleanUpHPScaler;"
        
        "cmp r12,0x30;"
        "je cleanUpHPScaler;"      

        //Calling Internet HP Scaler Function      
        "push rbx;"
        "push rcx;"
        "push rdx;"

        "sub rsp,0x08;"

        "lea rdx, qword ptr [rip + hpScaledValue];"
        "mov rbx, qword ptr [rip + HPScalerFunction];"

        "mov rcx,rax;"
        "call rbx;"

        "add rsp,0x08;"
       
        
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
      

        "cmp eax, dword ptr [rip + hpScaledValue];"
        "je cleanUpHPScaler;"

        "mov eax, dword ptr [rip + hpScaledValue];"
        "mov dword ptr [r14+0x0C], eax;"

        "jmp cleanUpHPScaler;"

        "getPinoAddress:"
        "mov [rip + pinoBaseAddress], r14;"
        "jmp cleanUpHPScaler;"
     
        
        //ORIGINAL
        "cleanUpHPScaler:"
        "mov dword ptr [rip + hpScaledValue], 0x00;"
        "cmp ecx, 0x00002710;"
        "je jmp0875;"

        "jmp exitHPScaler;"


        "jmp0875:"
        "jmp qword ptr [rip + injectHPScaler0875];"

        "exitHPScaler:"
        "jmp qword ptr [rip + returnInjectHPScaler];"




        );
}




















/*void  __attribute__((naked))InjectHPScaler() {

    __asm__ volatile(".intel_syntax noprefix;"
        "mov [rsp+0x30],rsi;"
        "xor esi,esi;"
        "nop dword ptr [rax+0x00000000];"
        "cmp byte ptr [rbx+0x15],0x01;"
        "jne EBC;"

        "cmp byte ptr [rbx+0x18],sil;"
        "je EB1;"
        "mov [rbx+0x0C],esi;"
        "jmp EBC;"

        "mov [rbx+0x0C],eax;"
        "jmp qword ptr [rip + injectHPScalerCallAddress];"
        "mov [rbx+0x0C],eax;"
        "add rbx,0x30;"
        "cmp rbx,rdi;"
        "jne EA0;"

        "EBC:"
        "jmp qword ptr [rip + jmpEBC];"

        "EB1:"
        "jmp qword ptr [rip + jmpEB1];"

        "EA0:"
        "jmp qword ptr [rip + jmpEA0];"

        "jmp qword ptr [rip + returnInjectHPScaler];"




        );
}*/