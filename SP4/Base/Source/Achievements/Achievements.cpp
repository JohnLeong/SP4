#include "Achievements.h"
#include "Properties.h"
CAchievements::CAchievements(string theName, vector<string> theRelatedProps, bool mUnlocked)
{
	mName = theName;
	mProps = theRelatedProps;
	this->mUnlocked = mUnlocked;
}


CAchievements::~CAchievements(void)
{
}

void CAchievements::Update(vector<CProperties*> propertyList)
{
	if (mUnlocked == false)
	{
		for (unsigned int i = 0; i < propertyList.size(); i++)
		{
			if (propertyList[i]->GetClearActivation() == false)
			{
				break;
			}
			else
			{
				mUnlocked = true;
			}
		}
	}
}
