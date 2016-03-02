#include "Achievements.h"
#include "Properties.h"
	
string CAchievements::propertyName[CAchievements::NUM_Properties] = { "Name", "Title", "TotalProperties", "Properties", "Completed", "ShowedOnce" };


CAchievements::CAchievements(string theName, string theTitle, vector<string> theRelatedProps, bool mUnlocked, bool mAppearedOnce, bool mShowedOnce)
{
	mName = theName;
	mTitle = theTitle;
	mProps = theRelatedProps;
	this->mUnlocked = mUnlocked;
	this->mAppearedOnce = mAppearedOnce;
	this->mShowedOnce = mShowedOnce;
}


CAchievements::~CAchievements(void)
{
}

void CAchievements::Update(vector<CProperties*> checkList)
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
}

vector<string> CAchievements::GetProps()
{
	return mProps;
}

string CAchievements::GetTitle()
{
	return mTitle;
}

bool CAchievements::GetUnlocked()
{
	return mUnlocked;
}

bool CAchievements::GetAppearedOnce()
{
	return mAppearedOnce;
}

bool CAchievements::GetShowedOnce()
{
	return mShowedOnce;
}

void CAchievements::SetUnlocked(bool mUnlocked)
{
	this->mUnlocked = mUnlocked;
}

void CAchievements::SetAppearedOnce(bool mAppearedOnce)
{
	this->mAppearedOnce = mAppearedOnce;
}

void CAchievements::SetShowedOnce(bool mShowedOnce)
{
	this->mShowedOnce = mShowedOnce;
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
	file << propertyName[ShowOnce] << id << " = " << mShowedOnce << "\n\n";
}

void CAchievements::Reset(fstream& file, int id)
{
	mUnlocked = false;
	mShowedOnce = false;
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[Title] << id << " = " << "\"" << mTitle << "\"" << "\n";
	file << propertyName[TotalProperties] << id << " = " << mProps.size() << "\n";
	for (int i = 0; i < mProps.size(); i++)
	{
		file << propertyName[Properties] << id << "_" << i + 1 << " = " << "\"" << mProps[i] << "\"" << "\n";
	}
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
	file << propertyName[ShowOnce] << id << " = " << mShowedOnce << "\n\n";
}