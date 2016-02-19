#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class CProperties
{
public:
	enum mActivation
	{
		ACTIVE_GREATER,
		ACTIVE_LESSER,
		ACTIVE_EQUAL,
		NUM_ACTIVE
	};

	CProperties(string theName, int theInitialValue, mActivation theActivation, int theActivationValue, bool clearActivation);
	~CProperties(void);

	void Update();								// Update

	string GetName();

	void SetValue(int theValue);

	int GetValue();

	bool GetClearActivation();
private:
	string mName;
	int mActivationValue;
	int mValue;
	mActivation mActive;
	bool mClearActive;
};