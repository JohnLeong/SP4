#include "Profile.h"
#include "../LuaScript.h"

string CProfile::propertyName[CProfile::NUM_Properties] = {"HighestLevelUnlocked"};


CProfile::CProfile(int theHighestLevelUnlocked)
{
	mHighestLevelUnlocked = theHighestLevelUnlocked;
}

CProfile::~CProfile(void)
{

}

void CProfile::Update()
{
}

int CProfile::GetHighestLevelUnlocked()
{
	return mHighestLevelUnlocked;
}

void CProfile::Save(fstream& file, int id)
{
	file << propertyName[HighestLevelUnlocked] << id << " = "  << mHighestLevelUnlocked  << "\n";
}

void CProfile::Reset(fstream& file, int id)
{
	mHighestLevelUnlocked = 1;
	file << propertyName[HighestLevelUnlocked] << id << " = " << mHighestLevelUnlocked << "\n";
}

