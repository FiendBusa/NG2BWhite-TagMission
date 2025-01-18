#include "pch.h"
#include "functions.h"
#include <random>
#include <cstddef>
#include "globals.h"
#include <vector>
#include <iterator>
#include <random>


std::random_device rd;
std::mt19937 gen(rd());

void Test(int HP, int* hpScaledValue)
{
	int newHPValue = HP;
	std::vector<int> enemyHPool;

	if (HPMatch(boss_hp_data, boss_hp_data_size, newHPValue)) { *hpScaledValue = HP; return; }
	if (HPMatch(stalker_rabbit_hp_data, stalker_rabbit_hp_data_size, newHPValue)) { *hpScaledValue = HP; return; }
	if (HPMatch(hotel_puppet_training_hp_data, hotel_puppet_training_hp_data_size, newHPValue)) { *hpScaledValue = HP; return; }
	if (HPMatch(quest_hp_data, quest_hp_data_size, newHPValue)) { *hpScaledValue = HP; return; }
	if (HPMatch(helpmate_hp_data, helpmate_hp_data_size, newHPValue)) { *hpScaledValue = HP; return; }



	switch (currentChapter){
	case 1:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[0]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[0]; return;
		}
		AssignHPoolVector(chapter_one_hp_data, chapter_one_hp_data_size, enemyHPool);
		break;
	case 2:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[1]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[0]; return;
		}
		AssignHPoolVector(chapter_two_hp_data, chapter_two_hp_data_size, enemyHPool);
		break;
	case 3:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[2]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[2]; return;
		}
		AssignHPoolVector(chapter_three_hp_data, chapter_three_hp_data_size, enemyHPool);
		break;
	case 4:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[3]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[2]; return;
		}
		AssignHPoolVector(chapter_four_hp_data, chapter_four_hp_data_size, enemyHPool);
		break;
	case 5:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[3]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[2]; return;
		}
		AssignHPoolVector(chapter_five_hp_data, chapter_five_hp_data_size, enemyHPool);
		break;
	case 6:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[4]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[2]; return;
		}
		AssignHPoolVector(chapter_six_hp_data, chapter_six_hp_data_size, enemyHPool);
		break;
	case 7:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[4]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[3]; return;
		}
		AssignHPoolVector(chapter_seven_hp_data, chapter_seven_hp_data_size, enemyHPool);
		break;
	case 8:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[4]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[3]; return;
		}
		AssignHPoolVector(chapter_eight_hp_data, chapter_eight_hp_data_size, enemyHPool);
		break;
	case 9:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[5]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[3]; return;
		}
		AssignHPoolVector(chapter_nine_hp_data, chapter_nine_hp_data_size, enemyHPool);
		break;
	case 11:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[5]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[3]; return;
		}
		AssignHPoolVector(chapter_eleven_hp_data, chapter_eleven_hp_data_size, enemyHPool);
		break;
	case 12:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[6]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[4]; return; }
		AssignHPoolVector(chapter_twelve_hp_data, chapter_twelve_hp_data_size, enemyHPool);
		break;
	case 13:
		if (HPMatch(stalker_hp_data, stalker_hp_data_size, newHPValue)) { *hpScaledValue = stalker_hp_data[7]; return; }
		if (HPMatch(miniboss_hp_data, miniboss_hp_data_size, newHPValue)) { *hpScaledValue = miniboss_hp_data_assign[4]; return; }
		AssignHPoolVector(chapter_thirteen_hp_data, chapter_thirteen_hp_data_size, enemyHPool);
		break;
	

	}
	if (enemyHPool.empty()) { *hpScaledValue = newHPValue; return; }

	std::uniform_int_distribution<int> dist(0, enemyHPool.size() - 1);
	*hpScaledValue = enemyHPool[dist(gen)];
	
}
bool HPMatch(const int* hpArray, size_t size, int hpToMatch) {

	for (int i = 0; i < size; i++) {
		if (hpArray[i] == hpToMatch) { return true; }
	}
	return false;
}
void AssignHPoolVector(const int* hpArray, size_t size, std::vector<int>& vec) {
	vec.clear();
	vec.reserve(size);
	std::copy(hpArray, hpArray + size, std::back_inserter(vec));
}