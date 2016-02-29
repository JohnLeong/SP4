#include "Properties.h"

CProperties::CProperties(string theName, int theInitialValue, string theActivation, int theActivationValue, bool clearActivation)
{
	mName = theName;
	mValue = theInitialValue;
	mActive = theActivation;
	mActivationValue = theActivationValue;
	mClearActive = clearActivation;
}


CProperties::~CProperties(void)
{
}

void CProperties::Update()
{
	if (mActive == "ACTIVE_GREATER")
	{
		if (mValue > mActivationValue)
		{
			mClearActive = true;
			m_cLuaScript->recordAchievementPropertiesProgressBool(mName);
		}
	}
	else if (mActive == "ACTIVE_LESSER")
	{
		if (mValue < mActivationValue)
		{
			mClearActive = true;
			m_cLuaScript->recordAchievementPropertiesProgressBool(mName);
		}
	}
	else if (mActive == "ACTIVE_EQUAL")
	{
		if (mValue == mActivationValue)
		{
			mClearActive = true;
			m_cLuaScript->recordAchievementPropertiesProgressBool(mName);
		}
	}
	else
	{
		mClearActive = false;
	}
}

string CProperties::GetName()
{
	return mName;
}

void CProperties::SetValue(int theValue)
{
	mValue = theValue;
}

int CProperties::GetValue()
{
	return mValue;
}

bool  CProperties::GetClearActivation()
{
	return mClearActive;
}

void CProperties::ChangeValue(int changeNumber)
{
	int mChangedValue = mValue + changeNumber;

	ostringstream convertor;
	string getValue = "";
	convertor << mValue;
	getValue.append(convertor.str());

	string getChangedValue = "";
	convertor << mChangedValue;
	getChangedValue.append(convertor.str());

	m_cLuaScript = new CLuaScript("AchievementProperties", "AP");
	m_cLuaScript->recordAchievementPropertiesProgressValue(mName, getValue, getChangedValue);
	delete m_cLuaScript;
	mValue += changeNumber;
}