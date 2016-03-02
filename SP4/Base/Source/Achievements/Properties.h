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
		Title,
		Value,
		Active,
		ActivationValue,
		Completed,
		NUM_Properties
	};
	
	CProperties(string theName, string theTitle, int theInitialValue, string theActivation, int theActivationValue, bool clearActivation);
	~CProperties(void);

	void Update();								// Update
	string GetName();
	string GetTitle();
	void SetValue(int theValue);
	int GetValue();
	bool GetClearActivation();
	void ChangeValue(int changeNumber);
	void Save(fstream& file, int id);
	void Reset(fstream& file, int id);

	static string propertyName[NUM_Properties];
private:
	string mName;
	string mTitle;
	int mActivationValue;
	int mValue;
	string mActive;
	bool mClearActive;
	CLuaScript* m_cLuaScript;
};