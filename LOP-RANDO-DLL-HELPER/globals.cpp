#include "pch.h"
#include "globals.h"
#include "functions.h"

DWORD_PTR lopBaseAddress = 0;

uintptr_t pinoBaseAddress = 0;

uint8_t currentChapter = 0;

uintptr_t returnInjectPinoBaseAddress = 0;


const unsigned char LD_Outer_Station[] = {
    0x4C, 0x44, 0x5F, 0x4F, 0x75, 0x74, 0x65, 0x72, 0x5F, 0x53, 0x74, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x5F,0x44,0x53,0x4E //0x5F, 0x44, 0x53, 0x4E
};

size_t LD_Outer_Station_Size = sizeof(LD_Outer_Station) / sizeof(LD_Outer_Station[0]);

const unsigned char LV_Inner_UpperStreet[] = {
    //0x4C, 0x56, 0x5F, 0x49, 0x6E, 0x6E, 0x65, 0x72, 0x5F, 0x55, 0x70, 0x70, 0x65, 0x72, 0x53, 0x74, 0x72, 0x65, 0x65, 0x74
    0x4C, 0x56, 0x5F, 0x49, 0x6E, 0x6E, 0x65, 0x72, 0x5F, 0x55, 0x70, 0x70, 0x65, 0x72, 0x53, 0x74, 0x72, 0x65, 0x65, 0x74, 0x5F,0x44,0x53,0x4E

};


size_t LV_Inner_UpperStreet_Size = sizeof(LV_Inner_UpperStreet) / sizeof(LV_Inner_UpperStreet[0]);

const unsigned char LV_Inner_Factory[] = {
    0x4C, 0x56, 0x5F, 0x49, 0x6E, 0x6E, 0x65, 0x72, 0x5F, 0x46, 0x61, 0x63, 0x74, 0x6F, 0x72, 0x79,0x5F,0x44,0x53,0x4E
};

size_t LV_Inner_Factory_Size = sizeof(LV_Inner_Factory) / sizeof(LV_Inner_Factory[0]);

const unsigned char LV_Inner_Cathedral[] = {
    //0x4C, 0x56, 0x5F, 0x49, 0x6E, 0x6E, 0x65, 0x72, 0x5F, 0x43, 0x61, 0x74, 0x68, 0x65, 0x64, 0x72, 0x61, 0x6C
    0x4C, 0x56, 0x5F, 0x49, 0x6E, 0x6E, 0x65, 0x72, 0x5F, 0x43, 0x61, 0x74, 0x68, 0x65, 0x64, 0x72, 0x61, 0x6C,0x5F,0x44,0x53,0x4E
};

size_t LV_Inner_Cathedral_Size = sizeof(LV_Inner_Cathedral) / sizeof(LV_Inner_Cathedral[0]);

const unsigned char LV_Krat_Old_Town[] = {
    //0x4C, 0x56, 0x5F, 0x4B, 0x72, 0x61, 0x74, 0x5F, 0x4F, 0x6C, 0x64, 0x5F, 0x54, 0x6F, 0x77, 0x6E
    0x4C, 0x56, 0x5F, 0x4B, 0x72, 0x61, 0x74, 0x5F, 0x4F, 0x6C, 0x64, 0x5F, 0x54, 0x6F, 0x77, 0x6E, 0x5F,0x44,0x53,0x4E

};

size_t LV_Krat_Old_Town_Size = sizeof(LV_Krat_Old_Town) / sizeof(LV_Krat_Old_Town[0]);

const unsigned char LV_Krat_EastEndWard[] = {
    0x4C, 0x56, 0x5F, 0x4B, 0x72, 0x61, 0x74, 0x5F, 0x45, 0x61, 0x73, 0x74, 0x45, 0x6E, 0x64, 0x57, 0x61, 0x72, 0x64, 0x5F,0x44,0x53,0x4E
};

size_t LV_Krat_EastEndWard_Size = sizeof(LV_Krat_EastEndWard) / sizeof(LV_Krat_EastEndWard[0]);

const unsigned char LV_Outer_Exhibition[] = {
    0x4C, 0x56, 0x5F, 0x4F, 0x75, 0x74, 0x65, 0x72, 0x5F, 0x45, 0x78, 0x68, 0x69, 0x62, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x5F,0x44,0x53,0x4E
};

size_t LV_Outer_Exhibition_Size = sizeof(LV_Outer_Exhibition) / sizeof(LV_Outer_Exhibition[0]);

const unsigned char LV_Outer_Grave[] = {
    0x4C, 0x56, 0x5F, 0x4F, 0x75, 0x74, 0x65, 0x72, 0x5F, 0x47, 0x72, 0x61, 0x76, 0x65, 0x5F,0x44,0x53,0x4E
};

size_t LV_Outer_Grave_Size = sizeof(LV_Outer_Grave) / sizeof(LV_Outer_Grave[0]);

const unsigned char LV_Outer_CentralStatinB[] = {
    0x4C, 0x56, 0x5F, 0x4F, 0x75, 0x74, 0x65, 0x72, 0x5F, 0x43, 0x65, 0x6E, 0x74, 0x72, 0x61, 0x6C, 0x53, 0x74, 0x61, 0x74, 0x69, 0x6E, 0x42, 0x5F,0x44,0x53,0x4E
};

size_t LV_Outer_CentralStatinB_Size = sizeof(LV_Outer_CentralStatinB) / sizeof(LV_Outer_CentralStatinB[0]);

const unsigned char LV_Outer_Underdark_A[] = {
    0x4C, 0x56, 0x5F, 0x4F, 0x75, 0x74, 0x65, 0x72, 0x5F, 0x55, 0x6E, 0x64, 0x65, 0x72, 0x64, 0x61, 0x72, 0x6B, 0x5F, 0x44, 0x53, 0x4E
};

size_t LV_Outer_Underdark_A_Size = sizeof(LV_Outer_Underdark_A) / sizeof(LV_Outer_Underdark_A[0]);


const unsigned char LV_Monastery_A[] = {
    0x4C, 0x56, 0x5F, 0x4D, 0x6F, 0x6E, 0x61, 0x73, 0x74, 0x65, 0x72, 0x79, 0x5F, 0x41, 0x5F,0x44,0x53,0x4E //0x5F, 0x44, 0x53, 0x4E
};

size_t LV_Monastery_A_Size = sizeof(LV_Monastery_A) / sizeof(LV_Monastery_A[0]);

const unsigned char LV_Monastery_B[] = {
    0x4C, 0x56, 0x5F, 0x4D, 0x6F, 0x6E, 0x61, 0x73, 0x74, 0x65, 0x72, 0x79, 0x5F, 0x42, 0x5F,0x44,0x53,0x4E
};

size_t LV_Monastery_B_Size = sizeof(LV_Monastery_B) / sizeof(LV_Monastery_B[0]);



uintptr_t returnInjectLvlHelper = 0;
uintptr_t returnInjectHPScaler = 0;

uintptr_t injectHPScaler0875 = 0x1AC0875;
void(*HPScalerFunction)(int, int*) = &Test;
int hpScaledValue = 0;


uintptr_t injectHPScaler = 0;

//REGULAR + 40% buff
const int boss_hp_data[] = {
    4400, //PARADE MASTER BOSS CH1
    6160,
    8710,//PUPPET JUDGE BOSS CH2
    11098,
    12194,
    8639,//FIRE EATER BOSS CH3
    12095,
    6995,//ARCHBISHOP CH3
    9793,
    7927,//ARCHBISHOP CH4
    2574,
    23965,
    8813,//CH5 STRONG MALE
    12338,
    12339,
    8474,//PuppetKING 00 CH6
    11863,
    11864,
    10557,//PuppetKINGP3 00 CH7
    14779,
    14780,
    23310, //Reborner Victor 00
    32634,
    25641, //Reborner Victor 01
    35897,
    35898,
    12115, //Green Hunter Boss 00
    16961,
    15144, //Green Hunter Boss 01
    21201,
    21202,
    14033, //Reborner Illusion Seed 00 CH9
    19604,
    19605,
    6174,
    14515, //Carcass Grave Keeper CH09
    20321,
    11317, //Strong Male Boss CH11
    15843,
    15844,
    17118, //Door Guardian CH12
    23605,
    23606,
    9137, //Raxasia 00
    12791,
    12792,
    13735, // Raxasia 01
    19229,
    13719, //Simon 00
    19206,
    19207,
    19166,//Simon 01
    26832,
    26833,
    11298,// 1st pinccio 00
    15817,
    15818,
    16947,// 1st pinccio P2
    23725,
    23726




};
const size_t boss_hp_data_size = sizeof(boss_hp_data) / sizeof(boss_hp_data[0]);

const int stalker_hp_data[] = {
    4696, // MAD DONKEY CH2
    6437, // SURVIVOR CH3
    6183, // Pilgrim CH4
    8942, // White CH6
    11346, //Weasel CH9
    12588, //Cat CH12
    12616 //Fox CH13


};
const size_t stalker_hp_data_size = sizeof(stalker_hp_data) / sizeof(stalker_hp_data[0]);

const int helpmate_hp_data[] = {
    2980,//CH2
    3144,//CH3
    4436,//CH4
    7783,//CH5
    5231,//CH6
    4901,//CH7
    5808,//CH8
    8083,//CH11
    7286,//CH12
    5242//CH13
};
const size_t helpmate_hp_data_size = sizeof(helpmate_hp_data) / sizeof(helpmate_hp_data[0]);

const int miniboss_hp_data[] = {
    9871, //CH3 Puppet Future
    11023,//CH6 PUPPET CLOWN SEED 00
    7649,//CH7 Puppet Clown Proto Named 00   
    11952,//CH08 Puppet Tomorrow Electric  
    7012,//CH08 puppet clown proto
    8913
    //6480,//CH7 Puppet Butcher Named 00
};


const int miniboss_hp_data_assign[] = {
    1584,//CH1
    2980,//CH2-CH4
    9871,//CH5-CH6
    11023,//CH7-CH11
    11952//CH12-CH13
};
const size_t miniboss_hp_data_assign_size = sizeof(miniboss_hp_data_assign) / sizeof(miniboss_hp_data_assign);

const size_t miniboss_hp_data_size = sizeof(miniboss_hp_data) / sizeof(miniboss_hp_data[0]);

const int quest_hp_data[] = {
     15305, // CH05 QST FOX & CH05 QST Cat

};
const size_t quest_hp_data_size = sizeof(quest_hp_data) / sizeof(quest_hp_data[0]);

const int hotel_puppet_training_hp_data[] =
{
    5269,
    10373
};
const size_t hotel_puppet_training_hp_data_size = sizeof(hotel_puppet_training_hp_data) / sizeof(hotel_puppet_training_hp_data[0]);


const int stalker_rabbit_hp_data[] = {
    2233,//CH5 Female
    2703,//CH5 Normal & Tall 
    5049, //CH11 Female
    6171, //CH11 Normal
    6384, //CH11 Tall
};

const size_t stalker_rabbit_hp_data_size = sizeof(stalker_rabbit_hp_data) / sizeof(stalker_rabbit_hp_data[0]);

const int chapter_one_hp_data[] = { 264, 277, 300, 211,185 }; //1386 1584 800
const size_t chapter_one_hp_data_size = sizeof(chapter_one_hp_data) / sizeof(chapter_one_hp_data[0]);

const int chapter_two_hp_data[] = { 311, 249,233, 280, 218, 420 }; //2491, 1916, 2728
const size_t  chapter_two_hp_data_size = sizeof(chapter_two_hp_data) / sizeof(chapter_two_hp_data[0]);

const int chapter_three_hp_data[] = { 264, 603, 555, 339, 302, 362, 424 }; //4342 4442, 2978
const size_t  chapter_three_hp_data_size = sizeof(chapter_three_hp_data) / sizeof(chapter_three_hp_data[0]);

const int chapter_four_hp_data[] = { 402, 313, 447, 705, 380, 536, 503, 469 }; //5082, 2281, 4419, 805
const size_t  chapter_four_hp_data_size = sizeof(chapter_four_hp_data) / sizeof(chapter_four_hp_data[0]);

const int chapter_five_hp_data[] = { 619, 639, 673, 542, 581, 725, 525 }; //3183, 2984, 2602, 4739, 4784, 2862 273
const size_t  chapter_five_hp_data_size = sizeof(chapter_five_hp_data) / sizeof(chapter_five_hp_data[0]);

const int chapter_six_hp_data[] = { 742, 685, 771, 514, 457, 914, 930, 950, 628, 614, 642 }; //4356 3753 400 2136 1877 514
const size_t  chapter_six_hp_data_size = sizeof(chapter_six_hp_data) / sizeof(chapter_six_hp_data[0]);

const int chapter_seven_hp_data[] = { 779, 719, 810, 540, 480, 960, 976, 998, 659, 645, 674 }; //6480 5863 4510 3514 7406 6608
const size_t  chapter_seven_hp_data_size = sizeof(chapter_seven_hp_data) / sizeof(chapter_seven_hp_data[0]);

const int chapter_eight_hp_data[] = { 818, 755, 850, 767, 804, 1008, 1025, 1048, 692, 677, 708 };
const size_t  chapter_eight_hp_data_size = sizeof(chapter_eight_hp_data) / sizeof(chapter_eight_hp_data[0]);

const int chapter_nine_hp_data[] = { 859, 793, 892, 795, 829, 1058, 1076, 1100, 727, 711, 743 };
const size_t  chapter_nine_hp_data_size = sizeof(chapter_nine_hp_data) / sizeof(chapter_nine_hp_data[0]);

const int chapter_eleven_hp_data[] = { 988, 912, 1026, 1217, 1237, 1265, 836, 818, 854 };
const size_t  chapter_eleven_hp_data_size = sizeof(chapter_eleven_hp_data) / sizeof(chapter_eleven_hp_data[0]);

const int chapter_twelve_hp_data[] = { 1136, 1049, 1180, 1400, 1423, 1455, 961, 941, 982 };
const size_t  chapter_twelve_hp_data_size = sizeof(chapter_twelve_hp_data) / sizeof(chapter_twelve_hp_data[0]);

const int chapter_thirteen_hp_data[] = { 1306, 1206, 1357, 1610, 1636, 1673, 1105, 1082, 1129 }; //678  774
const size_t  chapter_thirteen_hp_data_size = sizeof(chapter_thirteen_hp_data) / sizeof(chapter_thirteen_hp_data[0]);