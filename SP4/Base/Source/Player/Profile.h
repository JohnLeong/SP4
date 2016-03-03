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
		HighestLevelUnlocked,
		NUM_Properties
	};

	CProfile(int theHighestLevelUnlocked);
	~CProfile(void);
	void Update();		// Update
	int GetHighestLevelUnlocked();
	void Save(fstream& file, int id);
	void Reset(fstream& file, int id);
	static string propertyName[NUM_Properties];

private:
	int mHighestLevelUnlocked;
};