#pragma once
#include <vector>

void Test(int HP, int* hpScaledValue);
bool HPMatch(const int* hpArray, size_t size, int hpToMatch);
void AssignHPoolVector(const int* hpArray, size_t size, std::vector<int>& vec);
	
