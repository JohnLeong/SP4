#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;
using std::string;
using std::vector;

class CProfile
{
public:

	enum saveProperties
	{
		Name,
		HighestLevelUnlocked,
		NUM_Properties
	};

	CProfile(string theName, int theHighestLevelUnlocked);
	~CProfile(void);
	void Update();		// Update
	string GetName();
	int GetHighestLevelUnlocked();
	void Save(fstream& file, int id);

	static string propertyName[NUM_Properties];

private:
	string mName;
	int mHighestLevelUnlocked;
};