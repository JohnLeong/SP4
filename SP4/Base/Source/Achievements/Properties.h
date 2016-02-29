#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../LuaScript.h"

using namespace std;
using std::string;
using std::vector;

class CProperties
{
public:
	enum saveProperties
	{
		Name,
		Value,
		Active,
		ActivationValue,
		Completed,
		NUM_Properties
	};
	
	CProperties(string theName, int theInitialValue, string theActivation, int theActivationValue, bool clearActivation);
	~CProperties(void);

	void Update();								// Update
	string GetName();
	void SetValue(int theValue);
	int GetValue();
	bool GetClearActivation();
	void ChangeValue(int changeNumber);
	void Save(fstream& file, int id);

	static string propertyName[NUM_Properties];
private:
	string mName;
	int mActivationValue;
	int mValue;
	string mActive;
	bool mClearActive;
	CLuaScript* m_cLuaScript;
};