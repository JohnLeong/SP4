#include "Achievements.h"

CAchievements::CAchievements(string theId, vector<CProperties*> theRelatedProps)
{
	mName = theId;
	mProps = theRelatedProps;
	mUnlocked = false;
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
				mUnlocked = true;
			}
		}
	}
}
