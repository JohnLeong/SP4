#include "Properties.h"

string CProperties::propertyName[CProperties::NUM_Properties] = { "Name", "Title", "Value", "Active", "ActivationValue", "Completed" };

CProperties::CProperties(string theName, string theTitle, int theInitialValue, string theActivation, int theActivationValue, bool clearActivation)
{
	mName = theName;
	mTitle = theTitle;
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
			m_cLuaScript->saveAchievementPropertiesValues();
		}
	}
	else if (mActive == "ACTIVE_LESSER")
	{
		if (mValue < mActivationValue)
		{
			mClearActive = true;
			m_cLuaScript->saveAchievementPropertiesValues();
		}
	}
	else if (mActive == "ACTIVE_EQUAL")
	{
		if (mValue == mActivationValue)
		{
			mClearActive = true;
			m_cLuaScript->saveAchievementPropertiesValues();
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

string CProperties::GetTitle()
{
	return mTitle;
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

	m_cLuaScript = new CLuaScript("AchievementProperties");
	m_cLuaScript->saveAchievementPropertiesValues();
	delete m_cLuaScript;
	mValue += changeNumber;
}

void CProperties::Save(fstream& file, int id)
{
	file << propertyName[Name] << id << " = " << "\"" << mName << "\"" << "\n";
	file << propertyName[Title] << id << " = " << "\"" << mTitle << "\"" << "\n";
	file << propertyName[Value] << id << " = " << mValue << "\n";
	file << propertyName[Active] << id << " = " << "\"" << mActive << "\"" << "\n";
	file << propertyName[ActivationValue] << id << " = " << mActivationValue << "\n";
	file << propertyName[Completed] << id << " = " << mClearActive << "\n\n";
}