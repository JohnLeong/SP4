#include "Achievements.h"
#include "Properties.h"
	
string CAchievements::propertyName[CAchievements::NUM_Properties] = { "Name", "Title", "TotalProperties", "Properties", "Completed", "ShowedOnce" };


CAchievements::CAchievements(string theName, string theTitle, vector<string> theRelatedProps, bool mUnlocked, bool mAppearedOnce, bool mShowedOnce)
{
	mName = theName;
	mTitle = theTitle;
	mProps = theRelatedProps;
	this->mUnlocked = mUnlocked;
	this->mShowedOnce = mShowedOnce;
}


CAchievements::~CAchievements(void)
{
}

void CAchievements::Update(vector<CProperties*> checkList, double dt)
{
	if (mUnlocked == false)
	{
		for (int j = 0; j < mProps.size(); j++)
		{
			for (unsigned int i = 0; i < checkList.size(); i++)
			{
				if (checkList[i]->GetName() == mProps[j])
				{
					if (checkList[i]->GetClearActivation() == false)
					{
						break;
					}
					else
					{
						mUnlocked = true;
						CLuaScript* m_cLuaScript;
						m_cLuaScript = new CLuaScript("Achievements");
						m_cLuaScript->saveAchievementValues();
						delete m_cLuaScript;
					}
				}
			}
		}
	}
	if (mUnlocked == true && mShowedOnce == false)
	{
		if (mAppearedOnce == false)
		{
			/* Show Box*/
			if (dt > 10) //When the box appears completely finished
			{
				mAppearedOnce == true;
				dt = 0;
			}
		}
		else
		{
			/* Hide Box*/
			if (dt > 10) //When the box hides finished
			{
				mShowedOnce == true;
				CLuaScript* m_cLuaScript;
				m_cLuaScript = new CLuaScript("Achievements");
				m_cLuaScript->saveAchievementValues();
				delete m_cLuaScript;
			}
		}
	}
}

vector<string> CAchievements::GetProps()
{
	return mProps;
}

void CAchievements::Save(fstream& file, int id)
{
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[Title] << id << " = " << "\"" << mTitle << "\"" << "\n";
	file << propertyName[TotalProperties] << id << " = " << mProps.size() << "\n";
	for (int i = 0; i < mProps.size(); i++)
	{
		file << propertyName[Properties] << id << "_" << i + 1 << " = " << "\"" << mProps[i] << "\"" << "\n";
	}
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
	file << propertyName[ShowOnce] << id << " = " << mShowedOnce << "\n\n";
}
