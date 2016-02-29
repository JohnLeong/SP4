#include "Achievements.h"
#include "Properties.h"

string CAchievements::propertyName[CAchievements::NUM_Properties] = { "Name", "TotalProperties", "Properties", "Completed" };


CAchievements::CAchievements(string theName, vector<CProperties*> theRelatedProps, bool mUnlocked)
{
	mName = theName;
	mProps = theRelatedProps;
	this->mUnlocked = mUnlocked;
}


CAchievements::~CAchievements(void)
{

}

void CAchievements::Update()
{
	if (mUnlocked == false)
	{
		for (unsigned int i = 0; i < mProps.size(); i++)
		{
			if (mProps[i]->GetClearActivation() == false)
			{
				break;
			}
			else
			{
				cout << "YOU DIED" << endl;
				mUnlocked = true;	
				CLuaScript* m_cLuaScript;
				m_cLuaScript = new CLuaScript("Achievements");
				m_cLuaScript->saveAchievementValues();
				delete m_cLuaScript;
			}
		}
	}
}

vector<CProperties*> CAchievements::GetProps()
{
	return mProps;
}

void CAchievements::Save(fstream& file, int id)
{
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[TotalProperties] << id << " = " << mProps.size() << "\n";
	for (int i = 0; i < mProps.size(); i++)
	{
		file << propertyName[Properties] << id << "_" << i + 1 << " = " << "\"" << mProps[i]->GetName()  << "\"" << "\n";
	}
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
}
