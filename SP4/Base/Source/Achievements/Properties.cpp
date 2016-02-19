#include "Properties.h"

CProperties::CProperties(string theName, int theInitialValue, mActivation theActivation, int theActivationValue, bool clearActivation)
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
	switch (mActive)
	{
	case ACTIVE_GREATER:
		if (mValue > mActivationValue)
			mClearActive = true;
		break;
	case ACTIVE_LESSER:
		if (mValue < mActivationValue)
			mClearActive = true;
		break;
	case ACTIVE_EQUAL:
		if (mValue == mActivationValue)
			mClearActive = true;
		break;
	default:
		mClearActive = false;
		break;
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