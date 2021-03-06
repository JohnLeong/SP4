#include "Achievements.h"
#include "Properties.h"
	
string CAchievements::propertyName[CAchievements::NUM_Properties] = { "Name", "Title", "TotalProperties", "Properties", "Completed", "ShowedOnce" };


CAchievements::CAchievements(string theName, string theTitle, vector<string> theRelatedProps, int mUnlocked, bool mAppearedOnce, int mShowedOnce, double mTimer)
{
	mName = theName;
	mTitle = theTitle;
	mProps = theRelatedProps;
	this->mUnlocked = mUnlocked;
	this->mAppearedOnce = mAppearedOnce;
	this->mShowedOnce = mShowedOnce;
	this->mTimer = mTimer;
}


CAchievements::~CAchievements(void)
{
}

void CAchievements::Update(vector<CProperties*> checkList)
{
	if (mUnlocked == false)
	{
		for (unsigned j = 0; j < mProps.size(); j++)
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

int CAchievements::GetUnlocked()
{
	return mUnlocked;
}

bool CAchievements::GetAppearedOnce()
{
	return mAppearedOnce;
}

int CAchievements::GetShowedOnce()
{
	return mShowedOnce;
}

double CAchievements::GetTimer()
{
	return mTimer;
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

void CAchievements::SetTimer(double mTimer)
{
	this->mTimer = mTimer;
}

void CAchievements::Save(fstream& file, int id)
{
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[Title] << id << " = " << "\"" << mTitle << "\"" << "\n";
	file << propertyName[TotalProperties] << id << " = " << mProps.size() << "\n";
	for (unsigned i = 0; i < mProps.size(); i++)
	{
		file << propertyName[Properties] << id << "_" << i + 1 << " = " << "\"" << mProps[i] << "\"" << "\n";
	}
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
	file << propertyName[ShowOnce] << id << " = " << mShowedOnce << "\n\n";
}

void CAchievements::Reset(fstream& file, int id)
{
	mUnlocked = 0;
	mShowedOnce = 0;
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[Title] << id << " = " << "\"" << mTitle << "\"" << "\n";
	file << propertyName[TotalProperties] << id << " = " << mProps.size() << "\n";
	for (unsigned i = 0; i < mProps.size(); i++)
	{
		file << propertyName[Properties] << id << "_" << i + 1 << " = " << "\"" << mProps[i] << "\"" << "\n";
	}
	file << propertyName[Completed] << id << " = " << mUnlocked << "\n";
	file << propertyName[ShowOnce] << id << " = " << mShowedOnce << "\n\n";
}