#pragma once
#include <cstdint>

extern DWORD_PTR lopBaseAddress;

extern "C" uintptr_t pinoBaseAddress;

extern "C" uintptr_t returnInjectPinoBaseAddress;

extern "C" uint8_t currentChapter;

//GET PLAYER BASE ADDRESS
extern "C" uintptr_t returnInjectPinoBaseAddress;

//CHAPTER 1
extern "C" const unsigned char LD_Outer_Station[];
extern "C" size_t LD_Outer_Station_Size;

//CHAPTER 2
extern "C" const unsigned char LV_Inner_UpperStreet[];
extern "C" size_t LV_Inner_UpperStreet_Size;

//CHAPTER 3
extern "C" const unsigned char LV_Inner_Factory[];
extern "C" size_t LV_Inner_Factory_Size;

//CHAPTER 4
extern "C" const unsigned char LV_Inner_Cathedral[];
extern "C" size_t LV_Inner_Cathedral_Size;

//CHAPTER 5
extern "C" const unsigned char LV_Krat_Old_Town[];
extern "C" size_t LV_Krat_Old_Town_Size;

//CHAPTER 6
extern "C" const unsigned char LV_Krat_EastEndWard[];
extern "C" size_t LV_Krat_EastEndWard_Size;

//CHAPTER 7
extern "C" const unsigned char LV_Outer_Exhibition[];
extern "C" size_t LV_Outer_Exhibition_Size;

//CHAPTER 8
extern "C" const unsigned char LV_Outer_Grave[];
extern "C" size_t LV_Outer_Grave_Size;

//CHAPTER 9
extern "C" const unsigned char LV_Outer_CentralStatinB[];
extern "C" size_t LV_Outer_CentralStatinB_Size;

//CHAPTER 11
extern "C" const unsigned char LV_Outer_Underdark_A[];
extern "C" size_t LV_Outer_Underdark_A_Size;


//CHAPTER 12
extern "C" const unsigned char LV_Monastery_A[];
extern "C" size_t LV_Monastery_A_Size;

//CHAPTER 13
extern "C" const unsigned char LV_Monastery_B[];
extern "C" size_t LV_Monastery_B_Size;

//FETCH ACTIVE LEVEL (Used for scaling purposes)
extern "C" uintptr_t returnInjectLvlHelper;

//ENEMY HP SCALING
extern "C" uintptr_t returnInjectHPScaler;
extern "C" uintptr_t injectHPScaler0875;
extern "C" uintptr_t injectHPScaler;
//POP rax will restore original value anyway so make it void and save original value into variable and make that final regardless
extern "C" void(*HPScalerFunction)(int, int*);
extern "C" int hpScaledValue;

extern const int chapter_one_hp_data[];
extern const size_t chapter_one_hp_data_size;

extern const int chapter_two_hp_data[];
extern const size_t chapter_two_hp_data_size;

extern const int chapter_three_hp_data[];
extern const size_t chapter_three_hp_data_size;

extern const int chapter_four_hp_data[];
extern const size_t chapter_four_hp_data_size;

extern const int chapter_five_hp_data[];
extern const size_t chapter_five_hp_data_size;

extern const int chapter_six_hp_data[];
extern const size_t chapter_six_hp_data_size;

extern const int chapter_seven_hp_data[];
extern const size_t chapter_seven_hp_data_size;

extern const int chapter_eight_hp_data[];
extern const size_t chapter_eight_hp_data_size;

extern const int chapter_nine_hp_data[];
extern const size_t  chapter_nine_hp_data_size;

extern const int chapter_eleven_hp_data[];
extern const size_t  chapter_eleven_hp_data_size;

extern const int chapter_twelve_hp_data[];
extern const size_t  chapter_twelve_hp_data_size;

extern const int chapter_thirteen_hp_data[];
extern const size_t chapter_thirteen_hp_data_size;

extern const int boss_hp_data[];
extern const size_t boss_hp_data_size;

extern const int stalker_hp_data[];
extern const size_t stalker_hp_data_size;

extern const int helpmate_hp_data[];
extern const size_t helpmate_hp_data_size;

extern const int miniboss_hp_data[];
extern const size_t miniboss_hp_data_size;

extern const int miniboss_hp_data_assign[];
extern const size_t miniboss_hp_data_assign_size;


extern const int quest_hp_data[];
extern const size_t quest_hp_data_size;

extern const int hotel_puppet_training_hp_data[];
extern const size_t hotel_puppet_training_hp_data_size;

extern const int stalker_rabbit_hp_data[];
extern const size_t stalker_rabbit_hp_data_size;