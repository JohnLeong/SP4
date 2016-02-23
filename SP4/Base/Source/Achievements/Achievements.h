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
	CAchievements(string theName, vector<string> theRelatedProps, bool mUnlocked);
	~CAchievements(void);
	void Update(vector<CProperties*> propertyList);								// Update

private:
	string mName; // achievement name
	vector<string> mProps;
	bool mUnlocked;
};