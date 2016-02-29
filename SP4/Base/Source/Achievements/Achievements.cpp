#include "Achievements.h"
#include "Properties.h"
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
				mUnlocked = true;	
				CLuaScript* m_cLuaScript;
				m_cLuaScript = new CLuaScript("Achievements", "A");
				m_cLuaScript->recordAchievementProgress(mName);
				delete m_cLuaScript;
			}
		}
	}
}

vector<CProperties*> CAchievements::GetProps()
{
	return mProps;
}
