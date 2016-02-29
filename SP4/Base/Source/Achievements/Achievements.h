#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using std::string;
using std::vector;

class CProperties;
class CAchievements
{
public:

	enum saveProperties
	{
		Name,
		TotalProperties,
		Properties,
		Completed,
		NUM_Properties
	};

	CAchievements(string theName, vector<CProperties*> theRelatedProps, bool mUnlocked);
	~CAchievements(void);
	void Update();								// Update
	vector<CProperties*> GetProps();
	void Save(fstream& file, int id);

	static string propertyName[NUM_Properties];
private:
	string mName; // achievement name
	vector<CProperties*> mProps;
	bool mUnlocked;

};