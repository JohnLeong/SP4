#include "Profile.h"
#include "../LuaScript.h"

string CProfile::propertyName[CProfile::NUM_Properties] = { "Name", "HighestLevelUnlocked"};


CProfile::CProfile(string theName, int theHighestLevelUnlocked)
{
	mName = theName;
	mHighestLevelUnlocked = theHighestLevelUnlocked;
}

CProfile::~CProfile(void)
{

}

void CProfile::Update()
{
}

void CProfile::Save(fstream& file, int id)
{
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[HighestLevelUnlocked] << id << " = "  << mHighestLevelUnlocked  << "\n";
}
